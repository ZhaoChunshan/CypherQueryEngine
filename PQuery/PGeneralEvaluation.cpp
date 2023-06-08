#include "PGeneralEvaluation.h"

#include <utility>
#include "BGPQuery.h"
//#include "../Optimizer/Query.h"
//
// Created by zcs on 5/23/23.
//

PGeneralEvaluation::PGeneralEvaluation(KVstore *_kvstore, StringIndex *_stringindex,
                                       const std::shared_ptr<std::unordered_map<std::string, GPStore::Value>> & _param,
                                       TYPE_TRIPLE_NUM *_pre2num,TYPE_TRIPLE_NUM *_pre2sub,
                                       TYPE_TRIPLE_NUM *_pre2obj, TYPE_TRIPLE_NUM _triples_num, TYPE_PREDICATE_ID _limitID_predicate,
                                       TYPE_ENTITY_LITERAL_ID _limitID_literal, TYPE_ENTITY_LITERAL_ID _limitID_entity,
                                       std::shared_ptr<Transaction> txn)
:kvstore_(_kvstore), stringindex_(_stringindex), param_(_param), pre2num(_pre2num), pre2sub(_pre2sub),
pre2obj(_pre2obj), triples_num(_triples_num), limitID_predicate(_limitID_predicate), limitID_literal(_limitID_literal),
limitID_entity(_limitID_entity), txn_(txn)
{
    cypher_parser_ = std::make_shared<PCypherParser>();
    optimizer_ = std::make_shared<Optimizer>();
}

bool PGeneralEvaluation::ParseCypherQuery(const std::string &_query){
    // clear both Cypher AST && SPARQL AST
    cypher_ast_.reset(nullptr);
    // Generate New AST
    try{
        cypher_ast_.reset(cypher_parser_->CypherParse(_query, param_, kvstore_));
    } catch(const std::exception& e1)
    {
        std::cerr <<e1.what() << std::endl;
        return false;
    }
    id2var_name_ = cypher_ast_->id2var_name_;
    return true;
}
bool PGeneralEvaluation::ParseCypherQuery(std::istream& in){
    // clear both Cypher AST && SPARQL AST
    cypher_ast_.reset(nullptr);
    // Generate New AST
    try{
        cypher_ast_.reset(cypher_parser_->CypherParse(in, param_, kvstore_));
    } catch(const std::exception& e1)
    {
        std::cerr <<e1.what() << std::endl;
        return false;
    }
    id2var_name_ = cypher_ast_->id2var_name_;

    return true;
}


bool PGeneralEvaluation::GenerateLogicalPlan(){
    // clear old Logical plan
    logical_plan_.reset(nullptr);
    // Generate new plan
    try{
        logical_plan_.reset(PQueryTree::GenerateQueryTree(cypher_ast_.get()));
    } catch(const std::exception& e1)
    {
        std::cerr <<e1.what() << std::endl;
        return false;
    }
    return true;
}

bool PGeneralEvaluation::DoQuery() {
    static const int NOT_DONE = 0, FINISH_LEFT = 1, FINISH_RIGHT = 2;
    std::vector<std::unique_ptr<EvaluationStackItem>> st;        // a stack
    st.emplace_back(new EvaluationStackItem(logical_plan_.get(), nullptr, NOT_DONE));
    std::unique_ptr<PTempResult> cur_result(new PTempResult);
    while (!st.empty()) {
        auto &item = *st.back();
        //auto &item = st[st.size() - 1];
        if (item.state_ == NOT_DONE) {
            if (item.node_->left_ != nullptr) {
                st.emplace_back(new EvaluationStackItem(item.node_->left_, nullptr, NOT_DONE));
            }
            item.state_ = FINISH_LEFT;
        } else if (item.state_ == FINISH_LEFT) {
            if (item.node_->right_ != nullptr) {
                item.result_ = (cur_result.release());
                cur_result.reset(new PTempResult);
                st.emplace_back(new EvaluationStackItem(item.node_->right_, nullptr, NOT_DONE));
            }
            item.state_ = FINISH_RIGHT;
        } else {
            std::unique_ptr<PTempResult> new_result(new PTempResult);
            // cur_result ====oprt===> new_result
            if(item.node_->operator_->type_ == PQueryOperator::BGP){
                EvaluateStepBGP(*new_result, dynamic_cast<BGPOperator*>(item.node_->operator_.get()),st, item.node_->operator_->minimal_varset_);
            }
            else if(item.node_->operator_->type_ == PQueryOperator::PROJECTION){
                ProjectionOperator *proj_oprt = dynamic_cast<ProjectionOperator *>(item.node_->operator_.get());
                std::vector<const GPStore::Expression *> proj_exps;
                for (auto &proj_exp: proj_oprt->proj_exps_) {
                    proj_exps.push_back(proj_exp.get());
                }
                cur_result->doProjection(proj_exps, proj_oprt->var_id_, (proj_oprt->minimal_varset_ - proj_oprt->var_id_).vars, kvstore_,
                                        param_.get());
                new_result.reset(cur_result.release());
            }
            else if (item.node_->left_ == nullptr || item.node_->right_ == nullptr) {
                EvaluateStep(cur_result, new_result, item.node_->operator_.get());
            }
            // left_result + cur_result ====oprt====> new_result
            else if (item.node_->left_ != nullptr && item.node_->right_ != nullptr) {
                std::unique_ptr<PTempResult> left_result(item.result_);
                item.result_ = nullptr;
                EvaluateStep(left_result, cur_result, new_result, item.node_->operator_.get());
            }

            cur_result.reset(new_result.release());
            st.pop_back();
        }
    }
    temp_result_.reset(cur_result.release());
    return true;
}

