#include "PQueryOperator.h"
#include <unordered_map>
#include <string>
#include "../Value/Value.h"
#include "../PParser/CypherAST.h"

class PQueryTree{
public:
    enum Mode {SPARQL, Cypher};
    Mode mode_;
    /* root of the query tree, each node is PQueryOperator */
    PQueryOperator *root_;
    /* Cypher global paramters */
    std::shared_ptr<std::unordered_map<std::string, GPStore::Value>> param_;
    /* Variable id to string */
    std::vector<std::string> id2var_name_;
    /* Property id to string */
    std::map<unsigned, std::string> prop_id2string_;
    /* string to prop id */
    std::unordered_map<std::string, unsigned> prop2id_;
    PQueryTree();
    ~PQueryTree();

    GPStore::Value setParam(const std::string& param_name, const GPStore::Value &val);
    GPStore::Value getParam(const std::string& param_name);
    bool existParam(const std::string& param_name);
    void GenerateQueryTree(const CypherAST* ast);
    PQueryOperator * GenerateQueryTree(const SingleQueryAST* ast);
    PQueryOperator * GenerateQueryTree(const QueryUnitAST* ast, PQueryOperator * tree);
    PQueryOperator * GenerateQueryTree(const MatchAST *ast);

    PQueryOperator * GenerateQueryTree(const UnwindAST* ast, PQueryOperator * tree);
    PQueryOperator * GenerateQueryTree(const InQueryCallAST* ast, PQueryOperator * tree);

    PQueryOperator * GenerateQueryTree(const WithReturnAST* ast, PQueryOperator * tree);
};


