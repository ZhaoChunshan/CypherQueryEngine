#include "PQueryOperator.h"
#include <unordered_map>
#include <string>
#include "../Value/Value.h"

namespace GPStore{


class PQueryTree{
public:
    enum Mode {SPARQL, Cypher};
    Mode mode_;
    PQueryOperator *root_;
    /* Cypher global paramters */
    std::unordered_map<std::string, GPStore::Value> param_;
    /* SPARQL prefix name */
    std::map<std::string, std::string> prefix_map;
    PQueryTree();
    PQueryTree(Mode mode);
    ~PQueryTree();

    GPStore::Value setParam(const std::string& param_name, const GPStore::Value &val);
    GPStore::Value getParam(const std::string& param_name);
};

} // namespace GPStore