void PGeneralEvaluation::EvaluateStepBGP(PTempResult & new_result, BGPOperator *bgp_op, std::vector<std::unique_ptr<EvaluationStackItem>> & st, PVarset<unsigned > & selected_var){
    std::vector<unsigned > bgp_select;
    for(auto & pat : bgp_op->pattern_){
        bool all = !pat->is_anno_var_;
        for(auto & node : pat->nodes_){
            if(all || selected_var.findVar(node->var_id_)){
                new_result.head_.spo_var_.addVar(node->var_id_);
                bgp_select.push_back(node->var_id_);
            }
        }
        for(auto & edge: pat->edges_){
            if(all || selected_var.findVar(edge->var_id_)){
                if(edge->is_edge_length_v_){
                    new_result.head_.other_var_.addVar(edge->var_id_);
                } else {
                    new_result.head_.edge_var_.addVar(edge->var_id_);
                }
                bgp_select.push_back(edge->var_id_);

            }
        }
    }

    std::unique_ptr<BGPQueryNew> bgp(WritePatternToBGP(bgp_op, bgp_select));
//    bgp->print(kvstore_);
    // TODO: CALL Optimizer. GET intermedia Result
//    std::unique_ptr<Query> qu(new Query(kvstore_, pre2num, pre2sub, pre2obj, triples_num, limitID_predicate, limitID_literal, limitID_entity, bgp.get(), txn_));
//    qu->DoQuery();
    PIntermediateResult * intermedia = nullptr;
    copyIntermediaResult2TempResult(intermedia, &new_result);
    // TODO: Projection Path p = (a)-[]-(c)
}

