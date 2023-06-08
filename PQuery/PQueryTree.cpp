#include "PQueryTree.h"
#include <algorithm>
#include <cassert>

PTreeNode::~PTreeNode(){
    if(left_ != nullptr)
        delete left_;
    if(right_ != nullptr)
        delete right_;
}

void PTreeNode::print(int dep) const {
    operator_->print(dep);
    if(left_ != nullptr){
        for(int i = 0; i < dep; ++i) std::printf("\t");
        std::printf("Left:\n");
        left_->print(dep + 1);
    }
    if(right_ != nullptr){
        for(int i = 0; i < dep; ++i) std::printf("\t");
        std::printf("Right:\n");
        right_->print(dep + 1);
    }
}

PTreeNode * PQueryTree::GenerateQueryTree(const CypherAST * cypher_ast){
    PQueryTree * qt = new PQueryTree(cypher_ast->id2var_name_, cypher_ast->prop2id_, cypher_ast
    ->prop_id2string_);
    qt->GetQueryTree(cypher_ast);
    PTreeNode *tree = qt->root_;
    delete qt;
    return tree;
}

PQueryTree::PQueryTree(const std::shared_ptr<std::vector<std::string>>& id2var_name,
           const std::shared_ptr<std::unordered_map<std::string, unsigned>> & prop2id,
           const std::shared_ptr<std::map<unsigned, std::string>> & prop_id2string):
           root_(nullptr), id2var_name_(id2var_name), prop2id_(prop2id), prop_id2string_(prop_id2string){

}

PQueryTree::~PQueryTree() {
    root_ = nullptr;
}

/**
 * @brief Generate plan tree according to a cypher AST, and store the plan tree to PQueryTree::root.
 * @param cypher_ast A Cypher AST
 * */
void PQueryTree::GetQueryTree(const CypherAST * cypher_ast){
    if(cypher_ast->union_all_.empty()){
        root_ = GetQueryTree(cypher_ast->single_querys_[0].get());
        return;
    }

    int n = cypher_ast->union_all_.size(), last_union;
    for(last_union = n - 1; last_union >= 0; --last_union){
        if(cypher_ast->union_all_.at(last_union) == false){
            break;
        }
    }
    std::unique_ptr<PTreeNode> tree;
    tree.reset(GetQueryTree(cypher_ast->single_querys_[0].get()));
    for(int i = 0; i < n; ++i){
        auto right_child = GetQueryTree(cypher_ast->single_querys_[i + 1].get());
        auto new_tree = GenerateCypherUnion(tree.release(), right_child);
        if(i == last_union){
            new_tree = GenerateDistinct(new_tree);
        }
        tree.reset(new_tree);
    }
    root_ = tree.release();
}

/**
 * @brief Generate a plan tree for a SingleQueryAST.
 * @param single_query Pointer to SingleQueryAST.
 * @return Root of the plan tree.
 * */
PTreeNode * PQueryTree::GetQueryTree(const SingleQueryAST * single_query){
    PTreeNode * tree = GetQueryTree(single_query->query_units_[0].get(), nullptr);
    for(int i = 1; i < (int)single_query->query_units_.size(); ++i){
        tree = GetQueryTree(single_query->query_units_[i].get(), tree);
    }
    return tree;
}

/**
 * @brief Generate a plan tree for a QueryUnitAST.
 * @param query_unit Pointer to QueryUnitAST.
 * @param tree Plan tree that we already have.
 * */
PTreeNode * PQueryTree::GetQueryTree(const QueryUnitAST * query_unit, PTreeNode * tree){
    int n = query_unit->reading_.size(), m = query_unit->updating_.size();

    /// handle reading clauses
    for(int i = 0; i < n; ++i){
        auto & read = query_unit->reading_[i];
        if(read->reading_form_ == ReadingAST::MATCH &&
           dynamic_cast<MatchAST*>(read.get())->is_optional_ == false){
            int j = i;
            for(;j < n; ++j){
                if(query_unit->reading_[j]->reading_form_ != ReadingAST::MATCH ||
                   dynamic_cast<MatchAST*>(query_unit->reading_[j].get())->is_optional_ )
                    break;
            }
            // Match Region i, i + 1, ..., j - 1
            std::vector<BGPOperator*> bgps;
            for(int k = i; k < j; ++k){
                MatchAST * match = dynamic_cast<MatchAST*>(query_unit->reading_[k].get());
                auto match_bgp = GetBGPFromMatch(match);
                bgps.push_back(match_bgp);
            }
            BGPOperator *total_bgp = MergeBGP(bgps);
            // now we only need to consider join tree && total_bgp
            tree = SplitBGPByConnectedComponent(total_bgp, tree);
            i = j - 1; // iter i to j - 1, then j
        } else if(read->reading_form_ == ReadingAST::MATCH){
            // do optional match
            MatchAST * match = dynamic_cast<MatchAST*>(read.get());
            auto bgp = GetBGPFromMatch(match);
            auto right = SplitBGPByConnectedComponent(bgp, nullptr);

            tree = GenerateBinaryOperator(tree ,right, PQueryOperator::OPTIONAL);
        } else if( read->reading_form_ == ReadingAST::UNWIND){
            tree = GetQueryTree(dynamic_cast<UnwindAST *>(read.get()), tree);
        } else if( read->reading_form_ == ReadingAST::INQUERY_CALL){
            tree = GetQueryTree(dynamic_cast<const InQueryCallAST *>(read.get()), tree);
        }
    }

    /// TODO: Handle updating clauses
    for(int i = 0; i < m; ++i){
        auto & update = query_unit->updating_[i];
        if(update->updating_form_ == UpdatingAST::CREATE){
            CreateAST * create_ = dynamic_cast<CreateAST *>(update.get());
            tree = GetQueryTree(create_, tree);
        } else if(update->updating_form_ == UpdatingAST::DELETE){
            DeleteAST * del_ = dynamic_cast<DeleteAST*> (update.get());
            tree= GetQueryTree(del_, tree);
        } else if(update->updating_form_ == UpdatingAST::SET){
            SetAST * set_ = dynamic_cast<SetAST *>(update.get());
            tree = GetQueryTree(set_, tree);
        } else if(update->updating_form_ == UpdatingAST::REMOVE){
            RemoveAST * rm_ = dynamic_cast<RemoveAST*>(update.get());
            tree = GetQueryTree(rm_, tree);
        } else {
            assert(false);
        }
    }
    /// Handle WithReturn
    if(query_unit->with_return_ != nullptr)
        tree = GetQueryTree(query_unit->with_return_.get(), tree);
    /// Filter Pushdown
    tree = FilterPushdown(tree, nullptr, nullptr);
    /// Clip by return clause
    if(query_unit->with_return_ == nullptr){
        ClipVarset(tree, PVarset<unsigned>());
    } else if(!query_unit->with_return_->with_){
        ClipVarset(tree, PVarset<unsigned>(query_unit->with_return_->column_var_id_));
        tree->operator_->minimal_varset_.vars = query_unit->with_return_->column_var_id_;   // To keep order.
    }
    return tree;
}

