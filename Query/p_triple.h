#include <string>
#include <vector>
#include <map>
#include <../Value/src/Value.h>
#include <../Value/src/Expression.h>

using EdgeIdType = unsigned long long;
using NodeIdType = unsigned long long;
using LabelIdType = unsigned;
using PropertyIdType = unsigned;

class NodePattern{
public:
    NodeIdType id_;
    std::vector<LabelIdType> labels_;
    std::map<PropertyIdType, Value> props_;
}

class EdgePattern{
public:
    enum class EdgeDirectType{LeftArrow, RightArrow, Undirected }; 
    NodeIdType id_;
    EdgeDirectType direction_;
    int range_left_, range_right_;     
    std::vector<LabelIdType> labels_;
    std::map<PropertyIdType, Value> props_;
}


class PTriple{
public:
    NodeIdType s;
    EdgeIdType e;
    NodeIdType o;
};