void PGeneralEvaluation::EvaluateStep(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult>  & new_result,  PQueryOperator *oprt){
    // consider FILTER, MODIFIER,  UNWIND, CALL,
    // CREATE, DELETE, SET, REMOVE,  GROUP_BY, AGGREGATION,  SHORTEST_PATH
    std::string msg;
    for(auto var : oprt->minimal_varset_.vars){
        if(cur_result->head_.spo_var_.findVar(var))new_result->head_.spo_var_.addVar(var);
        else if(cur_result->head_.edge_var_.findVar(var)) new_result->head_.edge_var_.addVar(var);
        else if(cur_result->head_.other_var_.findVar(var)) new_result->head_.other_var_.addVar(var);
    }
    if (oprt->type_ == PQueryOperator::FILTER) {
        std::vector<GPStore::Expression *> exps;
        for (auto &f: dynamic_cast<FilterOperator *>(oprt)->filters_)
            exps.push_back(new GPStore::Expression(*f));
        std::unique_ptr<GPStore::Expression> filter(GPStore::Expression::JoinExpressionBy(exps));
        cur_result->doFilter(*new_result, filter.get(), kvstore_, param_.get());
    }
    else if (oprt->type_ == PQueryOperator::MODIFIER) {
        ModifierOperator * mod = dynamic_cast<ModifierOperator*>(oprt);
        std::vector<const GPStore::Expression *> exps;
        for(auto & ord : mod->order_exps_)
            exps.push_back(ord.get());
        std::vector<unsigned > cols;
        if(!mod->order_exps_.empty()){
            cols = cur_result->projectionView(exps, kvstore_, param_.get());
            cur_result->sort(0, (int)cur_result->rows_.size() - 1, cols, mod->ascending_);
        }
        if(mod->distinct_ && (mod->limit_ != INVALID || mod->skip_ != 0)){
            std::unique_ptr<PTempResult> tmp(new PTempResult);
            tmp->head_ = new_result->head_;
            cur_result->doDistinct(*tmp, mod->distinct_vars, cols);
            tmp->doLimit(*new_result, mod->limit_, mod->skip_);
        } else if(mod->limit_ != INVALID || mod->skip_ != 0){
            cur_result->doLimit(*new_result, mod->limit_, mod->skip_);
        } else if(mod->distinct_){
            cur_result->doDistinct(*new_result, mod->distinct_vars, cols);
        } else {
            new_result.reset(cur_result.release());
        }
    }
    else if (oprt->type_ == PQueryOperator::UNWIND) {
        UnwindOperator * unw = dynamic_cast<UnwindOperator*>(oprt);
        new_result->head_.other_var_.addVar(unw->var_id_);
        cur_result->doUnwind(*new_result, unw->unwind_.get(), unw->var_id_, kvstore_, param_.get());
    }
    else if (oprt->type_ == PQueryOperator::CALL) {
        throw std::runtime_error("[ERROR] Call Operator not implemented.");
    }
    else if (oprt->type_ == PQueryOperator::CREATE) {
        EvaluateStepCreate(cur_result, new_result, dynamic_cast<CreateOperator*>(oprt), msg);
    }
    else if (oprt->type_ == PQueryOperator::DELETE) {

    }
    else if (oprt->type_ == PQueryOperator::SET) {

    }
    else if (oprt->type_ == PQueryOperator::REMOVE) {

    }
    else if (oprt->type_ == PQueryOperator::GROUP_BY) {
        GroupByOperator * group = dynamic_cast<GroupByOperator*>(oprt);
        groups_ = cur_result->doGroupBy(group->grouping_keys_);
        new_result.reset(cur_result.release());
    }
    else if (oprt->type_ == PQueryOperator::AGGREGATION) {
        AggregationOperator * aggr = dynamic_cast<AggregationOperator*>(oprt);
        new_result->head_.other_var_ += aggr->aggr_var_id_;
        std::vector<const GPStore::Expression*> vec;
        for(auto & e : aggr->aggr_value_) vec.push_back(e.get());
        cur_result->doAggregation(*new_result, groups_, vec, aggr->aggr_var_id_, kvstore_,param_.get());
    }
    else if (oprt->type_ == PQueryOperator::SHORTEST_PATH) {

    }
}