/**
 * @brief Get a BGP Operator From a match AST. Store Pattern, Edge Conflict, Where Filter to BGP, and initialize maximal_varset.
 * All the property map constraint e.g. { age : 10 } will be rewrite to Filter.
 * The shortest path pattern will be rewrite, such that src and tgt dont have constraint.
 * @warning Filter may contain vars that do not belong to this BGP.
 * @param match Pointer to MATCH AST.
 * @return Pointer to BGP Operator.
 * */

BGPOperator * PQueryTree::GetBGPFromMatch(const MatchAST * match){
    BGPOperator *bgp = new BGPOperator;
    PVarset<unsigned > edges;
    std::map<unsigned, GPStore::NodePattern *> id2node;
    /// handle all path pattern except shortest_path
    for(auto & pat : match->pattern_){
        if(pat->type_ != GPStore::RigidPattern::PATH) continue;
        bgp->pattern_.emplace_back(new GPStore::RigidPattern(*pat));
        for(auto & n : bgp->pattern_.back()->nodes_){
            id2node.insert(std::make_pair(n->var_id_, n.get()));
            for(auto & prop : n->properties_){
                bgp->filters_.emplace_back( GPStore::Expression::VarPropertyToExpression(n->var_id_, n->var_name_,
                                                                                         n->prop_id[prop.first],prop.first, new GPStore::Expression(*prop.second)));

            }
            n->properties_.clear();
            n->prop_id.clear();
        }
        for(auto & e : bgp->pattern_.back()->edges_){
            edges.addVar(e->var_id_);
            for(auto & prop : e->properties_){
                bgp->filters_.emplace_back( GPStore::Expression::VarPropertyToExpression(e->var_id_, e->var_name_,
                                                                                         e->prop_id[prop.first],prop.first, new GPStore::Expression(*prop.second)));

            }
            e->properties_.clear();
            e->prop_id.clear();
        }
    }
    /// handle edge conflict
    std::sort(edges.vars.begin(), edges.vars.end());
    unsigned edge_cnt = edges.getVarsetSize();
    for(unsigned  i = 0; i < edge_cnt; ++i){
        for(unsigned  j = i + 1; j < edge_cnt; ++j){
            bgp->edge_conflict_.addVar(std::make_pair(edges.vars[i], edges.vars[j]));
        }
    }
    /// handle shortestPath
    for(auto & shortest : match->pattern_){
        if(shortest->type_ == GPStore::RigidPattern::PATH) continue;
        std::unique_ptr<GPStore::RigidPattern> pat(new GPStore::RigidPattern(*shortest));
        for(int i = 0; i < 2; ++i){
            unsigned node_id = pat->nodes_[i]->var_id_;
            auto it = id2node.find(node_id);
            if(it == id2node.end()){
                std::unique_ptr<GPStore::NodePattern> new_node(new GPStore::NodePattern(pat->nodes_[i]->is_anno_var_, pat->nodes_[i]->var_name_,
                                                     pat->nodes_[i]->var_id_));
                new_node->labels_ = pat->nodes_[i]->labels_;
                bgp->pattern_.emplace_back(new GPStore::RigidPattern(*new_node));
                id2node.insert(std::make_pair(node_id, bgp->pattern_.back()->nodes_[0].get()));
            }
            it = id2node.find(node_id);
            auto & target_labels = it->second->labels_;
            for(auto & label : pat->nodes_[i]->labels_){
                if(std::find(target_labels.begin(), target_labels.end(), label) != target_labels.end()){
                    target_labels.emplace_back(label);
                }
            }
            pat->nodes_[i]->labels_.clear();
            for(auto & prop : pat->nodes_[i]->properties_){
                bgp->filters_.emplace_back(GPStore::Expression::VarPropertyToExpression(node_id, pat->nodes_[i]->var_name_,
                                                                                        pat->nodes_[i]->prop_id[prop.first], prop.first,
                                                                                        new GPStore::Expression(*prop.second)));

            }
            pat->nodes_[i]->properties_.clear();
        }
        bgp->pattern_.emplace_back(pat.release());
    }
    if(match->where_ != nullptr){
        auto filters = GPStore::Expression::split(new GPStore::Expression(*match->where_), GPStore::Expression::AND);
        for(auto f : filters){
            bgp->filters_.emplace_back(f);
        }
    }

    /// maximal var set
    for(const auto & pat : bgp->pattern_){
        bgp->maximal_varset_ += pat->covered_var_id_;
    }
    return bgp;
}

/**
 * @brief Generate Plan Tree for Unwind clause
 * @param unwind Pointer to UnwindAST
 * @param tree plan tree we already have
 * @return root of the plan tree.
 * */
PTreeNode * PQueryTree::GetQueryTree(const UnwindAST* unwind, PTreeNode * tree){
    std::unique_ptr<PTreeNode> new_tree(new PTreeNode);
    std::unique_ptr<UnwindOperator> unwind_op(new UnwindOperator);
    unwind_op->unwind_.reset(new GPStore::Expression(*unwind->exp_));
    unwind_op->var_id_ = unwind->var_id_;
    new_tree->operator_.reset(unwind_op.release());
    if(tree != nullptr)
        new_tree->operator_->maximal_varset_ = tree->operator_->maximal_varset_;
    new_tree->operator_->maximal_varset_.addVar(unwind->var_id_);
    new_tree->left_ = tree;
    return new_tree.release();
}

/**
 * @brief Generate Plan Tree for Call clause
 * @param call Pointer to InQueryCall
 * @param tree plan tree we already have
 * @return root of the plan tree.
 * */
PTreeNode * PQueryTree::GetQueryTree(const InQueryCallAST* call, PTreeNode * tree){
    std::unique_ptr<PTreeNode> new_tree(new PTreeNode);
    std::unique_ptr<CallOperator> call_op(new CallOperator);
    int n = call->yield_var_id_.size();
    call_op->procedure_name_ = call->procedure_name_;
    for(auto & arg : call->args_){
        call_op->args_.emplace_back(new GPStore::Expression(*arg));
    }
    for(int i = 0; i < n; ++i){
        call_op->yield_var_id_.push_back(call->yield_var_id_[i]);
        call_op->yield_items_.emplace_back(call->yield_items_[i]);
    }
    if(tree != nullptr)
        call_op->maximal_varset_ = tree->operator_->maximal_varset_;
    call_op->maximal_varset_ += PVarset<unsigned >(call_op->yield_var_id_);
    new_tree->operator_.reset(call_op.release());
    new_tree->left_ = tree;
    tree = new_tree.release();
    if(call->where_ != nullptr){
        auto filters = GPStore::Expression::split(new GPStore::Expression(*(call->where_)), GPStore::Expression::AND);

        tree =  GenerateRelatedFilters(filters, tree);
    }
    return tree;
}

