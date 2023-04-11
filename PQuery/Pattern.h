#include <string>
#include <vector>
#include <map>

using Expression =  void*;

class NodeEdgePathVarInfo{
public:
    enum NodeEdgePathType { NODE_VAR, EDGE_VAR, PATH_VAR, SHORTEST_PATH_VAR };
    enum EdgeArrowType { LFET_ARROW, RIGHT_ARROW, UNDIRECTED };

    NodeEdgePathType type_;
    bool is_anno_var_;
    std::string var_name_;  // we give anno var name such as @anno_1
    // Just a one to one map from var_name_ to var_id_ [in this scope]
    // For the convinience of edge conflict && filter injection
    unsigned var_id_;           

    // used for node_var and edge_var
    std::vector<std::string> labels_or_types_;

    // for update clauses, may be parameters, e.g. CREATE (a $1)
    std::map<std::string, Expression> properties_;

    // Only used when type_ == EDGE_VAR
    bool is_variable_length_;
    unsigned long long range_left, range_right;
    static const unsigned long long RANGE_INF = 0xffffffffffffffffULL;
    EdgeArrowType edge_direction_;

    // Only used when type_ == PATH_VAR
    std::vector<unsigned> nodes_var_id_;
    std::vector<unsigned> edges_var_id_;

    // Only used when type_ == SHORTEST_PATH_VAR
    bool is_all_shortest_;
    unsigned src_, tgt_;

    NodeEdgePathVarInfo();
    NodeEdgePathVarInfo(NodeEdgePathType _type, bool _is_anno, std::string var_name, unsigned _id);
    NodeEdgePathVarInfo(NodeEdgePathType _type, bool _is_anno, std::string var_name, unsigned _id, EdgeArrowType _direction);
    void addLabelType(const std::string& _label);
    void insertProperty(const std::string& _prop_name, const Expression& _value);
    void addFilter(const Expression& _filter);
    void addNodeToPath(unsigned node_var_id);
    void addEdgeToPath(unsigned edge_var_id);
    void setShortestPath(unsigned src, unsigned tgt, bool is_all_shortest = false);
};



