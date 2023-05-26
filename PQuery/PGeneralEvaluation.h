//
// Created by zcs on 5/17/23.
//

#ifndef PQUERY_PGENERALEVALUATION_H
#define PQUERY_PGENERALEVALUATION_H

#include <memory>
#include "../PParser/PCypherParser.h"
#include "PQueryTree.h"
#include "PTempResult.h"
#include "../PParser/CypherAST.h"
#include "../Util/util.h"


/// TODO: handler transaction && kvstore, stringindex, PStore; we remove some vars from original GE.
/// Three-staged Query Evaluation:
/// 1. Parse a Cypher Query to an AST;
/// 2. Generate Logical plan;
/// 3. Execute according to the plan.
/// We perform optimization methods on 2,3
class PGeneralEvaluation{
private:
    std::unique_ptr<PTempResult> temp_result_;
    std::shared_ptr<PCypherParser> cypher_parser_;  // queryparser
    std::unique_ptr<PTreeNode> logical_plan_;       // querytree
    std::unique_ptr<CypherAST> cypher_ast_;         // AST
    std::shared_ptr<std::unordered_map<std::string, GPStore::Value>> param_;    // Cypher param
    std::shared_ptr<std::vector<std::string>> id2var_name_;     // decode a var id

    // int well_designed
    KVstore * kvstore_;
    PStore *pstore_;
    StringIndex * stringindex_;
    std::shared_ptr<Optimizer> optimizer_;
    // QueryCache *query_cache;
    //		PathQueryHandler *pqHandler;
    //		CSR *csr;
    //		bool ranked;

    TYPE_TRIPLE_NUM *pre2num;
    TYPE_TRIPLE_NUM *pre2sub;
    TYPE_TRIPLE_NUM *pre2obj;
    TYPE_TRIPLE_NUM triples_num;
    TYPE_PREDICATE_ID limitID_predicate;
    TYPE_ENTITY_LITERAL_ID limitID_literal;
    TYPE_ENTITY_LITERAL_ID limitID_entity;


    std::shared_ptr<Transaction> txn_;

    // shared_ptr<BGPQuery> bgp_query_total;

//    char* string_index_buffer;
//    unsigned string_index_buffer_size;
//
//    AllEntityId all_entity_id;
//    FILE* fp;
//    bool export_flag;
public:
    PGeneralEvaluation(KVstore *_kvstore, StringIndex *_stringindex, PStore * _pstore,
                       const std::shared_ptr<std::unordered_map<std::string, GPStore::Value>> & _param,
    TYPE_TRIPLE_NUM *_pre2num,TYPE_TRIPLE_NUM *_pre2sub,
            TYPE_TRIPLE_NUM *_pre2obj, TYPE_TRIPLE_NUM _triples_num, TYPE_PREDICATE_ID _limitID_predicate,
    TYPE_ENTITY_LITERAL_ID _limitID_literal, TYPE_ENTITY_LITERAL_ID _limitID_entity,
    std::shared_ptr<Transaction> txn = nullptr);

    bool ParseCypherQuery(const std::string &_query);
    bool ParseCypherQuery(std::istream& in);


    bool GenerateLogicalPlan();

    // Simulate Recursive Using a Stack.
    // State: 0 Have not been done
    // State: 1 Finished Left tree
    // State: 2 Finished Left && right Tree, pop stack
    // Nodes in the stack from bottom to top, is just a PATH from root to current node.
    // Scan The nodes in the stack, and then we can do Candidate Passing
    bool DoQuery();

private:
    /// helper functions for Stage3. doQuery.

};

#endif //PQUERY_PGENERALEVALUATION_H