/**
 * @brief Generate Plan Tree for WITH/RETURN clause
 * @param call Pointer to WithReturnAST
 * @param tree plan tree we already have
 * @return root of the plan tree.
 * */
PTreeNode * PQueryTree::GetQueryTree(const WithReturnAST* with_return, PTreeNode * tree){
    std::unique_ptr<ProjectionOperator> proj(new ProjectionOperator);
    std::unique_ptr<GroupByOperator> group;
    std::unique_ptr<AggregationOperator> aggr;
    std::unique_ptr<ModifierOperator> modifier;
    std::unique_ptr<PTreeNode> new_tree;
    int n = with_return->proj_exp_.size();
    if(!with_return->aggregation_){
        for(int i = 0; i < n; ++i){
            if(with_return->proj_exp_[i]->isVariable() && (with_return->alias_[i].empty() ||
            with_return->proj_exp_[i]->getVariableName() == with_return->alias_[i]))
                continue;
            proj->proj_exps_.emplace_back(new GPStore::Expression(*with_return->proj_exp_[i]));
            proj->var_id_.push_back(with_return->column_var_id_[i]);
        }
        if(!proj->proj_exps_.empty()){
            new_tree.reset(new PTreeNode);
            if(tree != nullptr)
                proj->maximal_varset_ = tree->operator_->maximal_varset_ ;
            proj->maximal_varset_ += PVarset<unsigned >(proj->var_id_);
            new_tree->operator_.reset(proj.release());
            new_tree->left_ = tree;
            tree = new_tree.release();
        }
    }
    else {
        group.reset(new GroupByOperator);
        aggr.reset(new AggregationOperator);
        for(int i = 0; i < n; ++i){
            if(with_return->proj_exp_[i]->containsAggrFunc()){
                aggr->aggr_value_.emplace_back(new GPStore::Expression(*with_return->proj_exp_[i]));
                aggr->aggr_var_id_.push_back(with_return->column_var_id_[i]);
            } else {
                group->grouping_keys_.push_back(with_return->column_var_id_[i]);
                aggr->grouping_keys_.push_back(with_return->column_var_id_[i]);
                if(with_return->proj_exp_[i]->isVariable() && (with_return->alias_[i].empty() ||
                                                               with_return->proj_exp_[i]->getVariableName() == with_return[i].alias_[i])){
                    continue;
                }
                proj->proj_exps_.emplace_back(new GPStore::Expression(*with_return->proj_exp_[i]));
                proj->var_id_.push_back(with_return->column_var_id_[i]);
            }
        }
        if(!proj->proj_exps_.empty()){
            new_tree.reset(new PTreeNode);
            if(tree != nullptr)
                proj->maximal_varset_ = tree->operator_->maximal_varset_ ;
            proj->maximal_varset_ += PVarset<unsigned >(proj->var_id_);
            new_tree->operator_.reset(proj.release());
            new_tree->left_ = tree;
            tree = new_tree.release();
        }

        new_tree.reset(new PTreeNode);
        if(tree != nullptr)
            group->maximal_varset_ = tree->operator_->maximal_varset_;
        new_tree->operator_.reset(group.release());
        new_tree->left_ = tree;
        tree = new_tree.release();

        new_tree.reset(new PTreeNode);
        if(tree != nullptr)
            aggr->maximal_varset_ = tree->operator_->maximal_varset_;
        aggr->maximal_varset_ += PVarset<unsigned >(aggr->aggr_var_id_);
        new_tree->operator_.reset(aggr.release());
        new_tree->left_ = tree;
        tree = new_tree.release();
    }
    if(with_return->skip_ != 0 || with_return->limit_ != INVALID || !with_return->order_by_.empty() ||
        with_return->distinct_){
        modifier.reset(new ModifierOperator);
        if(with_return->distinct_){
            modifier->distinct_ = with_return->distinct_;
            PVarset<unsigned > dis_var = with_return->column_var_id_;
            if(with_return->asterisk_)
                dis_var += with_return->implict_proj_var_id_;
        }
        modifier->limit_ = with_return->limit_;
        modifier->skip_ = with_return->skip_;
        for(int i = 0; i < (int)with_return->order_by_.size(); ++i){
            modifier->order_exps_.emplace_back(new GPStore::Expression(*with_return->order_by_[i]));
            modifier->ascending_.push_back( with_return->ascending_[i]);
        }
        if(tree != nullptr) modifier->maximal_varset_ = tree->operator_->maximal_varset_;
        new_tree.reset(new PTreeNode);
        new_tree->operator_.reset(modifier.release());
        new_tree->left_ = tree;
        tree = new_tree.release();
    }
    if(with_return->where_){
        auto filters = GPStore::Expression::split(new GPStore::Expression(*with_return->where_), GPStore::Expression::AND);
        tree = GenerateRelatedFilters(filters, tree);
    }

    return tree;
}

/**
 * @brief Generate Plan Tree for CREATE clause
 * @param _create Pointer to CreateAST
 * @param tree plan tree we already have
 * @return root of the plan tree.
 * */
PTreeNode * PQueryTree::GetQueryTree(const CreateAST * _create, PTreeNode * tree){
    std::unique_ptr<PTreeNode> new_tree(new PTreeNode);
    std::unique_ptr<CreateOperator> create_op(new CreateOperator);

    PVarset<unsigned > addition;
    for(auto & rigid : _create->pattern_){
        create_op->pattern_.emplace_back(new GPStore::RigidPattern(*rigid));
        addition += rigid->covered_var_id_;
    }

    if(tree != nullptr)
        create_op->maximal_varset_ = tree->operator_->maximal_varset_;
    create_op->maximal_varset_ += addition;
    new_tree->operator_.reset(create_op.release());
    new_tree->left_ = tree;
    return new_tree.release();
}

/**
 * @brief Generate Plan Tree for DELETE clause
 * @param _delete Pointer to DeleteAST
 * @param tree plan tree we already have
 * @return root of the plan tree.
 * */
PTreeNode * PQueryTree::GetQueryTree(const DeleteAST * _delete, PTreeNode * tree){
    std::unique_ptr<PTreeNode> new_tree(new PTreeNode);
    std::unique_ptr<DeleteOperator> delete_op(new DeleteOperator);

    for(auto & del_exp : _delete->exp_){
        delete_op->exp_.emplace_back(new GPStore::Expression(*del_exp));
    }

    if(tree != nullptr)
        delete_op->maximal_varset_ = tree->operator_->maximal_varset_;

    new_tree->operator_.reset(delete_op.release());
    new_tree->left_ = tree;
    return new_tree.release();
}