void PGeneralEvaluation::EvaluateStep(std::unique_ptr<PTempResult> & left_result, std::unique_ptr<PTempResult>  & right_result, std::unique_ptr<PTempResult>  & new_result, PQueryOperator *oprt){
    // consider AND, OPTIONAL, UNION, MINUS
    for(auto var : oprt->minimal_varset_.vars){
        if(left_result->head_.spo_var_.findVar(var)){
            new_result->head_.spo_var_.addVar(var);
        } else if(right_result->head_.spo_var_.findVar(var)){
            new_result->head_.spo_var_.addVar(var);
        } else if(left_result->head_.edge_var_.findVar(var)){
            new_result->head_.edge_var_.addVar(var);
        } else if(right_result->head_.edge_var_.findVar(var)){
            new_result->head_.edge_var_.addVar(var);
        } else if(left_result->head_.other_var_.findVar(var)){
            new_result->head_.other_var_.addVar(var);
        } else if(right_result->head_.other_var_.findVar(var)){
            new_result->head_.other_var_.addVar(var);
        }
    }
    auto comm = left_result->getAllVarset() * right_result->getAllVarset();
    int nl = left_result->head_.spo_var_.getVarsetSize(), ml = left_result->head_.edge_var_.getVarsetSize();
    int nr = right_result->head_.spo_var_.getVarsetSize(), mr = right_result->head_.edge_var_.getVarsetSize();

    std::vector<unsigned> left_cols, right_cols;

    for(auto var : comm.vars){
        if(left_result->head_.spo_var_id2col_.find(var) != left_result->head_.spo_var_id2col_.end()){
            left_cols.push_back(left_result->head_.spo_var_id2col_.at(var));
        } else if(left_result->head_.edge_var_id2col_.find(var) != right_result->head_.edge_var_id2col_.end()){
            left_cols.push_back(nl + left_result->head_.edge_var_id2col_.at(var));
        } else {
            left_cols.push_back(nl + ml + left_result->head_.value_var_id2col_.at(var));
        }

        if(right_result->head_.spo_var_id2col_.find(var) != right_result->head_.spo_var_id2col_.end()){
            right_cols.push_back(right_result->head_.spo_var_id2col_.at(var));
        }
        else if(right_result->head_.edge_var_id2col_.find(var) != right_result->head_.edge_var_id2col_.end()){
            right_cols.push_back(nr + right_result->head_.edge_var_id2col_.at(var));
        }
        else {
            right_cols.push_back(nr + mr + right_result->head_.value_var_id2col_.at(var));
        }
    }

    if (oprt->type_ == PQueryOperator::AND) {

        if(comm.empty()){
            left_result->doCartesianProduct(*right_result, *new_result);
        }
        else {
            left_result->doJoin(*right_result, *new_result, right_cols, left_cols);
        }
    }
    else if (oprt->type_ == PQueryOperator::OPTIONAL) {
        if(comm.empty()){
            left_result->doCartesianProduct(*right_result, *new_result);
        }
        else {
            left_result->doLeftOuterJoin(*right_result, *new_result, right_cols, left_cols);
        }
    }
    else if (oprt->type_ == PQueryOperator::UNION) {
        UnionOperator * union_op = dynamic_cast<UnionOperator *>(oprt);
        if(union_op->union_ty_ == UnionOperator::CYPHER_UNION){
            // comm var is not important. we see comm var name.
            PVarset<unsigned > vars1, vars2;
            vars1 = left_result->getAllVarset();
            vars2 = right_result->getAllVarset() * oprt->minimal_varset_;

            std::vector<int> map1to2;
            for(auto var :vars1.vars) {
                int n = -1;
                for(int i = 0; i < vars2.getVarsetSize(); ++i)
                    if(id2var_name_->at(var) == id2var_name_->at(vars2.vars[i])){
                        n = i;
                        break;
                    }
                map1to2.push_back(n);
            }

            // Update left's table header.
            PTempResult::Header new_head;
            for(int i = 0; i < vars1.getVarsetSize(); ++i){
                if(map1to2[i] == -1) continue;
                unsigned  var = vars1.vars[i];
                if(left_result->head_.spo_var_.findVar(var)){
                    new_head.spo_var_.addVar(vars2.vars[map1to2[i]]);
                    new_head.spo_var_id2col_[vars2.vars[map1to2[i]]] = left_result->head_.spo_var_id2col_.at(var);
                } else if(left_result->head_.edge_var_.findVar(var)){
                    new_head.edge_var_.addVar(vars2.vars[map1to2[i]]);
                    new_head.edge_var_id2col_[vars2.vars[map1to2[i]]] = left_result->head_.edge_var_id2col_.at(var);
                } else if(left_result->head_.other_var_.findVar(var)){
                    new_head.other_var_.addVar(vars2.vars[map1to2[i]]);
                    new_head.value_var_id2col_[vars2.vars[map1to2[i]]] = left_result->head_.value_var_id2col_.at(var);
                }
            }
            left_result->head_ = new_head;
            // do Union
            left_result->doUnion(*new_result);
            right_result->doUnion(*new_result);
        }
        else {
            left_result->doUnion(*new_result);
            right_result->doUnion(*new_result);
        }
    }
    else if (oprt->type_ == PQueryOperator::MINUS) {
        throw std::runtime_error("[ERROR] Minus Operator has not been implemented.");
    }
}

/**
 * @brief Create Nodes/ Edges, see Cypher CREATE clause for more details.
 * @param cur_result Current driving table.
 * @param new_result New table to stream results to.
 * @param create_op Create Operator.
 * @param msg Send error message to the caller.
 * @warning We don't check the correctness of semantics! Besides, like MATCH clause, we don't handle named paths in this version. (e.g. p = (a)-[]->(c) )
 * @attention Already bound edge cant occur in CREATE.
 * */
