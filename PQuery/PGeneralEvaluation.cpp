#include "PGeneralEvaluation.h"
//
// Created by zcs on 5/23/23.
//

PGeneralEvaluation::PGeneralEvaluation(KVstore *_kvstore, StringIndex *_stringindex, PStore * _pstore,
                                       const std::shared_ptr<std::unordered_map<std::string, GPStore::Value>> & _param,
                                       TYPE_TRIPLE_NUM *_pre2num,TYPE_TRIPLE_NUM *_pre2sub,
                                       TYPE_TRIPLE_NUM *_pre2obj, TYPE_TRIPLE_NUM _triples_num, TYPE_PREDICATE_ID _limitID_predicate,
                                       TYPE_ENTITY_LITERAL_ID _limitID_literal, TYPE_ENTITY_LITERAL_ID _limitID_entity,
                                       std::shared_ptr<Transaction> txn)
:kvstore_(_kvstore), stringindex_(_stringindex), pstore_(_pstore), param_(_param), pre2num(_pre2num), pre2sub(_pre2sub),
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

bool PGeneralEvaluation::DoQuery(){
    std::vector<EvaluationStackItem> st;        // a stack
    st.emplace_back(logical_plan_.get(), nullptr, NOT_DONE);
    std::unique_ptr<PTempResult> cur_result(new PTempResult);
    while(!st.empty()){
        auto & item = st.back();
        if(item.state_ == NOT_DONE) {
            if(item.node_->left_ != nullptr){
                st.emplace_back(item.node_->left_, nullptr, NOT_DONE);
            }
            item.state_ = FINISH_LEFT;
        } else if(item.state_ == FINISH_LEFT){
            if(item.node_->right_ != nullptr){
                item.result_.reset(cur_result.release());
                cur_result.reset(new PTempResult);
                st.emplace_back(item.node_->right_, nullptr, NOT_DONE);
            }
            item.state_ = FINISH_RIGHT;
        } else{
            std::unique_ptr<PTempResult> new_result(new PTempResult);
            for(auto var : item.node_->operator_->minimal_varset_.vars){
                if(cur_result->head_.spo_var_.findVar(var)){
                    new_result->head_.spo_var_.addVar(var);
                }
                else if(cur_result->head_.edge_var_.findVar(var)){
                    new_result->head_.edge_var_.addVar(var);
                }
                else if(cur_result->head_.other_var_.findVar(var)){
                    new_result->head_.other_var_.addVar(var);
                }
            }
            // cur_result ====oprt===> new_result
            if(item.node_->left_ == nullptr || item.node_->right_ == nullptr){
                // consider BGP, FILTER, PROJECTION  MODIFIER,  UNWIND, CALL,
                // CREATE, DELETE, SET, REMOVE,  GROUP_BY, AGGREGATION,  SHORTEST_PATH
                if(item.node_->operator_->type_ == PQueryOperator::BGP){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::FILTER){
                    std::vector<GPStore::Expression *> exps;
                    for(auto& f : dynamic_cast<FilterOperator*>(item.node_->operator_.get())->filters_)
                        exps.push_back(new GPStore::Expression(*f));
                    std::unique_ptr<GPStore::Expression> filter(GPStore::Expression::JoinExpressionBy(exps));
                    cur_result->doFilter(*new_result, filter.get(), kvstore_, param_.get());
                }
                else if(item.node_->operator_->type_ == PQueryOperator::PROJECTION){
                    ProjectionOperator *proj_oprt = dynamic_cast<ProjectionOperator*>(item.node_->operator_.get());
                    std::vector<const GPStore::Expression*> proj_exps;
                    for(auto & proj_exp : proj_oprt->proj_exps_){
                        proj_exps.push_back(proj_exp.get());
                    }
                    cur_result->doProjection(proj_exps, proj_oprt->var_id_, new_result->getAllVarset().vars, kvstore_, param_.get());
                }
                else if(item.node_->operator_->type_ == PQueryOperator::MODIFIER){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::UNWIND){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::CALL){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::CREATE){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::DELETE){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::SET){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::REMOVE){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::GROUP_BY){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::AGGREGATION){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::SHORTEST_PATH){

                }
            }

            // left_result + cur_result ====oprt====> new_result
            else if(item.node_->left_ != nullptr && item.node_->right_ != nullptr){
                // consider AND, OPTIONAL, UNION, MINUS
                if(item.node_->operator_->type_ == PQueryOperator::AND){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::OPTIONAL){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::UNION){

                }
                else if(item.node_->operator_->type_ == PQueryOperator::MINUS){

                }
            }

            cur_result.reset(new_result.release());
            st.pop_back();
        }
    }
    temp_result_.reset(cur_result.release());
    return true;
}