/**
 * @brief Generate Plan Tree for Set clause
 * @param _set Pointer to SetAST
 * @param tree plan tree we already have
 * @return root of the plan tree.
 * */
PTreeNode * PQueryTree::GetQueryTree(const SetAST * _set, PTreeNode * tree){
    std::unique_ptr<PTreeNode> new_tree(new PTreeNode);
    std::unique_ptr<SetOperator> set_op(new SetOperator);

    for(auto & set_item : _set->set_items_){
        if(set_item->set_type_ == SetItemAST::NODE_LABELS){
            set_op->var_ids_.push_back(set_item->var_id_);
            set_op->var_names_.emplace_back(set_item->var_name_);
        }
        if(set_item->set_type_ == SetItemAST::SINGLE_PROPERTY){
            set_op->prop_exps_.emplace_back(new GPStore::Expression(*set_item->prop_exp_));
            set_op->prop_vals_.emplace_back(new GPStore::Expression(*set_item->exp_));
        }
    }
    for(auto & set_item : _set->set_items_) {
        if(set_item->set_type_ == SetItemAST::ASSIGN_PROPERTIES
        || set_item->set_type_ == SetItemAST::ADD_PROPERTIES){
            set_op->var_ids_.push_back(set_item->var_id_);
            set_op->var_names_.emplace_back(set_item->var_name_);
            set_op->exps_.emplace_back(new GPStore::Expression(*set_item->exp_));
            set_op->add_property_.push_back(set_item->set_type_ == SetItemAST::ADD_PROPERTIES);
        }
    }

    if(tree != nullptr)
        set_op->maximal_varset_ = tree->operator_->maximal_varset_;

    new_tree->operator_.reset(set_op.release());
    new_tree->left_ = tree;
    return new_tree.release();
}

PTreeNode * PQueryTree::GetQueryTree(const RemoveAST * _remove, PTreeNode * tree){
    std::unique_ptr<PTreeNode> new_tree(new PTreeNode);
    std::unique_ptr<RemoveOperator> rm_op(new RemoveOperator);

    for(auto & rm_item : _remove->remove_items_){
        if(rm_item->prop_exp_ != nullptr){
            rm_op->prop_exps_.emplace_back(new GPStore::Expression(*rm_item->prop_exp_));
        } else {
            rm_op->var_ids_.push_back(rm_item->var_id_);
            rm_op->var_names_.emplace_back(rm_item->var_name_);
            rm_op->labels_.emplace_back();
            for(const auto & label : rm_item->labels_)
                rm_op->labels_.back().emplace_back(label);
        }

    }

    if(tree != nullptr)
        rm_op->maximal_varset_ = tree->operator_->maximal_varset_;

    new_tree->operator_.reset(rm_op.release());
    new_tree->left_ = tree;
    return new_tree.release();
}