bool PGeneralEvaluation::EvaluateStepCreate(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult> & new_result, CreateOperator *create_op, std::string & msg){
    /*=================Two CASE=================
     * 1. cur_result is empty(i.e. has no column)
     * 2. cur_result has some var bindings.
     * =========================================*/
    new_result->clear();
    // Firstly, Construct the columns of new result.
    PVarset<unsigned > node_var, edge_var, proj_path_var;
    for(auto & pat : create_op->pattern_){
        for(auto & node : pat->nodes_)
            new_result->head_.spo_var_.addVar(node->var_id_);
        for(auto & edge: pat->edges_)
            new_result->head_.edge_var_.addVar(edge->var_id_);
        if(!pat->is_anno_var_) {
            new_result->head_.other_var_.addVar(pat->var_id_);
            proj_path_var.addVar(pat->var_id_);
        }
        node_var += pat->covered_node_var_id_;
        edge_var += pat->covered_edge_var_id_;
    }
    PVarset<unsigned > scope = cur_result->getAllVarset() * new_result->getAllVarset();
    // Check type is node var.
    bool legal_create = true;
    for(auto var : scope.vars){
        int where = -1;
        if(cur_result->head_.spo_var_.findVar(var)) where = 0;
        else if(cur_result->head_.edge_var_.findVar(var)) where = 1;
        else if(cur_result->head_.other_var_.findVar(var)) where = 2;
        if(where == -1){legal_create = false;break;}
        if(node_var.findVar(var)){
            if(where == 1) { legal_create= false;break; }
            if(where == 2){
                legal_create = CheckColumnType(*cur_result, var, GPStore::Value::Type::NODE);
            }
        }
        if(edge_var.findVar(var)){
            if(where == 1) { legal_create= false;break; }
            if(where == 2){
                legal_create = CheckColumnType(*cur_result, var, GPStore::Value::Type::EDGE);
            }
        }

    }
    if(!legal_create)return false;


    PVarset<unsigned > remain = create_op->minimal_varset_ - new_result->getAllVarset();
    for(auto var : remain.vars){
        if(cur_result->head_.spo_var_.findVar(var)){
            new_result->head_.spo_var_.addVar(var);
        }
        else if(cur_result->head_.edge_var_.findVar(var)){
            new_result->head_.edge_var_.addVar(var);
        }
        else {
            new_result->head_.other_var_.addVar(var);
        }
    }

    // Deal with case1. Empty.
    if(cur_result->getAllVarset().empty()){
        // Case 1: Empty
        new_result->head_.initColumnInfoByVarset();
        new_result->rows_.emplace_back();
        for(auto & pat : create_op->pattern_){
            for(auto & node : pat->nodes_){
                if(scope.findVar(node->var_id_)) continue;
                // CREATE this var.
                // TODO: ACCESS KVStore, label
                // TODO: ACCESS KVStore, property.
                unsigned nid;

                new_result->rows_.back().spo_id_.push_back(nid);
                scope.addVar(node->var_id_);
            }
        }
        for(auto & pat : create_op->pattern_){
            int num_edges = pat->edges_.size();
            for(int i = 0; i < num_edges; ++i){
                auto & ei = pat->edges_[i];
                auto & ni = pat->nodes_[i], & ni1 = pat->nodes_[i+1];
                if(scope.findVar(ei->var_id_)) {
                    throw std::runtime_error("[ERROR]  代码有bug。Create/Pattern/Edge.");
                }
                unsigned nid1 = new_result->rows_.back().spo_id_.at(new_result->head_.spo_var_id2col_.at(ni->var_id_));
                unsigned nid2 = new_result->rows_.back().spo_id_.at(new_result->head_.spo_var_id2col_.at(ni1->var_id_));
                TYPE_EDGE_ID  eid = 0;
                // TODO: ACCESS KVStore, TYPE
                // TODO: ACCESS KVStore, property.
                new_result->rows_.back().edge_id_.push_back(eid);
                scope.addVar(eid);
            }
        }

        return true;
    }

    // Secondly, For each row, scan the pattern, construct the Node of pattern.
    int num_rows = cur_result->rows_.size();
    for(int i = 0; i < num_rows; ++i){
        for(auto & pat : create_op->pattern_){
            for(auto & node : pat->nodes_){
                if(scope.findVar(node->var_id_)) continue;
                // CREATE this var.
                cur_result->head_.spo_var_.addVar(node->var_id_);
                cur_result->head_.spo_var_id2col_[node->var_id_] = cur_result->rows_.back().spo_id_.size();
                // TODO: ACCESS KVStore, label
                // TODO: ACCESS KVStore, property.
                unsigned nid;

                cur_result->rows_[i].spo_id_.push_back(nid);
                scope.addVar(node->var_id_);
            }
        }
    }


    // Then, For each row, scan the pattern, construct the Edge of pattern.
    for(int rw = 0; rw < num_rows; ++rw) {
        for (auto &pat: create_op->pattern_) {
            int num_edges = pat->edges_.size();
            for (int i = 0; i < num_edges; ++i) {
                auto &ei = pat->edges_[i];
                auto &ni = pat->nodes_[i], &ni1 = pat->nodes_[i + 1];
                if (scope.findVar(ei->var_id_)) {
                    throw std::runtime_error("[ERROR]  代码有bug。Create/Pattern/Edge.");
                }
                unsigned nid1 = new_result->rows_[rw].spo_id_.at(new_result->head_.spo_var_id2col_.at(ni->var_id_));
                unsigned nid2 = new_result->rows_[rw].spo_id_.at(new_result->head_.spo_var_id2col_.at(ni1->var_id_));
                TYPE_EDGE_ID eid = 0;
                // TODO: ACCESS KVStore, TYPE
                // TODO: ACCESS KVStore, property.
                cur_result->head_.edge_var_.addVar(eid);
                cur_result->head_.edge_var_id2col_[ei->var_id_] = cur_result->rows_[i].edge_id_.size();
                cur_result->rows_[rw].edge_id_.push_back(eid);
                scope.addVar(eid);
            }
        }
    }
    // Lastly, project the path variable, and clip columns by minimal var set.
    // TODO : Implement projection path var.
    cur_result->doProjection({},{},create_op->minimal_varset_.vars, kvstore_, param_.get());
    new_result.reset(cur_result.release());
    return true;
}

