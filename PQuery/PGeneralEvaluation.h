//
// Created by zcs on 5/17/23.
//

#ifndef PQUERY_PGENERALEVALUATION_H
#define PQUERY_PGENERALEVALUATION_H

#include <memory>
#include "../PParser/PCypherParser.h"
#include "PQueryTree.h"
#include "PTempResult.h"
#include "BGPQuery.h"
#include "../PParser/CypherAST.h"
#include "../Util/Util.h"


/// TODO: handler transaction && kvstore, stringindex, PStore; we remove some vars from original GE.
/// Three-staged Query Evaluation:
/// 1. Parse a Cypher Query to an AST;
/// 2. Generate Logical plan;
/// 3. Execute according to the plan.
/// We perform optimization on 2,3
class PGeneralEvaluation{
public:
    std::unique_ptr<PTempResult> temp_result_;
    std::shared_ptr<PCypherParser> cypher_parser_;  // queryparser
    std::unique_ptr<PTreeNode> logical_plan_;       // querytree
    std::unique_ptr<CypherAST> cypher_ast_;         // AST
    std::shared_ptr<std::unordered_map<std::string, GPStore::Value>> param_;    // Cypher param
    std::shared_ptr<std::vector<std::string>> id2var_name_;     // decode a var id

    // int well_designed
    KVstore * kvstore_;
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

    PGeneralEvaluation(KVstore *_kvstore, StringIndex *_stringindex,
                       const std::shared_ptr<std::unordered_map<std::string, GPStore::Value>> & _param,
    TYPE_TRIPLE_NUM *_pre2num,TYPE_TRIPLE_NUM *_pre2sub,
            TYPE_TRIPLE_NUM *_pre2obj, TYPE_TRIPLE_NUM _triples_num, TYPE_PREDICATE_ID _limitID_predicate,
    TYPE_ENTITY_LITERAL_ID _limitID_literal, TYPE_ENTITY_LITERAL_ID _limitID_entity,
    std::shared_ptr<Transaction> txn = nullptr);

    bool ParseCypherQuery(const std::string &_query);
    bool ParseCypherQuery(std::istream& in);

    bool GenerateLogicalPlan();

    bool DoQuery();

private:
    class EvaluationStackItem{
    public:
        int state_; // 0, 1, 2
        PTempResult *result_;   // store left tree
        PTreeNode * node_;      // plan tree node
        EvaluationStackItem():state_(0), result_(nullptr), node_(nullptr){}
        EvaluationStackItem(PTreeNode * oprt_node, PTempResult * tmp_result, int state):node_(oprt_node),result_(tmp_result),state_(state){}
        EvaluationStackItem(const EvaluationStackItem & that): state_(that.state_),result_(that.result_),node_(that.node_){}
        ~EvaluationStackItem() = default ;
    };

    std::vector<unsigned > groups_;         // tmp vector for group by. remember each group.
    /// helper functions for Stage3. doQuery.

    void EvaluateStepBGP(PTempResult & new_result, BGPOperator *bgp_op, std::vector<std::unique_ptr<EvaluationStackItem>> & st, PVarset<unsigned > & selected_var);

    void EvaluateStep(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult>  & new_result,  PQueryOperator *oprt);

    void EvaluateStep(std::unique_ptr<PTempResult> & left_result, std::unique_ptr<PTempResult>  & right_result, std::unique_ptr<PTempResult>  & new_result, PQueryOperator *oprt);

    bool EvaluateStepCreate(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult>  & right_result, CreateOperator *create_op, std::string & msg);
    bool EvaluateStepDelete(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult> & new_result, DeleteOperator *delete_op, std::string & msg);
    bool EvaluateStepSet(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult> & new_result, SetOperator *set_op, std::string & msg);
    bool EvaluateStepRemove(std::unique_ptr<PTempResult> & cur_result, std::unique_ptr<PTempResult> & new_result, RemoveOperator *rm_op, std::string & msg);

    BGPQueryNew * WritePatternToBGP(BGPOperator * bgp_op, const std::vector<unsigned > & selected_var);
    void copyIntermediaResult2TempResult(const PIntermediateResult * intermedia, PTempResult * tmp_result);

    // Check of Execution Time
    bool CheckColumnType(const PTempResult & tb, unsigned var_id, GPStore::Value::Type value_ty);
};

#endif //PQUERY_PGENERALEVALUATION_H