void PQueryTree::ClipVarset(PTreeNode * tree, const PVarset<unsigned> & required){
    if(tree == nullptr) return;
    PQueryOperator::OperatorType op = tree->operator_->type_;
    PVarset<unsigned > this_required;
    if(op == PQueryOperator::BGP) {
        tree->operator_->minimal_varset_ = tree->operator_->maximal_varset_ * required;
    }
    else if( op == PQueryOperator::FILTER){
        for(auto & filter : dynamic_cast<FilterOperator*>(tree->operator_.get())->filters_){
            this_required += filter->covered_var_id_;
        }
        ClipVarset(tree->left_, this_required + required);
        tree->operator_->minimal_varset_ = tree->left_->operator_->minimal_varset_ * required;
    }
    else if( op == PQueryOperator::PROJECTION){
        ProjectionOperator *proj_op = dynamic_cast<ProjectionOperator*>(tree->operator_.release());
        int n = proj_op->proj_exps_.size();
        std::vector<std::unique_ptr<GPStore::Expression>> new_exp;
        std::vector<unsigned > new_id;
        for(int i = 0; i < n; ++i){
            if(required.findVar(proj_op->var_id_[i])){
                this_required += proj_op->proj_exps_[i]->covered_var_id_;
                new_exp.emplace_back(proj_op->proj_exps_[i].release());
                new_id.push_back(proj_op->var_id_[i]);
            } else {
                proj_op->proj_exps_[i].reset(nullptr);
            }
        }
        if(!new_exp.empty()) {
            proj_op->proj_exps_.swap(new_exp);
            proj_op->var_id_.swap(new_id);
        }
        tree->operator_.reset(proj_op);
        if(tree->left_ != nullptr){
            ClipVarset(tree->left_, this_required + required);
            tree->operator_->minimal_varset_ = (tree->left_->operator_->minimal_varset_ + PVarset<unsigned >(proj_op->var_id_) ) * required;
        } else {
            tree->operator_->minimal_varset_ = required * PVarset<unsigned >(proj_op->var_id_);
        }
    }
    else if( op == PQueryOperator::AND || op == PQueryOperator::OPTIONAL || op == PQueryOperator::MINUS){
        this_required = tree->left_->operator_->maximal_varset_ * tree->right_->operator_->maximal_varset_;

        ClipVarset(tree->left_, this_required + required);
        ClipVarset(tree->right_, this_required + required);
        tree->operator_->minimal_varset_ = (tree->left_->operator_->minimal_varset_ + tree->right_->operator_->minimal_varset_) * required;

    }
    else if( op == PQueryOperator::UNION){
        ClipVarset(tree->left_, required);
        ClipVarset(tree->right_, required);
        tree->operator_->minimal_varset_ = (tree->left_->operator_->minimal_varset_ + tree->right_->operator_->minimal_varset_) * required;
    }
    else if( op == PQueryOperator::MODIFIER){
        ModifierOperator * modifier = dynamic_cast<ModifierOperator*>(tree->operator_.get());
        for(auto & order: modifier->order_exps_){
            this_required += order->covered_var_id_;
        }
        ClipVarset(tree->left_, this_required + required);
        tree->operator_->minimal_varset_ = tree->left_->operator_->minimal_varset_ * required;
    }
    else if( op == PQueryOperator::UNWIND){
        UnwindOperator * unwind = dynamic_cast<UnwindOperator*>(tree->operator_.get());
        this_required = unwind->unwind_->covered_var_id_;
        if(tree->left_ != nullptr) {
            ClipVarset(tree->left_, this_required + required);
            tree->operator_->minimal_varset_ = tree->left_->operator_->minimal_varset_;
        }
        tree->operator_->minimal_varset_.addVar(unwind->var_id_);
        tree->operator_->minimal_varset_ = tree->operator_->minimal_varset_ * required;
    }
    else if( op == PQueryOperator::CALL){
        CallOperator * call = dynamic_cast<CallOperator*>(tree->operator_.release());
        int n = call->args_.size();
        for(auto & arg : call->args_){
            this_required += arg->covered_var_id_;
        }

        std::vector<std::string> yield_item;
        std::vector<unsigned > yield_id;
        for(int i = 0; i < n; ++i){
            if(required.findVar(call->yield_var_id_[i])){
                yield_item.emplace_back(call->yield_items_[i]);
                yield_id.push_back(call->yield_var_id_[i]);
            }
        }
        call->yield_var_id_.swap(yield_id);
        call->yield_items_.swap(yield_item);
        tree->operator_.reset(call);

        if(tree->left_ != nullptr){
            ClipVarset(tree->left_, this_required + required);
            tree->operator_->minimal_varset_ = tree->left_->operator_->minimal_varset_;
        }
        tree->operator_->minimal_varset_ = (tree->operator_->minimal_varset_ + call->yield_var_id_) * required;
    }
    else if( op == PQueryOperator::CREATE){
        CreateOperator * create_ = dynamic_cast<CreateOperator*>(tree->operator_.get());
        for(auto & pat : create_->pattern_){
            this_required += pat->covered_var_id_;
        }
        if(tree->left_ != nullptr){
            ClipVarset(tree->left_, this_required + required);
            tree->operator_->minimal_varset_ = (tree->left_->operator_->minimal_varset_ + this_required) * required;
        }else{
            tree->operator_->minimal_varset_ = this_required * required;
        }
    }
    else if( op == PQueryOperator::DELETE){
        DeleteOperator * del_ = dynamic_cast<DeleteOperator*>(tree->operator_.get());
        for(auto & exp : del_->exp_){
            this_required += exp->covered_var_id_;
        }
        ClipVarset(tree->left_, this_required + required);
        tree->operator_->minimal_varset_ = tree->left_->operator_->minimal_varset_ * required;
    }
    else if( op == PQueryOperator::SET){
        SetOperator * set_ = dynamic_cast<SetOperator*>(tree->operator_.get());
        this_required = PVarset<unsigned >(set_->var_ids_);
        for(auto & exp : set_->exps_){
            this_required += exp->covered_var_id_;
        }
        for(auto & prop_exp : set_->prop_exps_){
            this_required += prop_exp->covered_var_id_;
        }
        for(auto & prop_val : set_->prop_vals_){
            this_required += prop_val->covered_var_id_;
        }
        ClipVarset(tree->left_, required + this_required);
        tree->operator_->minimal_varset_ = required * tree->left_->operator_->minimal_varset_;
    }
    else if( op == PQueryOperator::REMOVE){
        RemoveOperator * rm_ = dynamic_cast<RemoveOperator*> (tree->operator_.get());
        this_required.vars = rm_->var_ids_;
        for(auto & prop_exp : rm_->prop_exps_) this_required += prop_exp->covered_var_id_;

        ClipVarset(tree->left_, this_required + required);
        tree->operator_->minimal_varset_ = tree->left_->operator_->minimal_varset_ * required;
    }
    else if( op == PQueryOperator::GROUP_BY){
        GroupByOperator * group = dynamic_cast<GroupByOperator*>(tree->operator_.get());
        this_required.vars = group->grouping_keys_;
        ClipVarset(tree->left_, this_required + required);
        tree->operator_->minimal_varset_ = tree->left_->operator_->minimal_varset_ * required;
    }
    else if( op == PQueryOperator::AGGREGATION){
        AggregationOperator * aggr = dynamic_cast<AggregationOperator*>(tree->operator_.release());
        int n = aggr->aggr_value_.size();
        std::vector<std::unique_ptr<GPStore::Expression>> aggr_val;
        std::vector<unsigned > aggr_id;
        for(int i = 0; i < n; ++i){
            if(required.findVar(aggr->aggr_var_id_[i])){
                this_required += aggr->aggr_value_[i]->covered_var_id_;
                aggr_val.emplace_back(aggr->aggr_value_[i].release());
                aggr_id.push_back(aggr->aggr_var_id_[i]);
            } else {
                aggr->aggr_value_[i].reset(nullptr);
            }
        }
        aggr->aggr_value_.swap(aggr_val);
        aggr->aggr_var_id_.swap(aggr_id);
        ClipVarset(tree->left_, this_required + required);
        aggr->minimal_varset_ = (tree->left_->operator_->minimal_varset_ + aggr->aggr_var_id_)*required;
        tree->operator_.reset(aggr);
    }
    else if( op == PQueryOperator::SHORTEST_PATH){
        ShortestPathOperator *shortest = dynamic_cast<ShortestPathOperator*>(tree->operator_.get());
        this_required.addVar(shortest->src_);
        this_required.addVar(shortest->tgt_);
        ClipVarset(tree->left_, this_required + required);
        tree->operator_->minimal_varset_ = tree->left_->operator_->minimal_varset_;
        tree->operator_->minimal_varset_.addVar(shortest->edge_pattern_->var_id_);
        tree->operator_->minimal_varset_.addVar(shortest->path_var_id_);
        tree->operator_->minimal_varset_ = tree->operator_->minimal_varset_ * required;
    }
    else {
        assert(false);
    }
}

/**
 * @brief Push down a filter, Optionally Inject filter to BGP, And Operators.
 * */
