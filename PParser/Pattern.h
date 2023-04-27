#ifndef PPARSER_PATTERN_H
#define PPARSER_PATTERN_H

#include <string>
#include <vector>
#include <map>
/* make it able to be compiled */
namespace GPStore{
class NodePattern;
class EdgePattern;
class RigidPattern;
}
#include "../PQuery/PVarset.h"
#include "../Value/Expression.h"
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

    // for update clauses, may be parameters, e.g. CREATE (a $prop)
    std::map<std::string, GPStore::Expression> properties_;
    std::map<std::string, unsigned> prop_id_;
    std::string param_str_;

    NodePattern();
    NodePattern(bool _is_anno, std::string var_name, unsigned _var_id);
    NodePattern(std::string _constant_str);
    NodePattern(const NodePattern& that);
    NodePattern& operator=(const NodePattern& that);
    bool constraintEmpty() const;
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
    std::map<std::string, Expression> properties_;
    std::map<std::string, unsigned> prop_id_;
    std::string param_str_;
    EdgePattern();
    EdgePattern(bool is_anno, std::string _var_name, unsigned _var_id, EdgeArrowType _direction);
    EdgePattern(bool is_anno, std::string _var_name, unsigned _var_id, EdgeArrowType _direction, unsigned long long _left, unsigned long long _right);
    EdgePattern(std::string constant_str);
    EdgePattern(const EdgePattern& that);
    EdgePattern& operator= (const EdgePattern& that);
    bool constraintEmpty() const;
    ~EdgePattern();

    void print() const;

};


// Support both SPARQL Triple Pattern && Cypher Path Pattern
class RigidPattern{
public:
    enum RigidPatternType {PATH, SHORTEST_PATH, ALL_SHORTEST_PATHS };
    RigidPatternType type_;

    // only named var has var_name
    std::string var_name_;
    // only named var has var_id
    unsigned var_id_;

    bool is_anno_var_;

    std::vector<NodePattern> nodes_;
    std::vector<EdgePattern> edges_;

    // Named node vars and named edge vars
    PVarset<unsigned> covered_var_id_;
    PVarset<unsigned> covered_node_var_id_;
    PVarset<unsigned> covered_edge_var_id_;
    RigidPattern();
    RigidPattern(const NodePattern& node);
    RigidPattern(const RigidPattern& that);
    RigidPattern& operator=(const RigidPattern& that);
    ~RigidPattern();

    void print() const;
};

} // namespace GPStore

#endif