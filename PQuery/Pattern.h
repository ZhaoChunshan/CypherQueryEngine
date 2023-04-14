#include <string>
#include <vector>
#include <map>
#include "../Value/Expression.h"
#include "Varset.h"

namespace GPStore{

// Support both SPARQL && Cypher NodeVar
class NodePattern{
public:
    // Only SPARQL has constant
    enum NodePatternType { NODE_VAR, NODE_CONST };
    
    NodePatternType type_;
    bool is_anno_var_;
    // we give anno var name such as @anno_1
    std::string var_name_;  
    // For constant only
    std::string constant_str_;
    // For constant, it's id in kvstore; For variable, it's
    // Just a one to one map from var_name_ to var_id_
    // For the convinience of edge conflict && filter injection
    unsigned var_id_;                

    // used for node_var and edge_var
    std::vector<std::string> labels_;

    // for update clauses, may be parameters, e.g. CREATE (a $1)
    std::map<std::string, GPStore::Expression> properties_;

    NodePattern();
    NodePattern(bool _is_anno, std::string var_name, unsigned _var_id);
    NodePattern(std::string _constant_str);
    NodePattern(const NodePattern& that);
    NodePattern& operator=(const NodePattern& that);

    ~NodePattern();

    void print() const;
};


// Support both SPARQL && Cypher EdgeVar
class EdgePattern{
public:
    // Only SPARQL has constant
    enum EdgePatternType { EDGE_VAR, EDGE_CONST };
    enum EdgeArrowType { LEFT_ARROW, RIGHT_ARROW, UNDIRECTED };

    EdgePatternType type_;
    EdgeArrowType arrow_direction_;

    bool is_anno_var_;
    // we give anno var name such as @anno_1
    std::string var_name_;  
    // For constant only
    std::string constant_str_;
    // For constant, it's id in kvstore; For variable, it's
    // Just a one to one map from var_name_ to var_id_
    // For the convinience of edge conflict && filter injection
    unsigned var_id_;           

    bool is_edge_length_v_; // variable-length pattern
    unsigned long long range_left_, range_right_;
    static const unsigned long long RANGE_INF = 0xffffffffffffffffULL;

    // used for node_var and edge_var
    std::vector<std::string> edge_types_;

    // for update clauses, may be parameters, e.g. CREATE (a $1)
    std::map<std::string, GPStore::Expression> properties_;

    EdgePattern();
    EdgePattern(bool is_anno, std::string _var_name, unsigned _var_id, EdgeArrowType _direction);
    EdgePattern(bool is_anno, std::string _var_name, unsigned _var_id, EdgeArrowType _direction, unsigned long long _left, unsigned long long _right);
    EdgePattern(std::string constant_str);
    EdgePattern(const EdgePattern& that);
    EdgePattern& operator= (const EdgePattern& that);

    ~EdgePattern();

    void print() const;

};


// Support both SPARQL Triple Pattern && Cypher Path Pattern
class RigidPattern{
    // only named path var has var_name
    std::string var_name_;
    // only named path var has var_id
    unsigned var_id_;

    bool is_anno_var_;

    std::vector<NodePattern> nodes_;
    std::vector<EdgePattern> edges_;

    // Named node vars and named edge vars
    Varset covered_vars_;
    Varset covered_node_vars_;
    Varset covered_edge_vars_;
    RigidPattern();
    RigidPattern(const RigidPattern& that);
    RigidPattern& operator=(const RigidPattern& that);
    ~RigidPattern();

    void print() const;
};

} // namespace GPStore