PTreeNode * PQueryTree::FilterPushdown(PTreeNode *tree, PTreeNode * parent, GPStore::Expression * filter){
    if(tree == nullptr)
        return nullptr;

    if(filter == nullptr){
        if(tree->left_ != nullptr)
            tree->left_ = FilterPushdown(tree->left_, tree, nullptr);
        if(tree->right_ != nullptr)
            tree->right_ = FilterPushdown(tree->right_, tree, nullptr);
        if(tree->operator_->type_ != PQueryOperator::FILTER)
            return tree;
        PTreeNode * sub = tree->left_;
        for(auto & exp : dynamic_cast<FilterOperator*>(tree->operator_.get())->filters_){
            sub = FilterPushdown(sub, nullptr, exp.release());
        }
        tree->left_ = nullptr;
        delete tree;
        return sub;
    }
    // Now, filter != nullptr.

    PQueryOperator::OperatorType op = tree->operator_->type_;

    if(op == PQueryOperator::BGP) {
        BGPOperator * bgp = dynamic_cast<BGPOperator*>(tree->operator_.get());
        if(filter->covered_var_id_.belongTo(bgp->maximal_varset_)){
            bgp->filters_.emplace_back(filter);
        } else {
            std::vector<GPStore::Expression* >f;
            f.push_back(filter);
            tree = GenerateRelatedFilters(f, tree);
        }
    }
    else if( op == PQueryOperator::FILTER || op == PQueryOperator::PROJECTION || op == PQueryOperator::OPTIONAL ||
    op == PQueryOperator::MINUS ||  op == PQueryOperator::MODIFIER || op == PQueryOperator::UNWIND || op == PQueryOperator::CALL
    || op == PQueryOperator::CREATE || op == PQueryOperator::DELETE || op == PQueryOperator::SET ||
            op == PQueryOperator::REMOVE || op == PQueryOperator::GROUP_BY || op == PQueryOperator::AGGREGATION ||
            op == PQueryOperator::SHORTEST_PATH){
        if(tree->left_ != nullptr && filter->covered_var_id_.belongTo(tree->left_->operator_->maximal_varset_)){
            tree->left_ = FilterPushdown(tree->left_, tree, filter);
        } else if(op == PQueryOperator::FILTER){
            dynamic_cast<FilterOperator*>(tree->operator_.get())->filters_.emplace_back(filter);
        } else if(parent != nullptr && parent->operator_->type_ == PQueryOperator::FILTER){
            dynamic_cast<FilterOperator*>(parent->operator_.get())->filters_.emplace_back(filter);
        } else {
            std::vector<GPStore::Expression* >f;
            f.push_back(filter);
            tree = GenerateRelatedFilters(f, tree);
        }
    }
    else if( op == PQueryOperator::AND){
        if(tree->left_ != nullptr && filter->covered_var_id_.belongTo(tree->left_->operator_->maximal_varset_)){
            tree->left_ = FilterPushdown(tree->left_, tree, filter);
        } else if(tree->right_ != nullptr && filter->covered_var_id_.belongTo(tree->right_->operator_->maximal_varset_)){
            tree->right_ = FilterPushdown(tree->right_, tree, filter);
        } else if(filter->oprt_ == GPStore::Expression::EQUAL){
            dynamic_cast<AndOperator*>(tree->operator_.get())->filters_.emplace_back(filter);
        } else if(parent != nullptr && parent->operator_->type_ == PQueryOperator::FILTER){
            dynamic_cast<FilterOperator*>(parent->operator_.get())->filters_.emplace_back(filter);
        } else {
            std::vector<GPStore::Expression* >f;
            f.push_back(filter);
            tree = GenerateRelatedFilters(f, tree);
        }
    } else if(op == PQueryOperator::UNION){
        if(tree->left_ != nullptr && filter->covered_var_id_.belongTo(tree->left_->operator_->maximal_varset_)){
            tree->left_ = FilterPushdown(tree->left_, tree, filter);
            if(tree->right_ != nullptr && filter->covered_var_id_.belongTo(tree->right_->operator_->maximal_varset_)){
                tree->right_ = FilterPushdown(tree->right_, tree, filter);
            }
        } else if(tree->right_ != nullptr && filter->covered_var_id_.belongTo(tree->right_->operator_->maximal_varset_)){
            tree->right_ = FilterPushdown(tree->right_, tree, filter);
        } else if(parent != nullptr && parent->operator_->type_ == PQueryOperator::FILTER){
            dynamic_cast<FilterOperator*>(parent->operator_.get())->filters_.emplace_back(filter);
        } else {
            std::vector<GPStore::Expression* >f;
            f.push_back(filter);
            tree = GenerateRelatedFilters(f, tree);
        }
    }
    return tree;
}

/**
 * @brief Rewrite a BGP Operator. Assume this BGP contain only path pattern, don't contain shortest pattern.
 * And assume that all properties constraints have been written in filters, only Label constrain occur in pattern.
 * Edge conflict may exist.
 * */
void PQueryTree::RewriteBGPOperator(BGPOperator * bgp){

    // rigid1 = (a:Person)-[]-(c:City), rigid2 = (a:Student)
    // then rigid2 is duplicated single node
    std::map<unsigned, GPStore::NodePattern *> id2node;
    std::map<unsigned, unsigned > cnt;
    std::map<unsigned, std::vector<std::string>> id2labels;
    for(auto & rigid : bgp->pattern_){
        for(auto & node : rigid->nodes_){
            if(id2labels.find(node->var_id_) == id2labels.end()){
                id2labels.emplace(std::make_pair(node->var_id_, std::vector<std::string>()));
            }
            auto it = id2labels.find(node->var_id_);
            for(auto & l : node->labels_)
                if(std::find(it->second.begin(),it->second.end(),l) == it->second.end())
                    it->second.emplace_back(l);
            node->labels_.clear();
            auto it2 = cnt.find(node->var_id_);
            if(it2 == cnt.end()){
                cnt.insert(std::make_pair(node->var_id_, 1));
            } else {
                it2->second++;
            }
        }
    }
    //// Firstly, remove duplicated single Nodes
    for(auto & rigid: bgp->pattern_){
        if(rigid != nullptr && rigid->covered_var_id_.getVarsetSize() == 1 && cnt.at(rigid->nodes_[0]->var_id_) > 1){
            rigid.reset(nullptr);
        }
    }
    /// Second, write Label to first occur
    for(auto & rigid :bgp->pattern_){
        if(rigid != nullptr){
            for(auto & n : rigid->nodes_){
                if(id2node.find(n->var_id_) == id2node.end()){
                    id2node.insert(std::make_pair(n->var_id_, n.get()));
                }
            }
        }
    }
    for(auto & n_labels : id2labels){
        id2node.at(n_labels.first)->labels_ = n_labels.second;
    }
    /// lastly, remove duplicated nullptr;
    std::vector<std::unique_ptr<GPStore::RigidPattern>> pattern_;
    for(auto & rigid : bgp->pattern_){
        if(rigid != nullptr)
            pattern_.emplace_back(rigid.release());
    }
    bgp->pattern_.swap(pattern_);
    return;
}

/**
 * @brief Merge some BGPs. Merge their Patterns, Filters, and Edge Conflicts.
 * @warning After the call, all bgps will be deleted.
 * */
BGPOperator * PQueryTree::MergeBGP(std::vector<BGPOperator *>& bgp){
    if(bgp.empty()) return nullptr;
    if(bgp.size() == 1) return bgp[0];

    BGPOperator *total = new BGPOperator;
    for(auto small_bgp : bgp){
        for(auto & pat : small_bgp->pattern_){
            total->pattern_.emplace_back(pat.release());
        }
        for(auto & filter : small_bgp->filters_){
            total->filters_.emplace_back(filter.release());
        }
        total->edge_conflict_ += small_bgp->edge_conflict_;
        delete small_bgp;
    }
    return total;
}

