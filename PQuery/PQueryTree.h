#include "PQueryOperator.h"
#include <unordered_map>
#include <string>
#include "../Value/Value.h"

class PQueryTree{
public:
    enum Mode {SPARQL, Cypher};
    Mode mode_;
    /* root of the query tree, each node is PQueryOperator */
    PQueryOperator *root_;
    /* Cypher global paramters */
    std::unordered_map<std::string, GPStore::Value> param_;

    PQueryTree();
    PQueryTree(Mode mode);
    ~PQueryTree();

    GPStore::Value setParam(const std::string& param_name, const GPStore::Value &val);
    GPStore::Value getParam(const std::string& param_name);
};


