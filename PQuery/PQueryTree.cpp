#include "PQueryTree.h"
#include <algorithm>
#include <cassert>
PQueryTree::PQueryTree(){
    root_ = nullptr;
    param_.reset(new std::unordered_map<std::string, GPStore::Value>());
}

PQueryTree::~PQueryTree(){
    if(root_ != nullptr)
        delete root_;
}

GPStore::Value PQueryTree::setParam(const std::string& param_name, const GPStore::Value &val){
    param_->emplace(param_name, val);
}

GPStore::Value PQueryTree::getParam(const std::string& param_name){
    return param_->at(param_name);
}

bool PQueryTree::existParam(const std::string& param_name){
    return param_->find(param_name) != param_->end();
}


/**
 * @brief generate a query tree for a cypher query
 * @return root of the plan tree
*/
void PQueryTree::GenerateQueryTree(const CypherAST* ast){
    mode_ = Cypher;
    id2var_name_ = ast->id2var_name_;
    prop2id_ = ast->prop2id_;
    prop_id2string_ = ast->prop_id2string_;
    if(ast->union_all_.size() == 0){
        root_ = GenerateQueryTree(ast->single_querys_[0].get());
        return;
    }

    int n = ast->union_all_.size();
    std::unique_ptr<PQueryOperator> tree;
    tree.reset(GenerateQueryTree(ast->single_querys_[0].get()));
    for(int i = 1; i <= n; ++i){
        PQueryOperator *right = GenerateQueryTree(ast->single_querys_[i].get());
        PQueryOperator *left = tree.release();
        tree.reset(new PQueryOperator(PQueryOperator::UNION));
        tree->left_ = left;
        tree->right_ = right;
        tree->union_ty_ = ast->union_all_[i - 1] ?
            PQueryOperator::CYPHER_UNION_ALL : PQueryOperator::CYPHER_UNION;
        tree->maximal_varset_ = tree->minimal_varset_ = right->minimal_varset_;
    }
    root_ = tree.release();
}

PQueryOperator * PQueryTree::GenerateQueryTree(const SingleQueryAST* ast){
    PQueryOperator * tree = nullptr;
    for(const auto & query_unit : ast->query_units_){
        tree = GenerateQueryTree(query_unit.get(), tree);
    }
    return tree;
}

/**
 * @brief generate a plan tree for a QueryUnit
 * @param ast a pointer to QueryUnitAST
 * @param tree plan tree that we already have
*/
PQueryOperator * PQueryTree::GenerateQueryTree(const QueryUnitAST* ast, PQueryOperator * tree){

    /// Handle reading clauses
    int n = (int)ast->reading_.size();
    for(int i = 0; i < n; ++i){
        auto & read = ast->reading_[i];
        if(read->reading_form_ == ReadingAST::MATCH &&
        dynamic_cast<MatchAST*>(read.get())->is_optional_ == false){
            int j = i;
            for(;j < n; ++j){
                if(ast->reading_[j]->reading_form_ != ReadingAST::MATCH ||
                dynamic_cast<MatchAST*>(ast->reading_[j].get())->is_optional_ )
                    break;
            }
            // Match Region i, i + 1, ..., j - 1 
            std::vector<PQueryOperator*> bgps;
            for(int k = i; k < j; ++k){
                MatchAST * match = dynamic_cast<MatchAST*>(ast->reading_[k].get());
                auto match_bgp = GenerateQueryTree(match);
                bgps.push_back(match_bgp);
            }
            PQueryOperator *total_bgp = PQueryOperator::mergeBGP(bgps);
            for(auto bgp : bgps) delete bgp;

            // now we only need to consider join tree && total_bgp
            tree = PQueryOperator::partitionConnectedComponent(total_bgp, tree);
            delete total_bgp;
            i = j; // iter i to j
        } else if(read->reading_form_ == ReadingAST::MATCH){
            // do optional match
            MatchAST * match = dynamic_cast<MatchAST*>(read.get());
            auto bgp = GenerateQueryTree(match);
            auto right = PQueryOperator::partitionConnectedComponent(bgp, nullptr);
            delete bgp;
            tree = PQueryOperator::generateBinaryOperator(tree ,right, PQueryOperator::OPTIONAL);

        } else if( read->reading_form_ == ReadingAST::UNWIND){
            tree = GenerateQueryTree(dynamic_cast<const UnwindAST *>(read.get()), tree);
        } else if( read->reading_form_ == ReadingAST::INQUERY_CALL){
            tree = GenerateQueryTree(dynamic_cast<const InQueryCallAST *>(read.get()), tree);
        }
    }

    /// TODO: Handle updating clauses

    /// Handle WithReturn
    tree = GenerateQueryTree(ast->with_return_.get(), tree);
    /// Clip by return clause
    if(ast->with_return_ == nullptr){
        tree->clipVarset(PVarset<unsigned>());
    } else if(!ast->with_return_->with_){
        tree->clipVarset(PVarset<unsigned>(ast->with_return_->column_var_id_));
    }
    return tree;
}