/**
 * @brief Partition a BGP to Connected Components: e.g. BGP => BGP1 AND BGP2 AND BGP3.
 * Filters will be done as early as possible.
 * @param bgp Total BGP, may contain some patterns, filters, shortest_paths, edge_conflicts.
 * @param tree Plan Tree that we already have
 * @return Root of the plan tree.
 * @warning the parameter bgp will be modified.
 */
PTreeNode * PQueryTree::SplitBGPByConnectedComponent(BGPOperator *bgp, PTreeNode * tree){
    std::vector<GPStore::Expression *> filters;
    std::vector<std::unique_ptr<BGPOperator>> conn_comp;
    std::vector<std::unique_ptr<GPStore::RigidPattern>> shortest;
    std::unique_ptr<PTreeNode> new_node;
    /// filters
    for(auto & f : bgp->filters_){
        filters.push_back(f.release());
    }
    bgp->filters_.clear();
    /// ShortestPath
    for(auto & s : bgp->pattern_){
        if(s->type_ != GPStore::RigidPattern::PATH){
            shortest.emplace_back(s.release());
        }
    }
    RemoveNullPtr(bgp->pattern_);
    auto cc = CalculateBGPConnectedComponent(bgp);
    std::unique_ptr<std::map<unsigned,unsigned>> connected_comp_id(cc.first);
    unsigned cc_n = cc.second;

    // Split Rigid Pattern
    for(int i = 0; i < (int)cc_n; i++)
        conn_comp.emplace_back(new BGPOperator);
    for(auto & rigid : bgp->pattern_){
        unsigned cc_id = connected_comp_id->at(rigid->covered_var_id_.vars[0]);
        if(rigid->type_ == GPStore::RigidPattern::PATH){
            conn_comp[cc_id]->maximal_varset_ += rigid->covered_var_id_;
            conn_comp[cc_id]->pattern_.emplace_back(rigid.release());
        }
    }
    // Edge Conflict
    for(auto & edge_conf : bgp->edge_conflict_.vars){
        if(connected_comp_id->at(edge_conf.first) != connected_comp_id->at(edge_conf.second)){
            filters.push_back(GPStore::Expression::VarNonEqualToExpression(id2var_name_->at(edge_conf.first),
                                                                           id2var_name_->at(edge_conf.second),
                                                                           edge_conf.first, edge_conf.second));
        }
        else {
            conn_comp[connected_comp_id->at(edge_conf.first)]->edge_conflict_.addVar(edge_conf);
        }
    }

    // Rewrite BGP CC, e.g. BGP{ (a)-[b]-(c), (c:Person) } = BGP{ (a)-[b]-(c:Person) }
    for(auto & conn : conn_comp){
        RewriteBGPOperator(conn.get());
    }

    /// Heuristic Algorithm
    /// First, BGP that has common var with tree
    for(auto & conn : conn_comp){
        if(conn != nullptr && tree != nullptr && conn->maximal_varset_.hasCommonVar(tree->operator_->maximal_varset_)){
            // duplicated single node
            if(conn->pattern_.empty() || (conn->pattern_.size() == 1 && conn->pattern_[0]->nodes_.size() == 1
            && conn->pattern_[0]->nodes_[0]->constraintEmpty())){
                conn.reset(nullptr);
                continue;
            }
            // This BGP has pattern, edge conflict.
            new_node.reset(new PTreeNode);
            new_node->operator_.reset(conn.release());
            tree = GenerateBinaryOperator(tree, new_node.release(), PQueryOperator::AND);
            tree = GenerateRelatedFilters(filters, tree);
        }
    }
    /// Second, ShortestPath that belong to the tree varset
    for(auto & s : shortest){
        if(s != nullptr && tree != nullptr && tree->operator_->maximal_varset_.findVar(s->nodes_[0]->var_id_)
        && tree->operator_->maximal_varset_.findVar(s->nodes_[1]->var_id_)){
            tree = GenerateShortestPath(s.release(), tree);
        }
    }
    /// Third, shortestPath in single BGP
    for(auto & conn : conn_comp){
        if(conn == nullptr) continue;
        bool exists_ = false;
        for(auto & s : shortest){
            if(s != nullptr && s->covered_node_var_id_.belongTo(conn->maximal_varset_)){
                exists_ = true;
                break;
            }
        }
        if(!exists_) continue;
        new_node.reset(new PTreeNode);
        new_node->operator_.reset(conn.release());
        for(auto & s : shortest){
            if(s != nullptr  && s->covered_node_var_id_.belongTo(new_node->operator_->maximal_varset_)){
                new_node.reset(GenerateShortestPath(s.release(), new_node.release()));
            }
        }
        tree = GenerateBinaryOperator(tree, new_node.release(), PQueryOperator::AND);
        tree = GenerateRelatedFilters(filters, tree);
    }
    /// Forth, shortest path across two BGP
    for(auto & s : shortest){
        if(s == nullptr) continue;
        unsigned cc_id1 = connected_comp_id->at(s->nodes_[0]->var_id_);
        unsigned cc_id2 = connected_comp_id->at(s->nodes_[1]->var_id_);
        new_node.reset(new PTreeNode);
        new_node->operator_.reset(conn_comp.at(cc_id1).release());
        auto new_node2 = new PTreeNode;
        new_node2->operator_.reset(conn_comp.at(cc_id2).release());
        new_node.reset(GenerateBinaryOperator(new_node.release(), new_node2, PQueryOperator::AND));
        new_node.reset(GenerateRelatedFilters(filters, new_node.release()));
        new_node.reset(GenerateShortestPath(s.release(), new_node.release()));
        tree = GenerateBinaryOperator(tree, new_node.release(), PQueryOperator::AND);
        tree = GenerateRelatedFilters(filters, tree);
    }
    /// Fifth, do remained BGP
    for(auto & conn : conn_comp){
        if(conn != nullptr){
            new_node.reset(new PTreeNode);
            new_node->operator_.reset(conn.release());
            tree = GenerateBinaryOperator(tree, new_node.release(), PQueryOperator::AND);
            tree = GenerateRelatedFilters(filters, tree);
        }
    }
    return tree;
}

/**
 * @brief Calculate Connected Component for a BGP.
 * @param bgp Pointer to BGPOperator
 * @return which connected component a var belong to && num of connected components
 * */
