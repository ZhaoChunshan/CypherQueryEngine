#include "Pattern.h"
#include <iostream>
#include <cstdio>

GPStore::NodePattern::NodePattern():type_(NODE_VAR), is_anno_var_(false){

}

GPStore::NodePattern::NodePattern(bool _is_anno, std::string var_name, unsigned _var_id):type_(NODE_VAR){
    is_anno_var_ = _is_anno;
    var_name_ = var_name;
    var_id_ = _var_id;
}

GPStore::NodePattern::NodePattern(std::string _constant_str):type_(NODE_CONST), is_anno_var_(false), constant_str_(_constant_str){

}

GPStore::NodePattern::NodePattern(const NodePattern& that):type_(that.type_), is_anno_var_(that.is_anno_var_), \
var_name_(that.var_name_), constant_str_(that.constant_str_), var_id_(that.var_id_), labels_(that.labels_), properties_(that.properties_), prop_id_(that.prop_id_),param_str_(that.param_str_){

}

GPStore::NodePattern& 
GPStore::NodePattern::operator=(const NodePattern& that){
    type_ = that.type_;
    is_anno_var_ = that.is_anno_var_;
    var_name_ = that.var_name_;
    constant_str_ = that.constant_str_;
    var_id_ = that.var_id_;
    labels_ = that.labels_;
    properties_ = that.properties_;
    prop_id_ = that.prop_id_;
    param_str_ = that.param_str_;
    return *this;
}

GPStore::NodePattern::~NodePattern(){

}

bool GPStore::NodePattern::constraintEmpty() const{ 
    return labels_.size() == 0 && properties_.size() == 0 && param_str_.size() == 0;
}

void GPStore::NodePattern::print() const{
    if(type_ == NODE_CONST){
        std::printf("(%s)\n", constant_str_);
        return;
    }
    
    std::printf("(%s (id:%u) ", var_name_.c_str(), var_id_);
    for(const auto& l : labels_){
        std::printf(" :%s",l.c_str());
    }
    if(properties_.size() != 0){
        std::printf(")  Properties:\n");

        for(const auto& p : properties_){
            std::printf("%s:\n", p.first.c_str());
            p.second.print(0);
        }
    } else if(param_str_.size() != 0){
        std::printf("  $%s)\n", param_str_.c_str());
    }
    else{
        std::printf(")\n");
    }
}


GPStore::EdgePattern::EdgePattern():type_(EDGE_VAR), arrow_direction_(RIGHT_ARROW), is_anno_var_(false), is_edge_length_v_(false), range_left_(1), range_right_(1){

}

GPStore::EdgePattern::EdgePattern(bool is_anno, std::string _var_name, unsigned _var_id, EdgeArrowType _direction):type_(EDGE_VAR), arrow_direction_(_direction), is_anno_var_(is_anno), \
var_name_(_var_name), var_id_(_var_id), is_edge_length_v_(false), range_left_(1), range_right_(1){

}

GPStore::EdgePattern::EdgePattern(bool is_anno, std::string _var_name, unsigned _var_id, EdgeArrowType _direction, unsigned long long _left, unsigned long long _right):type_(EDGE_VAR), arrow_direction_(_direction), is_anno_var_(is_anno), \
var_name_(_var_name), var_id_(_var_id), is_edge_length_v_(true), range_left_(_left), range_right_(_right){

}

GPStore::EdgePattern::EdgePattern(std::string constant_str):type_(EDGE_CONST), arrow_direction_(RIGHT_ARROW), is_anno_var_(false), \
constant_str_(constant_str), is_edge_length_v_(false), range_left_(1), range_right_(1){

}

GPStore::EdgePattern::EdgePattern(const EdgePattern& that):type_(that.type_), arrow_direction_(that.arrow_direction_), \
is_anno_var_(that.is_anno_var_), var_name_(that.var_name_), constant_str_(that.constant_str_), var_id_(that.var_id_), \
is_edge_length_v_(that.is_edge_length_v_), range_left_(that.range_left_), range_right_(that.range_right_), \
edge_types_(that.edge_types_), properties_(that.properties_), prop_id_(that.prop_id_),param_str_(that.param_str_){

}

GPStore::EdgePattern& GPStore::EdgePattern::operator=(const EdgePattern& that){
    type_ = that.type_;
    arrow_direction_ = that.arrow_direction_;
    is_anno_var_ = that.is_anno_var_;
    var_name_ = that.var_name_;
    constant_str_ = that.constant_str_;
    var_id_ = that.var_id_;
    is_edge_length_v_ = that.is_edge_length_v_;
    range_left_ = that.range_left_;
    range_right_ = that.range_right_;
    edge_types_ = that.edge_types_;
    properties_ = that.properties_;
    prop_id_ = that.prop_id_;
    param_str_ = that.param_str_;
    return *this;
}

GPStore::EdgePattern::~EdgePattern(){

}

bool GPStore::EdgePattern::constraintEmpty() const{ 
    return edge_types_.size() == 0 && properties_.size() == 0 && param_str_.size() == 0;
}


void GPStore::EdgePattern::print() const{
    if(type_ == EDGE_CONST){
        std::printf("-[%s]->\n", constant_str_.c_str());
        return;
    }
    if(arrow_direction_ != LEFT_ARROW){
        std::printf("-[");
    }else{
        std::printf("<-[");
    }

    std::printf("%s(id:%u)", var_name_.c_str(), var_id_);
    for(const auto& t : edge_types_){
        std::printf(" :%s",t.c_str());
    }

    if(arrow_direction_ != RIGHT_ARROW){
        std::printf("]-");
    }else{
        std::printf("]->");
    }
    if(properties_.size() != 0){
        std::printf("  Properties:\n");
        for(const auto& p : properties_){
            std::printf("%s:\n", p.first);
            p.second.print(0);
        }
    }else{
        std::printf("\n");
    }
}


GPStore::RigidPattern::RigidPattern(){

}

GPStore::RigidPattern::RigidPattern(const GPStore::NodePattern& node):type_(PATH), 
is_anno_var_(true){
    nodes_.emplace_back(node);
    covered_node_var_id_.addVar(node.var_id_);
    covered_var_id_.addVar(node.var_id_);
}

GPStore::RigidPattern::RigidPattern(const RigidPattern& that):type_(that.type_),
var_name_(that.var_name_), var_id_(that.var_id_), is_anno_var_(that.is_anno_var_),
nodes_(that.nodes_), edges_(that.edges_), covered_var_id_(that.covered_var_id_), covered_node_var_id_(that.covered_node_var_id_), covered_edge_var_id_(that.covered_edge_var_id_){

}

GPStore::RigidPattern& GPStore::RigidPattern::operator=(const RigidPattern& that){
    type_ = that.type_;
    var_name_ = that.var_name_;
    var_id_ = that.var_id_;
    is_anno_var_ = that.is_anno_var_;
    nodes_ = that.nodes_;
    edges_ = that.edges_;
    covered_var_id_ = that.covered_var_id_;
    covered_node_var_id_ = that.covered_node_var_id_;
    covered_edge_var_id_ = that.covered_edge_var_id_;
    return *this;
}

GPStore::RigidPattern::~RigidPattern(){

}

void GPStore::RigidPattern::print() const{
    std::printf("Rigid Pattern:\n");
    unsigned int n = edges_.size();
    nodes_.at(0).print();
    for(unsigned i = 0; i < n; ++i){
        edges_.at(i).print();
        nodes_.at(i + 1).print();
    }
}