/**
 * @brief generate a BGP Operator, initialize pattern, edge conflict, filters, maximal_varset.
 * 
 * For a node pattern (:Person{name:'A', age: b.age}), age:b.age is not a literal, but 
 * is a filter between a and b.
 * @warning the filters in this BGP may contain vars that dont occur in this BGP. 
 * For example, the BGP (a)-[:KNOWS]-(b), can contain filter: a.age = c.age, even if c doesnt
 *  occur in this bgp. You should handle this case.
 * @param ast pointer to MatchAST
*/
PQueryOperator * PQueryTree::GenerateQueryTree(const MatchAST *ast){
    PQueryOperator *bgp = new PQueryOperator(PQueryOperator::BGP);
    std::unique_ptr<GPStore::Expression> exp;
    PVarset<unsigned> covered_edge_var;
    
    /* Extract filter in property map */
    for(const auto & pat : ast->pattern_){
        bgp->pattern_.emplace_back(pat);
        bgp->maximal_varset_ += pat.covered_var_id_;
        auto &rigid = bgp->pattern_.back();
        for(auto &node : rigid.nodes_){
            std::vector<std::string> erase_keys;
            for(auto &p : node.properties_){
                if(p.second.covered_var_id_.getVarsetSize()){
                    erase_keys.emplace_back(p.first);
                    exp.reset(PQueryOperator::propertyEqualityToExpression(node.var_id_, p.first, node.prop_id_.at(p.first), p.second));
                    bgp->filters_.emplace_back(*exp);
                }
            }
            for(auto & prop : erase_keys){
                node.properties_.erase(prop);
                node.prop_id_.erase(prop);
            }
        }
        for(auto &edge : rigid.edges_){
            std::vector<std::string> erase_keys;
            for(auto &p : edge.properties_){
                if(p.second.covered_var_id_.getVarsetSize()){
                    erase_keys.emplace_back(p.first);
                    exp.reset(PQueryOperator::propertyEqualityToExpression(edge.var_id_, p.first, edge.prop_id_.at(p.first), p.second));
                    bgp->filters_.emplace_back(*exp);
                }
            }
            for(auto & prop : erase_keys){
                edge.properties_.erase(prop);
                edge.prop_id_.erase(prop);
            }
        }
    }

    /* Handle Edge conflict */
    for(const auto & pat : ast->pattern_){
        if(pat.type_  == GPStore::RigidPattern::PATH){
            covered_edge_var += pat.covered_edge_var_id_;
        }
    }
    std::sort(covered_edge_var.vars.begin(), covered_edge_var.vars.end());
    unsigned n = covered_edge_var.getVarsetSize();
    for(unsigned i = 0; i < n; ++i){
        for(unsigned j = i + 1; j < n; ++j){
            bgp->edge_conflict_.addVar(std::make_pair(i, j));
        }
    }
    
    /* Handle filter in where clause */
    if(ast->where_ != nullptr){
        auto exps = GPStore::Expression::split(new GPStore::Expression(*ast->where_), GPStore::Expression::AND);
        for(auto split_exp : exps){
            bgp->filters_.emplace_back(*split_exp);
            delete split_exp;
        }
    }
    return bgp;
}

