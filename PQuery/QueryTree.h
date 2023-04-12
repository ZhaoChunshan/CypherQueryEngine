#include "PQueryOperator.h"
#include <unordered_map>
#include <string>
#include "../Value/Value.h"

namespace GPStore{


class QueryTree{
public:
    enum Mode {SPARQL, Cypher};
    Mode mode_;
    PQueryOperator *root_;
    /* Cypher global paramters */
    std::unordered_map<std::string, GPStore::Value> param_;

    QueryTree();
    QueryTree(Mode mode);
    ~QueryTree();

    GPStore::Value setParam(const std::string& param_name, const GPStore::Value &val);
    GPStore::Value getParam(const std::string& param_name);
};

} // namespace GPStore