/**
 * @brief Delete Nodes/ Edges, see Cypher DELETE clause for more details.
 * @param cur_result Current driving table.
 * @param new_result New table to stream results to.
 * @param delete_op Delete Operator.
 * @param msg Send error message to the caller.
 * @warning We don't check the correctness of semantics! Besides, like MATCH clause, we don't handle named paths in this version. (e.g. p = (a)-[]->(c) )
 * @attention Already bound edge cant occur in CREATE.
 * */
bool PGeneralEvaluation::EvaluateStepDelete(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult> & new_result, DeleteOperator *delete_op, std::string & msg){
    return true;
}

/**
 * @brief Set Node labels, Node/Edge properties, see Cypher Set clause for more details.
 * @param cur_result Current driving table.
 * @param new_result New table to stream results to.
 * @param set_op Set Operator.
 * @param msg Send error message to the caller.
 * */
bool PGeneralEvaluation::EvaluateStepSet(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult> & new_result, SetOperator *set_op, std::string & msg){
    return true;
}

/**
 * @brief Remove Node labels, Node/Edge properties, see Cypher REMOVE clause for more details.
 * @param cur_result Current driving table.
 * @param new_result New table to stream results to.
 * @param rm_op Remove Operator.
 * @param msg Send error message to the caller.
 * */
bool PGeneralEvaluation::EvaluateStepRemove(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult> & new_result, RemoveOperator *rm_op, std::string & msg){
    return true;
}