/**
 * @brief generate plan tree for a unwind clause
 * @param ast pointer to unwind AST
 * @param tree plan tree we already have
*/
PQueryOperator * PQueryTree::GenerateQueryTree(const UnwindAST* ast, PQueryOperator * tree){
    PQueryOperator * unwind = new PQueryOperator(PQueryOperator::UNWIND);
    unwind->unwind_.reset(new GPStore::Expression(*ast->exp_));
    unwind->unwind_var_id_ = ast->var_id_;
    if(tree == nullptr){
        unwind->maximal_varset_.addVar(unwind->unwind_var_id_);
    } else {
        unwind->left_ = tree;
        unwind->right_ = nullptr;
        unwind->maximal_varset_ = tree->maximal_varset_;
        unwind->maximal_varset_.addVar(unwind->unwind_var_id_);
    }
    return unwind;
}


PQueryOperator * PQueryTree::GenerateQueryTree(const InQueryCallAST* ast, PQueryOperator * tree){
    assert(false);
    return nullptr;
}

/**
 * @brief generate plan tree for a with/return clause
 * @param ast pointer to withreturn AST
 * @param tree plan tree we already have
*/
PQueryOperator * PQueryTree::GenerateQueryTree(const WithReturnAST* ast, PQueryOperator * tree){
    auto proj = new PQueryOperator(PQueryOperator::PROJECTION);
    std::unique_ptr<GPStore::Expression> tmp_exp;
    if(!ast->aggregation_){
        for(unsigned i : ast->implict_proj_var_id_){
            tmp_exp.reset(PQueryOperator::varIdToExpression(i));
            proj->proj_exps_.emplace_back(*tmp_exp);
            proj->var_id_.push_back(i);
        }
        int n = ast->proj_exp_.size();
        for(int i = 0; i < n; ++i){
            proj->proj_exps_.emplace_back(*(ast->proj_exp_[i]));
            proj->var_id_.push_back(ast->column_var_id_[i]);
        }
        proj->left_ = tree;
        proj->maximal_varset_ = proj->var_id_;
        tree = proj;
        
    } else {
        // We have to handle aggregation functions 
        auto group_by = new PQueryOperator(PQueryOperator::GROUP_BY);
        auto aggr = new PQueryOperator(PQueryOperator::AGGREGATION);
        for(unsigned i : ast->implict_proj_var_id_){
            tmp_exp.reset(PQueryOperator::varIdToExpression(i));
            proj->proj_exps_.emplace_back(*tmp_exp);
            proj->var_id_.push_back(i);
            group_by->group_by_key_.push_back(i);
        }
        int n = ast->proj_exp_.size();
        for(int i = 0; i < n; ++i){
            if(!ast->proj_exp_[i]->containsAggrFunc()){
                proj->proj_exps_.emplace_back(*ast->proj_exp_[i]);
                proj->var_id_.emplace_back(ast->column_var_id_[i]);
                group_by->group_by_key_.push_back(ast->column_var_id_[i]);
            } else {
                aggr->aggr_value_.emplace_back(*ast->proj_exp_[i]);
                aggr->aggr_value_var_id_.push_back(ast->column_var_id_[i]);
            }
        }
        proj->left_ = tree;
        proj->maximal_varset_ = proj->var_id_;
        group_by->left_ = proj;
        group_by->maximal_varset_ = proj->maximal_varset_;
        aggr->left_ = group_by;
        aggr->maximal_varset_ = proj->maximal_varset_ + PVarset<unsigned>(aggr->aggr_value_var_id_);
        tree = aggr;
    }
    
    if(ast->skip_ != nullptr || ast->limit_ != nullptr || ast->distinct_ ||
    ast->order_by_.size()){
        auto order_by = new PQueryOperator(PQueryOperator::ORDER_BY);
        if(ast->skip_){
            // Calculator Exp here!
        }
        if(ast->limit_){
            // Calculator Exp here!
        }
        if(ast->distinct_){
            order_by->distinct_ = true;
        }
        for(int i = 0; i < (int)ast->order_by_.size(); ++i){
            order_by->order_exps_.emplace_back(*ast->order_by_[i]);
            order_by->ascending_.push_back(ast->ascending_[i]);
        }
        order_by->left_ = tree;
        order_by->maximal_varset_ = tree->maximal_varset_;
        tree = order_by;
    }
    // Handle where clause [Filter].
    if(ast->where_){
        auto filter = new PQueryOperator(PQueryOperator::FILTER);
        filter->filters_.emplace_back(*ast->where_);
        filter->left_ = tree;
        filter->maximal_varset_ = tree->maximal_varset_;
        tree = filter;
    }
    return tree;
}