std::pair<std::map<unsigned, unsigned> *, unsigned>
PQueryTree::CalculateBGPConnectedComponent(const BGPOperator *bgp){
    PVarset<unsigned> vars;

    for(const auto & pat : bgp->pattern_){
        vars += pat->covered_var_id_;
    }
    std::map<unsigned, std::set<unsigned>> adj;
    for(unsigned var : vars.vars)
        adj.emplace(std::make_pair(var, std::set<unsigned>()));

    for(const auto & pat : bgp->pattern_){
        if(pat->covered_var_id_.getVarsetSize() == 0) assert(false);

        unsigned n = pat->covered_var_id_.vars.size();

        int v = pat->covered_var_id_.vars[0];
        for(unsigned i = 1; i < n; ++i){
            int u = pat->covered_var_id_.vars[i];
            adj[u].insert(v);
            adj[v].insert(u);
        }
    }

    return calculateGraphConnectedComponent(adj);
}

/**
 * @brief Generate a Cypher Union Operator to connect left, right subtree.
 * @param left left sub-tree
 * @param right right sub-tree
 * @return the plan tree that joins left and right by Cypher Union
 * */
PTreeNode * PQueryTree::GenerateCypherUnion(PTreeNode *left, PTreeNode *right){
    PTreeNode * new_node = new PTreeNode;
    UnionOperator * union_op = new UnionOperator(UnionOperator::CYPHER_UNION);
    if(right != nullptr)
        union_op->maximal_varset_ = right->operator_->maximal_varset_;
    new_node->operator_.reset(union_op);
    new_node->left_ = left;
    new_node->right_ = right;
    return new_node;
}

/**
 * @brief Generate a Distinct Operator.
 * @param tree Plan tree that we already have.
 * @return The plan tree ends with Distinct.
 * */
PTreeNode * PQueryTree::GenerateDistinct(PTreeNode *tree){
    PTreeNode * new_node = new PTreeNode;
    ModifierOperator * modifier = new ModifierOperator;
    modifier->distinct_ = true;
    if(tree != nullptr)
        modifier->maximal_varset_ = tree->operator_->maximal_varset_;
    new_node->operator_.reset(modifier);
    new_node->left_ = tree;
    return new_node;
}

/**
 * @brief Generate Related Filters. The filters that were done will be removed.
 * @param filters the filters to be done.
 * @param tree Plan tree that we already have.
 * @return The plan tree
 * */
PTreeNode * PQueryTree::GenerateRelatedFilters(std::vector<GPStore::Expression *> &filters, PTreeNode *tree){
    if(tree == nullptr) return tree;
    std::vector<GPStore::Expression *> remain_;
    std::vector<GPStore::Expression *> can_do;
    for(auto exp : filters){
        if(exp->covered_var_id_.belongTo(tree->operator_->maximal_varset_)){
            can_do.push_back(exp);
        }else{
            remain_.push_back(exp);
        }
    }
    if(!can_do.empty()){
        auto filter = new FilterOperator;
        for(auto exp : can_do){
            filter->filters_.emplace_back(exp);
        }
        filter->maximal_varset_ = tree->operator_->maximal_varset_;
        auto new_node = new PTreeNode;
        new_node->operator_.reset(filter);
        new_node->left_ = tree;
        tree = new_node;
    }
    filters.swap(remain_);
    return tree;
}

PTreeNode * PQueryTree::GenerateBinaryOperator(PTreeNode *left, PTreeNode *right, PQueryOperator::OperatorType op){
    if(left == nullptr) return right;
    if(right == nullptr) return left;
    std::unique_ptr<PTreeNode> new_node(new PTreeNode);
    if(op == PQueryOperator::AND){
        auto and_op = new AndOperator;
        and_op->maximal_varset_ = left->operator_->maximal_varset_ + right->operator_->maximal_varset_;
        new_node->operator_.reset(and_op);
    } else if(op == PQueryOperator::UNION){
        auto union_op = new UnionOperator;
        union_op->maximal_varset_ = left->operator_->maximal_varset_ + right->operator_->maximal_varset_;
        new_node->operator_.reset(union_op);
    } else if(op == PQueryOperator::MINUS){
        auto minus_op = new MinusOperator;
        minus_op->maximal_varset_ = left->operator_->maximal_varset_ + right->operator_->maximal_varset_;
        new_node->operator_.reset(minus_op);
    } else if(op == PQueryOperator::OPTIONAL){
        auto optional = new OptionalOperator;
        optional->maximal_varset_ = left->operator_->maximal_varset_ + right->operator_->maximal_varset_;
        new_node->operator_.reset(optional);
    }
    new_node->left_ = left;
    new_node->right_ = right;
    return new_node.release();
}

PTreeNode * PQueryTree::GenerateShortestPath(GPStore::RigidPattern *rigid_pattern, PTreeNode * tree){
    if(rigid_pattern == nullptr || tree == nullptr) return tree;
    std::unique_ptr<PTreeNode> new_node(new PTreeNode);
    std::unique_ptr<ShortestPathOperator> shortest(new ShortestPathOperator);
    if(rigid_pattern->is_anno_var_){
        shortest->path_var_id_ = INVALID;
    } else {
        shortest->path_var_id_ = rigid_pattern->var_id_;
    }
    shortest->src_ = rigid_pattern->nodes_[0]->var_id_;
    shortest->tgt_ = rigid_pattern->nodes_[1]->var_id_;
    shortest->edge_pattern_.reset(rigid_pattern->edges_[0].release());
    shortest->maximal_varset_ = tree->operator_->maximal_varset_ + rigid_pattern->covered_var_id_;
    delete rigid_pattern;
    new_node->operator_.reset(shortest.release());
    new_node->left_ = tree;
    return new_node.release();
}


void PQueryTree::_dfs_label(unsigned u, const std::map<unsigned, std::set<unsigned>>& adj, std::map<unsigned, unsigned> & labels, unsigned cur_label ){
    if(labels[u] != 0xffffffffU) return;
    labels[u] = cur_label;
    for(unsigned v : adj.at(u)){
        if(labels[v] == 0xffffffffU)
            _dfs_label(v, adj, labels, cur_label);
    }
    return;
}

/**
 * @brief Calculate connected components of a directed graph
 * @param adj the adjacent list of the graph, adj.size() = var_num
 * @return which connected component a node belong to && # ConnectedComponent
 */
std::pair<std::map<unsigned, unsigned> *, unsigned>
PQueryTree::calculateGraphConnectedComponent(const std::map<unsigned, std::set<unsigned>>& adj){
    auto connected_comp_id = new std::map<unsigned, unsigned>();
    std::vector<unsigned> vars;
    unsigned UINF = 0xffffffff, cnt = 0;
    for(const auto & p : adj){
        connected_comp_id->emplace(std::make_pair(p.first, UINF));
        vars.push_back(p.first);
    }

    for(unsigned i = 0; i < vars.size(); ++i){
        if((*connected_comp_id)[vars[i]] == UINF){
            _dfs_label(vars[i], adj, *connected_comp_id, cnt);
            ++cnt;
        }
    }
    return std::make_pair(connected_comp_id, cnt);
}