BGPQueryNew * PGeneralEvaluation::WritePatternToBGP(BGPOperator * bgp_op, const std::vector<unsigned > & selected_var){
    bool edge_isomorphism = true;
    PVarset<unsigned> edges;
    for(auto & pat : bgp_op->pattern_){
        for(auto & edge : pat->edges_){
            edges.addVar(edge->var_id_);
        }
    }
    std::sort(edges.vars.begin(), edges.vars.end());
    for(int i = 0; i < edges.getVarsetSize(); ++i){
        for(int j = i + 1; j < edges.getVarsetSize(); ++j){
            if(!bgp_op->edge_conflict_.findVar(std::make_pair(edges.vars[i], edges.vars[j]))){
                edge_isomorphism = false;
                break;
            }
        }
    }
    std::vector<std::shared_ptr<VarDescriptor>> var_desc;
    std::map<unsigned, unsigned > id2index;
    for(auto & pat : bgp_op->pattern_){
        for(auto & node : pat->nodes_){
            unsigned idx = 0;
            if(id2index.find(node->var_id_) == id2index.end()){
                std::vector<unsigned > labels;
                for(auto & l : node->labels_) labels.push_back(kvstore_->getIDByString(l));
                idx = var_desc.size();
                var_desc.emplace_back(new NodeVarDescriptor(node->var_id_, VarDescriptor::VarType::Node, node->var_name_, labels, {}));
                id2index[node->var_id_] = idx;
                if(std::find(selected_var.begin(), selected_var.end(), node->var_id_) != selected_var.end())
                    var_desc.back()->selected_ = true;
            }
            else {
                idx = id2index.at(node->var_id_);
                auto & ptr = var_desc.at(idx);
                std::vector<unsigned > labels;
                for(auto & l : node->labels_) labels.push_back(kvstore_->getIDByString(l));

                for(auto label_id : labels){
                    if(std::find(ptr->labels_or_types_.begin(), ptr->labels_or_types_.end(), label_id) != ptr->labels_or_types_.end()){
                        ptr->labels_or_types_.push_back(label_id);
                    }
                }
            }
        }
        for(auto & edge : pat->edges_){
            unsigned idx = 0;
            if(id2index.find(edge->var_id_) == id2index.end()){
                std::vector<unsigned > tys;
                for(auto & l : edge->edge_types_) tys.push_back(kvstore_->getIDByString(l));
                idx = var_desc.size();
                if(edge->is_edge_length_v_){
                    var_desc.emplace_back(new EdgeVarDescriptor(edge->var_id_, VarDescriptor::VarType::Edge, edge->var_name_,
                                                                tys, {}, false, edge->range_left_,
                                                                edge->range_right_ == GPStore::EdgePattern::RANGE_INF ? -1 : edge->range_right_));

                } else {
                    var_desc.emplace_back(new EdgeVarDescriptor(edge->var_id_, VarDescriptor::VarType::Edge, edge->var_name_,
                                                                tys, {}, false, 1,1));

                }
                id2index[edge->var_id_] = idx;
                if(std::find(selected_var.begin(), selected_var.end(), edge->var_id_) != selected_var.end())
                    var_desc.back()->selected_ = true;
            }
            else {
                idx = id2index.at(edge->var_id_);
                auto & ptr = var_desc.at(idx);
                PVarset<unsigned >  tys;
                for(auto & l : edge->edge_types_) tys.addVar(kvstore_->getIDByString(l));
                tys += ptr->labels_or_types_;
                ptr->labels_or_types_ = tys.vars;
            }
        }
    }
    for(auto & f : bgp_op->filters_){
        if(f != nullptr && f->covered_var_id_.getVarsetSize() == 1){
            auto & var_d = var_desc[id2index[f->covered_var_id_.vars[0]]];
            var_d->exps_.emplace_back(f.get()); // !!WARN: Cant delete !
        }
    }
    BGPQueryNew * bgp = new BGPQueryNew;
    bgp->single_node_ = false;
    for(auto & var : var_desc){
        bgp->addVarDescriptor(var);
    }
    PVarset<unsigned > vars;
    for(auto & pat : bgp_op->pattern_){ vars += pat->covered_edge_var_id_; vars+=pat->covered_node_var_id_;}
    if(vars.getVarsetSize() == 1){
        bgp->single_node_ = true;
        return bgp;
    }
    for(auto & pat : bgp_op->pattern_){
        int n = pat->edges_.size();
        for(int  i = 0; i < n; ++i){
            // ni ei ni+1
            if(pat->edges_[i]->arrow_direction_ == GPStore::EdgePattern::UNDIRECTED){
                bgp->addCypherTripleVarId(pat->nodes_[i]->var_id_, pat->edges_[i]->var_id_, pat->nodes_[i + 1]->var_id_,false);
            } else if(pat->edges_[i]->arrow_direction_ == GPStore::EdgePattern::RIGHT_ARROW){
                bgp->addCypherTripleVarId(pat->nodes_[i]->var_id_, pat->edges_[i]->var_id_, pat->nodes_[i + 1]->var_id_,true);
            } else if(pat->edges_[i]->arrow_direction_ == GPStore::EdgePattern::LEFT_ARROW){
                bgp->addCypherTripleVarId(pat->nodes_[i + 1]->var_id_, pat->edges_[i]->var_id_, pat->nodes_[i]->var_id_,true);
            }
        }
    }

    for(auto & f : bgp_op->filters_){
        if(f->covered_var_id_.getVarsetSize() != 1){
            bgp->addFilterExp(f.get());
        }
    }
    if(edge_isomorphism) bgp->setExecMode(ExecMode::EdgeIsomorphism);
    return bgp;
}

