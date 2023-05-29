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
        if(item.)
    }
}
