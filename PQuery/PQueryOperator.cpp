#include "PQueryOperator.h"
#include <algorithm>
#include <cassert>

/* helper functions */

void _dfs_label(unsigned u, const std::map<unsigned, std::set<unsigned>>& adj, std::map<unsigned, unsigned> & labels, unsigned cur_label ){
    if(labels[u] != 0xffffffffU) return;
    labels[u] = cur_label;
    for(unsigned v : adj.at(u)){
        if(labels[v] == 0xffffffffU)
            _dfs_label(v, adj, labels, cur_label);
    }
    return;
}

/**
 * @brief Calculate connected components of a undirected graph
 * @param adj the adjacent list of the graph, adj.size() = var_num
 * @return which connected component a node belong to
 */
std::pair<std::map<unsigned, unsigned> *, unsigned> calculateConnectedComponent(const std::map<unsigned, std::set<unsigned>>& adj){
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


PQueryOperator::PQueryOperator():left_(nullptr), right_(nullptr), parent_(nullptr), 
skip(0), limit(0xffffffff), distinct_(false), unwind_var_id_(0xffffffff), src_(0xffffffff), 
tgt_(0xffffffff), path_var_id_(0xffffffff){

}

PQueryOperator::PQueryOperator(OperatorType op_type):left_(nullptr), right_(nullptr), parent_(nullptr),
skip(0), limit(0xffffffff), distinct_(false), unwind_var_id_(0xffffffff), src_(0xffffffff), 
tgt_(0xffffffff), path_var_id_(0xffffffff){
    type_ = op_type;
}

PQueryOperator::PQueryOperator(const PQueryOperator& that): type_(that.type_), left_(nullptr), right_(nullptr), parent_(nullptr){
    if(type_ == BGP){
        pattern_ = that.pattern_;
        edge_conflict_ = that.edge_conflict_;
    }
    else if(type_ == UNION){
        union_ty_ = that.union_ty_;
    } else if(type_ == SHORTEST_PATH){
        is_all_shortest_ = that.is_all_shortest_;
        src_ = that.src_;
        tgt_ = that.tgt_;
        path_var_id_ = that.path_var_id_;
        edge_pattern_ = that.edge_pattern_;
    } else if(type_ == PROJECTION){
        proj_exps_ = that.proj_exps_;
        var_id_ = that.var_id_;
    } else if(type_ == ORDER_BY){
        order_exps_ = that.order_exps_;
        ascending_ = that.ascending_;
        skip = that.skip;
        limit = that.limit;
        distinct_ = that.distinct_;
    } else if(type_ == GROUP_BY){
        group_by_key_ = that.group_by_key_;
    } else if(type_ == AGGREGATION){
        group_by_key_ = that.group_by_key_;
        aggr_value_ = that.aggr_value_;
        aggr_value_var_id_  = that.aggr_value_var_id_;
    } else if(type_ == UNWIND){
        unwind_ .reset(new GPStore::Expression(*that.unwind_));
        unwind_var_id_ = that.unwind_var_id_;
    }
    filters_ = that.filters_;
}

PQueryOperator& PQueryOperator::operator=(const PQueryOperator& that){
    if(this == &that) return *this;

    type_ = that.type_;
    left_ =  right_ = parent_ = nullptr;
    if(type_ == BGP){
        pattern_ = that.pattern_;
        edge_conflict_ = that.edge_conflict_;
    }
    else if(type_ == UNION){
        union_ty_ = that.union_ty_;
    } else if(type_ == SHORTEST_PATH){
        is_all_shortest_ = that.is_all_shortest_;
        src_ = that.src_;
        tgt_ = that.tgt_;
        path_var_id_ = that.path_var_id_;
        edge_pattern_ = that.edge_pattern_;
    } else if(type_ == PROJECTION){
        proj_exps_ = that.proj_exps_;
        var_id_ = that.var_id_;
    } else if(type_ == ORDER_BY){
        order_exps_ = that.order_exps_;
        ascending_ = that.ascending_;
        skip = that.skip;
        limit = that.limit;
        distinct_ = that.distinct_;
    } else if(type_ == GROUP_BY){
        group_by_key_ = that.group_by_key_;
    } else if(type_ == AGGREGATION){
        group_by_key_ = that.group_by_key_;
        aggr_value_ = that.aggr_value_;
        aggr_value_var_id_  = that.aggr_value_var_id_;
    } else if(type_ == UNWIND){
        unwind_ .reset(new GPStore::Expression(*that.unwind_));
        unwind_var_id_ = that.unwind_var_id_;
    }
    filters_ = that.filters_;
    return *this;
}
    
PQueryOperator::~PQueryOperator(){
    if(left_ != nullptr)
        delete left_;
    if(right_ != nullptr)
        delete right_;
}

void PQueryOperator::print(int dep) const{
    return;
}

/**
 * @brief Clip output varset of this plan tree node. 
 * Save the clipped varset to minimal_varset.
*/
void PQueryOperator::clipVarset(const PVarset<unsigned> & required){
    if(left_ == nullptr && right_ == nullptr) {    
        minimal_varset_  = required * maximal_varset_;
        return;
    }

    if(type_ == BGP){
        minimal_varset_  = required * maximal_varset_;
        return;
    } else if(type_ == FILTER){
        PVarset<unsigned> filter_required;
        for(const auto & e : filters_){
            filter_required += e.covered_var_id_;
        }
        left_->clipVarset(filter_required + required);
        minimal_varset_ = left_->minimal_varset_ * required;
    } else if(type_ == AND || type_ == OPTIONAL || type_ == MINUS ||
    (type_ == UNION && union_ty_ == SPARQL_UNION) ){// 4 binary-operators
        PVarset<unsigned> binop_required = left_->maximal_varset_ * right_->maximal_varset_;
        binop_required += required;
        left_->clipVarset(binop_required);
        right_->clipVarset(binop_required);
        minimal_varset_ = (left_->minimal_varset_ + right_->minimal_varset_) * required;
    } else if(type_ == UNION && (union_ty_ == CYPHER_UNION || union_ty_ == CYPHER_UNION_ALL)){
        // Control flow should never reach here.
        assert(false);
    } else if(type_ == PROJECTION){
        PVarset<unsigned> proj_required;
        int n = proj_exps_.size();
        for(int i = 0; i < n; ++i){
            if(required.findVar(var_id_[i])){
                proj_required += proj_exps_[i].covered_var_id_;
            }
        }
        left_->clipVarset(proj_required);
        minimal_varset_ = PVarset<unsigned>(var_id_) * required;
    } else if(type_ == SHORTEST_PATH){
        PVarset<unsigned> shortest_required;
        shortest_required.addVar(src_);
        shortest_required.addVar(tgt_);
        left_->clipVarset(shortest_required + required);
        minimal_varset_ = left_->minimal_varset_;
        if(required.findVar(path_var_id_))
            minimal_varset_.addVar(path_var_id_);
        if(required.findVar(edge_pattern_.var_id_))
            minimal_varset_.addVar(edge_pattern_.var_id_);
        minimal_varset_ = minimal_varset_ * required;
    } else if(type_ == ORDER_BY || type_ == GROUP_BY){
        left_->clipVarset(required);
        minimal_varset_ = left_->minimal_varset_;
    } else if(type_ == AGGREGATION){
        PVarset<unsigned> aggr_required;
        PVarset<unsigned> required_remove;
        int n = aggr_value_.size();
        for(int i = 0; i < n; ++i){
            if(required.findVar(aggr_value_var_id_[i])){
                aggr_required += aggr_value_[i].covered_var_id_;
                required_remove.addVar(aggr_value_var_id_[i]);
            } 
        }
        left_->clipVarset(aggr_required + (required - required_remove));
        minimal_varset_ = (left_->minimal_varset_ + PVarset<unsigned>(aggr_value_var_id_) ) *required;
    } else if(type_ == UNWIND){
        PVarset<unsigned> unwind_required = unwind_->covered_var_id_;
        left_->clipVarset(unwind_required + required);
        minimal_varset_ = (left_->minimal_varset_ + unwind_var_id_) * required;
    }
    return;
}


/**
 * @brief Merge two BGPs and their edge conflict and filters are remained.
 *  */
PQueryOperator * PQueryOperator::mergeBGP(const std::vector<PQueryOperator *>& bgps){
    std::unique_ptr<PQueryOperator> total_bgp(new PQueryOperator(BGP));
    for(auto bgp : bgps){
        for(const auto & rigid : bgp->pattern_){
            total_bgp->pattern_.emplace_back(rigid);
        }
        total_bgp->edge_conflict_ += bgp->edge_conflict_;
        for(const auto & exp : bgp->filters_){
            total_bgp->filters_.emplace_back(exp);
        }
    }
    return total_bgp.release();
}

/**
 * @brief Merge two Filters .
 */
PQueryOperator * PQueryOperator::mergeFilter(const PQueryOperator *filter1, const PQueryOperator *filter2){
    std::unique_ptr<PQueryOperator> filter(new PQueryOperator(FILTER));
    for(const auto & exp : filter1->filters_)
        filter->filters_.emplace_back(exp);
    for(const auto & exp : filter2->filters_)
        filter->filters_.emplace_back(exp);
    return filter.release();
}

/**
 * @brief Partition a BGP to Connected Components: e.g. BGP => BGP1 AND BGP2 AND BGP3.
 * Filters will be done as early as possible.
 * @param bgp Total BGP, may contain some filters.
 * @param root Plan Tree that we already have
 * @param filter other filters about the bgp
 * @return Root of the plan tree.
 * @warning the parameter bgp will be modified.
 */
PQueryOperator * PQueryOperator::partitionConnectedComponent(PQueryOperator *bgp,  PQueryOperator *root, const PQueryOperator *filter){
    std::vector<std::unique_ptr<GPStore::Expression>> edge_conf_filters;    // auto delete
    std::set<const GPStore::Expression *> filters;    // should not delete exp
    std::vector<std::unique_ptr<PQueryOperator>> connected_comp;    // set nullptr if done
    std::set<const GPStore::RigidPattern *> shortest_path_pattern; // should not delete rigid
    

    // Writing Constraint of shortestPath node to its first occur
    rewriteShortestPathPattern(bgp);
    
    // Consider filters
    for(const auto &exp : bgp->filters_){
        filters.insert(&exp);
    }
    if(filter != nullptr){
        for(const auto & exp : filter->filters_){
            filters.insert(&exp);
        }
    }
    
    // get connected components
    auto cc = calculateVarConnectedComponent(bgp);
    std::unique_ptr<std::map<unsigned,unsigned>> connected_comp_id(cc.first);
    unsigned cc_n = cc.second;

    // Consider Rigid Pattern && shortestPath
    for(int i = 0; i < (int)cc_n; i++)
        connected_comp.emplace_back(new PQueryOperator(BGP));
    for(int i = 0; i < bgp->pattern_.size(); ++i){
        if(bgp->pattern_[i].type_ == GPStore::RigidPattern::PATH){
            connected_comp[connected_comp_id->at(bgp->pattern_[i].covered_var_id_.vars[0])]
            ->pattern_.emplace_back(bgp->pattern_[i]);
        } else {
            shortest_path_pattern.insert(&bgp->pattern_[i]);
        }
    }

    for(auto &bgp_c : connected_comp){
        for(const auto & rigid : bgp_c->pattern_){
            bgp_c->maximal_varset_ += rigid.covered_var_id_;
        }
    }

    // Consider edge conflict 
    for(const auto & p : bgp->edge_conflict_.vars){
        if((*connected_comp_id)[p.first] == (*connected_comp_id)[p.second]){
            connected_comp[connected_comp_id->at(p.first)]->edge_conflict_.addVar(p);
        } else {
            edge_conf_filters.emplace_back(edgeConflictToExpression(p.first, p.second));
            filters.insert(edge_conf_filters.back().get());
        }
    }

    // All prepare work was done. Now, we need to join root, bgps, filters, shortestPaths
    // Firstly, Join the bgp that have commom var with root, and do filters among them
    if(root != nullptr){
        for(auto &bgp : connected_comp){
            if(bgp!= nullptr && !bgp->maximal_varset_.hasCommonVar(root->maximal_varset_))
                continue;

            /* find a bgp that has common var with root */
            auto bgp_ptr = bgp.release(), tmp = new PQueryOperator(AND);
            bgp.reset(nullptr);
            tmp->left_ = root;
            tmp->right_ = bgp_ptr;
            tmp->maximal_varset_ = root->maximal_varset_ + bgp->maximal_varset_;
            root = tmp;
            
            /* consider related filters*/
            root = generateRelatedFilters(root, filters);
        }
    }
    // Then, do the shortestQuery: not optimal, just a simple implementation
    for(auto shortest : shortest_path_pattern){
        unsigned src = shortest->nodes_[0].var_id_;
        unsigned tgt = shortest->nodes_[1].var_id_;
        if(root == nullptr || !root->maximal_varset_.findVar(src)){
            PQueryOperator *bgp = nullptr;
            for(auto &bgp_comp : connected_comp){
                if(bgp_comp != nullptr && bgp_comp->maximal_varset_.findVar(src)){
                    bgp = bgp_comp.release();
                    bgp_comp.reset(nullptr);
                    break;
                }
            }
            if(bgp == nullptr) assert(false);
            root = generateBinaryOperator(root, bgp, AND);
            root = generateRelatedFilters(root ,filters);    
        }

        if(!root->maximal_varset_.findVar(tgt)){
            PQueryOperator *bgp = nullptr;
            for(auto &bgp_comp : connected_comp){
                if(bgp_comp != nullptr && bgp_comp->maximal_varset_.findVar(src)){
                    bgp = bgp_comp.release();
                    bgp_comp.reset(nullptr);
                    break;
                }
            }
            if(bgp == nullptr) assert(false);
            root = generateBinaryOperator(root, bgp, AND);
            root = generateRelatedFilters(root ,filters);
        }

        root =generateShortestPath(root, *shortest);
    }

    // Finally, Join the remained bgp and filters
    for(auto &bgp_comp : connected_comp){
        if(bgp_comp != nullptr){
            root = generateBinaryOperator(root, bgp_comp.release(), AND);
            root = generateRelatedFilters(root, filters);
        }
    }
    return root;
} 

std::pair<std::map<unsigned, unsigned> *, unsigned>
PQueryOperator::calculateVarConnectedComponent(const PQueryOperator *bgp){
    PVarset<unsigned> vars;
    
    for(const auto & pat : bgp->pattern_){
        vars += pat.covered_var_id_;
    }
    std::map<unsigned, std::set<unsigned>> adj;
    for(unsigned var : vars.vars)
        adj.emplace(std::make_pair(var, std::set<unsigned>()));

    for(const auto & pat : bgp->pattern_){
        if(pat.covered_var_id_.getVarsetSize() == 0) assert(false);

        unsigned n = pat.covered_var_id_.vars.size();

        int v = pat.covered_var_id_.vars[0];
        for(unsigned i = 1; i < n; ++i){
            int u = pat.covered_var_id_.vars[i];        
            adj[u].insert(v);
            adj[v].insert(u);
        }
    }

    return calculateConnectedComponent(adj);
}

GPStore::Expression * 
PQueryOperator::edgeConflictToExpression(unsigned e1, unsigned e2){
    GPStore::Variable * a = new GPStore::Variable();
    GPStore::Variable * b = new GPStore::Variable();
    a->id_ = e1;
    b->id_ = e2;
    a->covered_var_id_.addVar(e1);
    b->covered_var_id_.addVar(e2);
    GPStore::Expression *exp1 = new GPStore::Expression();
    GPStore::Expression *exp2 = new GPStore::Expression();
    exp1->atom_ = dynamic_cast<GPStore::Atom*>(a);
    exp2->atom_ = dynamic_cast<GPStore::Atom*>(b);
    exp1->covered_var_id_.addVar(e1);
    exp2->covered_var_id_.addVar(e2);
    GPStore::Expression *exp = new GPStore::Expression();
    
    exp->oprt_ = GPStore::Expression::AND;
    exp->children_.push_back(exp1);
    exp->children_.push_back(exp2);
    exp->covered_var_id_.addVar(e1);
    exp->covered_var_id_.addVar(e2);
    return exp;
}

GPStore::Expression *
PQueryOperator::propertyEqualityToExpression(unsigned var_id, const std::string & prop_name, unsigned prop_id, const GPStore::Expression & prop_val){
    GPStore::Expression * exp = new GPStore::Expression();
    GPStore::Variable * var = new GPStore::Variable();
    var->id_ = var_id;
    var->covered_var_id_.addVar(var->id_);
    exp->oprt_ = GPStore::Expression::EQUAL;
    exp->children_.push_back(new GPStore::Expression());
    exp->children_.back()->atom_ = dynamic_cast<GPStore::Atom*>(var);
    exp->children_.back()->property_label_ = new GPStore::AtomPropertyLabels();
    exp->children_.back()->property_label_->addKeyName(prop_name);
    exp->children_.back()->property_label_->prop_id_ = prop_id;
    exp->children_.back()->covered_props_.addVar(std::make_pair(var_id, prop_id));
    exp->children_.back()->covered_var_id_.addVar(var_id);
    exp->children_.push_back(new GPStore::Expression(prop_val));
    exp->covered_props_ = exp->children_[0]->covered_props_ + exp->children_[1]->covered_props_;
    exp->covered_var_id_ = exp->children_[0]->covered_var_id_ + exp->children_[1]->covered_var_id_;
    return exp;
}

GPStore::Expression * 
PQueryOperator::varIdToExpression(unsigned var_id){
    GPStore::Variable * var = new GPStore::Variable();
    GPStore::Expression *exp = new GPStore::Expression();
    var->id_ = var_id;
    var->covered_var_id_.addVar(var_id);
    exp->covered_var_id_.addVar(var_id);
    exp->atom_ = dynamic_cast<GPStore::Atom*>(var);
    return exp;
}

/**
 * @brief ReWrite ShortestPath Pattern of a BGP, such that src node and tgt node of the ShortestPath Pattern dont have any constraint. 
 * For example, (a), (c), shortestPath((a {name:'A'})-[*]-(c:Person)). 
 * => (a {name:'A'}), (c:Person), shortestPath((a)-[*]-(c))
 * @warning this function may extract property constraint to bgp->filters_
*/
void
PQueryOperator::rewriteShortestPathPattern(PQueryOperator *bgp){
    std::map<unsigned, GPStore::NodePattern*> varid2node_;
    // get first occurance
    for(auto &pat : bgp->pattern_){
        if(pat.type_ == GPStore::RigidPattern::PATH){
            for(auto &node : pat.nodes_){
                if(varid2node_.find(node.var_id_) == varid2node_.end()){
                    varid2node_.insert(std::make_pair(node.var_id_, &node));
                }
            }
        }
    }
    // rewrite path pattern
    for(auto &pat: bgp->pattern_){
        if(pat.type_ == GPStore::RigidPattern::PATH) continue;
        for(auto & node : pat.nodes_){
            if( node.constraintEmpty()) continue;
            auto it = varid2node_.find(node.var_id_);
            if(it != varid2node_.end()){
                auto node_ptr = it->second;
                for(auto & label : node.labels_){
                    if(std::find(node_ptr->labels_.begin(), node_ptr->labels_.end(),label) == node_ptr->labels_.end()) 
                        node_ptr->labels_.emplace_back(label);
                }
                for(auto &p : node.properties_){
                    if(node_ptr->properties_.find(p.first) == node_ptr->properties_.end()){
                        node_ptr->properties_.emplace(p);
                        node_ptr->prop_id_.emplace(std::make_pair(p.first, node.prop_id_.at(p.first)));
                    } else {
                        auto filter_exp = propertyEqualityToExpression(node.var_id_,p.first, node.prop_id_.at(p.first),p.second);
                        bgp->filters_.emplace_back(*filter_exp);
                        delete filter_exp;
                    }
                }
            } else {
                // add a node as a path pattern(length = 0)
                bgp->pattern_.emplace_back(node);
            }
            node.prop_id_.clear();
            node.properties_.clear();
            node.labels_.clear();
        }   
    }

}   

PQueryOperator *
PQueryOperator::generateRelatedFilters(PQueryOperator *root, std::set<const GPStore::Expression *> & filters){
    std::vector<const GPStore::Expression *> related_filters;
    for(auto filter_exp : filters){
        if(filter_exp->covered_var_id_.belongTo(root->maximal_varset_)){
            related_filters.push_back(filter_exp);
        }
    }
    if(related_filters.size()){
        auto tmp = new PQueryOperator(PQueryOperator::FILTER);
        tmp->left_ = root;
        for(auto filter_exp : related_filters){
            tmp->filters_.emplace_back(*filter_exp);
        }
        tmp->maximal_varset_ = root->maximal_varset_;
        root = tmp;
        // remove the filters that we've done.
        for(auto filter_exp : related_filters)
            filters.erase(filter_exp);
    }
    return root;
}

PQueryOperator *
PQueryOperator::generateBinaryOperator(PQueryOperator *left, PQueryOperator *right, PQueryOperator::OperatorType op){
    if(left == nullptr) return right;
    if(right == nullptr) return left;
    PQueryOperator *root = new PQueryOperator(op);
    root->left_ = left;
    root->right_ = right;
    root->type_ = op;
    return root;
}

PQueryOperator * 
PQueryOperator::generateShortestPath(PQueryOperator *root, const GPStore::RigidPattern &pattern){
    PQueryOperator *tmp = new PQueryOperator(SHORTEST_PATH);
    tmp->is_all_shortest_ = (pattern.type_ == GPStore::RigidPattern::ALL_SHORTEST_PATHS);
    tmp->src_ = pattern.nodes_[0].var_id_;
    tmp->tgt_ = pattern.nodes_[1].var_id_;
    tmp->edge_pattern_ = pattern.edges_[0];
    tmp->left_ = root;
    tmp->maximal_varset_ = root->maximal_varset_;
    if(pattern.is_anno_var_){
        tmp->path_var_id_ = 0xffffffffU;
    } else {
        tmp->path_var_id_ = pattern.var_id_;
        tmp->maximal_varset_.addVar(tmp->path_var_id_);
    }
    return tmp;
}