void PGeneralEvaluation::copyIntermediaResult2TempResult(const PIntermediateResult * intermedia, PTempResult * tmp_result){
    tmp_result->head_.initColumnInfoByVarset();
    if(intermedia == nullptr) {
        return;
    }
    int n = tmp_result->head_.spo_var_.getVarsetSize(), m = tmp_result->head_.edge_var_.getVarsetSize();
    int v = tmp_result->head_.other_var_.getVarsetSize(), prop_num = tmp_result->head_.prop_.getVarsetSize();

    int rows = intermedia->spo_vars_.size();
    for(int row = 0; row < rows; ++row){
        tmp_result->rows_.emplace_back();

        for(int i = 0; i < n; ++i){
            unsigned spo_var = tmp_result->head_.spo_var_.vars[i], embedding_id;
            if(intermedia->spo_id2pos_.find(spo_var) != intermedia->spo_id2pos_.end()){
                embedding_id = intermedia->spo_vars_[row].at(intermedia->spo_id2pos_.at(spo_var));
            }else if(intermedia->prop_id2pos_.find(std::make_pair(spo_var, INVALID)) != intermedia->prop_id2pos_.end()){
                unsigned  pos = intermedia->prop_id2pos_.at(std::make_pair(spo_var, INVALID));
                embedding_id = intermedia->properties_[row].at(pos).data_.Node;
            } else {
                assert(false);
            }

            tmp_result->rows_.back().spo_id_.push_back(embedding_id);
        }

        for(int i = 0; i < m; ++i){
            unsigned edge_var = tmp_result->head_.edge_var_.vars[i], pos;
            TYPE_EDGE_ID eid;
            if(intermedia->e_id2pos_.find(edge_var) != intermedia->e_id2pos_.end()){
                eid = intermedia->edges_[row].at(intermedia->e_id2pos_.at(edge_var));
            }
            else if(intermedia->prop_id2pos_.find(std::make_pair(edge_var, INVALID))!= intermedia->prop_id2pos_.end()){
                pos = intermedia->prop_id2pos_.at(std::make_pair(edge_var, INVALID));
                eid = intermedia->properties_[row].at(pos).data_.Edge;
            } else {
                assert(false);
            }
            tmp_result->rows_.back().edge_id_.push_back(eid);
        }

        for(int i = 0; i < v; ++i){
            unsigned value_var = tmp_result->head_.other_var_.vars[i], pos;
            if(intermedia->prop_id2pos_.find(std::make_pair(value_var, INVALID))!= intermedia->prop_id2pos_.end()){
                pos = intermedia->prop_id2pos_.at(std::make_pair(value_var, INVALID));
                tmp_result->rows_.back().values_.emplace_back(intermedia->properties_[row].at(pos));
            }
            else if(intermedia->path_id2pos_.find(value_var) != intermedia->path_id2pos_.end()){
                pos = intermedia->path_id2pos_.at(value_var);
                std::vector<TYPE_ENTITY_LITERAL_ID > nodes;
                std::vector<TYPE_EDGE_ID> edges;
                auto & path = intermedia->paths_[row].at(pos);
                int n  = path.size();
                if(n != 0){nodes.push_back(path[0]);}
                for(int i = 1; i < n; ++i){
                    edges.push_back(path[i++]);
                    nodes.push_back(path[i]);
                }
                tmp_result->rows_.back().values_.emplace_back(nodes, edges);
            }
            else
                assert(false);
        }

        for(int i = 0; i < prop_num; ++i){
            auto prop = tmp_result->head_.prop_.vars[i];
            auto it = intermedia->prop_id2pos_.find(prop);
            if(it == intermedia->prop_id2pos_.end()){
                // TODO: Access KVstore
                tmp_result->rows_.back().values_.emplace_back();
            }
            else {
                tmp_result->rows_.back().values_.emplace_back(intermedia->properties_[row].at(it->second));
            }
        }
    }
    return;
}

bool PGeneralEvaluation::CheckColumnType(const PTempResult & tb, unsigned var_id, GPStore::Value::Type value_ty){
    auto it = tb.head_.value_var_id2col_.find(var_id);
    unsigned pos, n = tb.rows_.size();
    if(it != tb.head_.value_var_id2col_.end()){
        pos = it->second;
    } else return false;

    for(int i = 0; i < n; ++i){
        if(tb.rows_[i].values_[pos].type_ != value_ty)
            return false;
    }
    return true;
}