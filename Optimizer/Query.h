//
// Created by yll on 5/9/23.
//

#ifndef GPSTORE_OPTIMIZER_QUERY_H_
#define GPSTORE_OPTIMIZER_QUERY_H_

#include "../PQuery/BGPQuery.h"
#include "PlanGeneratorNew.h"
#include "../Executor/p_executor.h"

enum class QueryStrategy {Normal, TopK, LimitK};

class Query {
private:
    KVstore* kv_store_;
    TYPE_TRIPLE_NUM* pre2num_;
    TYPE_TRIPLE_NUM* pre2sub_;
    TYPE_TRIPLE_NUM* pre2obj_;
    TYPE_TRIPLE_NUM triples_num_;
    TYPE_PREDICATE_ID limitID_predicate_;
    TYPE_ENTITY_LITERAL_ID limitID_literal_;
    TYPE_ENTITY_LITERAL_ID limitID_entity_;
    BGPQueryNew* bgp_query_;
    shared_ptr<Transaction> txn_;

    PExecutor executor_;

public:
    Query(KVstore* kv_store, TYPE_TRIPLE_NUM* pre2num, TYPE_TRIPLE_NUM* pre2sub, TYPE_TRIPLE_NUM* pre2obj, TYPE_TRIPLE_NUM triples_num,
          TYPE_PREDICATE_ID limitID_predicate, TYPE_ENTITY_LITERAL_ID limitID_literal, TYPE_ENTITY_LITERAL_ID limitID_entity,
          BGPQueryNew* bgp_query, std::shared_ptr<Transaction> txn);
    ~Query() = default;

    QueryStrategy ChooseQueryStrategy();

    void BFSExecutionOneNode(TreeNode *tree_node, CandidateList *id_caches, PIntermediateResult *result);
    PIntermediateResult* BFSExecution(PlanTreeNew *plan_tree, CandidateList &id_caches);
    void CopyToResult(PIntermediateResult *result);

    PIntermediateResult DoQuery();
};

#endif //GPSTORE_OPTIMIZER_QUERY_H_
