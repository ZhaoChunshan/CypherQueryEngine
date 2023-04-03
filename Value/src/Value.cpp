#include "Value.h"
#include <cassert>
#include <math.h>
#include <set>
#include <sstream>
#include <iostream>
using namespace std;

PGStore::Value::Value(){
    type_ = NO_VALUE;
}

PGStore::Value::Value(Type _type_):type_(_type_){
    if(_type_ == STRING){
        data_.String = new string();
    } else if(_type_ == PATH){
        data_.Path = new PathContent();
    }else if(_type_ == LIST){
        data_.List = new vector<Value *>();
    }else if(_type_ == MAP){
        data_.Map = new map<std::string, Value *>();
    }
}

PGStore::Value::Value(const Value &other){
    ConstructFrom(other);
}

PGStore::Value::Value(int_64 int_){
    type_ = INTEGER;
    data_.Int = int_;
}

PGStore::Value::Value(double float_):type_(FLOAT){
    data_.Float = float_;
}

PGStore::Value::Value(const std::string& str):type_(STRING){
    data_.String = new string(str);
}   

PGStore::Value::Value(const char* s):type_(STRING){
    data_.String = new string(s);
}

PGStore::Value::Value(bool b):type_(BOOLEAN){
    data_.Boolean = b;
}

PGStore::Value::Value(Type _type, uint_64 _id):type_(_type){
    if(_type == NODE)
        data_.Node = _id;
    else
        data_.Edge = _id;
}

PGStore::Value::Value(const PathContent &path_):type_(PATH){
    data_.Path = new PathContent();
    for(auto node :path_.node_id_){
        data_.Path->node_id_.push_back(node);
    }
    for(auto edge : path_.edge_id_){
        data_.Path->edge_id_.push_back(edge);
    }
    for(auto ty : path_.edge_type_){
        data_.Path->edge_type_.push_back(ty);
    }
}

PGStore::Value::Value(const std::vector<uint_64>& node_id, const std::vector<uint_64> &edge_id, const std::vector<EdgeType>& edge_type):type_(PATH){
    data_.Path = new PathContent();
    for(auto node :node_id){
        data_.Path->node_id_.push_back(node);
    }
    for(auto edge : edge_id){
        data_.Path->edge_id_.push_back(edge);
    }
    for(auto ty : edge_type){
        data_.Path->edge_type_.push_back(ty);
    }
}

PGStore::Value::Value(const std::vector<Value *> &list_):type_(LIST){
    data_.List = new vector<Value *>();
    for(const Value *v : list_){
        data_.List->push_back(ValueDeepCopy(v));
    }
}

PGStore::Value::Value(const std::vector<std::string> &keys, const std::vector<Value *> &values):type_(MAP) {
    data_.Map = new map<std::string, Value *>();
    uint_64 n = keys.size();
    assert(values.size() == n);
    for(uint_64 i = 0; i < n; ++i){
        data_.Map->insert(make_pair(keys[i], ValueDeepCopy(values[i])));
    }
}

PGStore::Value::~Value(){
    Destruct();
}

bool PGStore::Value::isNull() const{
    return type_ == NO_VALUE;
}

bool PGStore::Value::storable() const{
    return type_ == INTEGER || type_ == FLOAT || type_ == STRING || type_ == BOOLEAN ||
        isIntArray() || isFloatArray() || isBooleanArray() || isStringArray();
}

bool PGStore::Value::isIntArray() const{
    if(type_ != LIST) return false;

    for(const Value *v : *data_.List){
        if(v->type_ != INTEGER)
            return false;
    }

    return true;
}

bool PGStore::Value::isFloatArray() const{
    if(type_ != LIST) return false;

    for(const Value *v : *data_.List){
        if(v->type_ != INTEGER && v->type_ != FLOAT)
            return false;
    }

    return true;
}

bool PGStore::Value::isStringArray() const{
    if(type_ != LIST) return false;

    for(const Value *v : *data_.List){
        if(v->type_ != STRING)
            return false;
    }

    return true;
}

bool PGStore::Value::isBooleanArray() const{
    if(type_ != LIST) return false;

    for(const Value *v : *data_.List){
        if(v->type_ != BOOLEAN)
            return false;
    }

    return true;
}

PGStore::uint_64 PGStore::Value::convertToBytes(void * ptr){
    //TODO
    return 0;
}

void PGStore::Value::constructFromBytes(const void * ptr, uint_64 n){
    // TODO
    return;
}


PGStore::Value::Type PGStore::Value::getType() const{
    return type_;
}

PGStore::int_64 PGStore::Value::hashCode() const {
    int_64 hash = 0, seed = 131, mask = 0x7FFFFFFFFFFFFFFF;
    uint_64 n = 0;
    switch (type_)
    {
        case Value::INTEGER:
            return data_.Int & mask;
        case Value::FLOAT:
            return *(int_64 *) (&data_.Float) & mask;
        case Value::STRING:
            n = data_.String->size();
            for(uint_64 i = 0; i < n; ++i){
                hash = hash * seed + (data_.String->at(i));
            }
            return (hash & mask);
        case Value::BOOLEAN:
            return data_.Boolean ? 1 : 0;
        case Value::NODE:
            return data_.Node & mask;
        case Value::EDGE:
            return data_.Edge & mask;
        case Value::PATH:
            return 7; // Unable to hash a path.
        case Value::LIST:
            n = data_.List->size();
            for(uint_64 i = 0; i < n; ++i){
                hash = hash * seed + (data_.List->at(i)->hashCode());
            }
            return (hash & mask);
        case Value::MAP:
            return 13; // Unable to hash a map
        case Value::NO_VALUE:
            return 17;
    }
    return 131; //make g++ happy
}

bool PGStore::Value::operator==(const Value& other) const{
    switch (type_)
    {
        case Value::INTEGER:
            return IntEqualTo(other);
        case Value::FLOAT:
            return FloatEqualTo(other);
        case Value::STRING:
            return StringEqualTo(other);
        case Value::BOOLEAN:
            return BooleanEqualTo(other);
        case Value::NODE:
            return NodeEqualTo(other);
        case Value::EDGE:
            return EdgeEqualTo(other);
        case Value::PATH:
            return PathEqualTo(other);
        case Value::LIST:
            return ListEqualTo(other);
        case Value::MAP:
            return MapEqualTo(other);
        case Value::NO_VALUE:
            return NoValueEqualTo(other);
    }
    return false; //make g++ happy
}


bool PGStore::Value::operator<(const Value& other) const{
    switch (type_)
    {
        case Value::INTEGER:
            return CompareIntWith(other);
        case Value::FLOAT:
            return CompareFloatWith(other);
        case Value::STRING:
            return CompareStringWith(other);
        case Value::BOOLEAN:
            return CompareBooleanWith(other);
        case Value::NODE:
            return CompareNodeWith(other);
        case Value::EDGE:
            return CompareEdgeWith(other);
        case Value::PATH:
            return ComparePathWith(other);
        case Value::LIST:
            return CompareListWith(other);
        case Value::MAP:
            return CompareMapWith(other);
        case Value::NO_VALUE:
            return CompareNoValueWith(other);
    }
    return false;   //make g++ happy
}

PGStore::Value& PGStore::Value::operator=(const Value&other){
    if(this == &other){
        return *this;
    }
    Destruct();
    ConstructFrom(other);
    return *this;
}

void PGStore::Value::append(const PGStore::Value& value){
    data_.List->push_back(ValueDeepCopy(&value));
    return;
}

PGStore::Value& PGStore::Value::operator[](uint_64 index){
    assert(type_ == LIST and data_.List->size() > index);
    return *data_.List->at(index);
}

void PGStore::Value::insert(const std::string &key, const PGStore::Value &value){
    assert(type_ == MAP);
    data_.Map->insert(make_pair(key, ValueDeepCopy(&value)));
}

PGStore::Value * PGStore::Value::search(const std::string &key){
    assert(type_ == MAP);
    auto end = data_.Map->end();
    auto it = data_.Map->find(key);
    if(it != end){
        return it->second;
    } else {
        return nullptr;
    }
}

PGStore::uint_64 PGStore::Value::size(){
    if(type_ == STRING){
        return data_.String->size();
    }else if(type_ == LIST){
        return data_.List->size();
    }else if(type_ == MAP){
        return data_.Map->size();
    }else{
        assert(false);
    }
}

std::string PGStore::Value::toString() const {
    switch (type_)
    {
        case PGStore::Value::INTEGER:
            return to_string(data_.Int);
        case PGStore::Value::FLOAT:
            return to_string(data_.Float);
        case PGStore::Value::STRING:
            return *data_.String;
        case PGStore::Value::BOOLEAN:
            return data_.Boolean ? "true" : "false";
        case PGStore::Value::NODE:
            return string("Node(") + to_string(data_.Node) + ")";
        case PGStore::Value::EDGE:
            return string("Edge(") + to_string(data_.Edge) + ")";
        case PGStore::Value::PATH:
            return "PATH";
        case PGStore::Value::LIST:
            return "LIST";
        case PGStore::Value::MAP:
            return "<MAP>";
        case PGStore::Value::NO_VALUE:
            return "null";
    }
    return "";   //make g++ happy
}

PGStore::Value * PGStore::Value::ValueDeepCopy(const Value *value){
    Value::Type ty = value->type_;
    Value *new_elem = nullptr;
    switch (ty)
    {
        case PGStore::Value::INTEGER:
            new_elem = new PGStore::Value(value->data_.Int);
            break;
        case PGStore::Value::FLOAT:
            new_elem = new PGStore::Value(value->data_.Float);
            break;
        case PGStore::Value::STRING:
            new_elem = new PGStore::Value(*value->data_.String);
            break;
        case PGStore::Value::BOOLEAN:
            new_elem = new PGStore::Value(value->data_.Boolean);
            break;
        case PGStore::Value::NODE:
            new_elem = new PGStore::Value(Value::NODE, value->data_.Node);
            break;
        case PGStore::Value::EDGE:
            new_elem = new PGStore::Value(Value::EDGE, value->data_.Edge);
            break;
        case PGStore::Value::PATH:
            new_elem = new PGStore::Value(value->data_.Path->node_id_, value->data_.Path->edge_id_, value->data_.Path->edge_type_);
            break;
        case PGStore::Value::LIST:
            new_elem = new PGStore::Value(Value::LIST);
            for(const Value * v: *value->data_.List){
                new_elem->data_.List->push_back(ValueDeepCopy(v));
            }
            break;
        case PGStore::Value::MAP:
            new_elem = new PGStore::Value(PGStore::Value::MAP);
            for(const auto &p : *value->data_.Map){
                new_elem->data_.Map->insert(make_pair(p.first, ValueDeepCopy(p.second)));
            }
            break;
        case PGStore::Value::NO_VALUE:
            new_elem = new PGStore::Value(PGStore::Value::NO_VALUE);
            break;
    }
    return new_elem;
}

//--------------------Private--------------------//

void PGStore::Value::ConstructFrom(const PGStore::Value& other){
    // called when no string, path, list, map is allocated.
    // we neednot free them
    type_ = other.type_;
    switch (type_)
    {
        case PGStore::Value::INTEGER:
            data_.Int = other.data_.Int;
            break;
        case PGStore::Value::FLOAT:
            data_.Float = other.data_.Float;
            break;
        case PGStore::Value::STRING:
            data_.String = new string(*other.data_.String);
            break;
        case PGStore::Value::BOOLEAN:
            data_.Boolean = other.data_.Boolean;
            break;
        case PGStore::Value::NODE:
            data_.Node = other.data_.Node;
            break;
        case PGStore::Value::EDGE:
            data_.Edge = other.data_.Edge;
            break;
        case PGStore::Value::PATH:
            data_.Path = new PathContent();
            for(auto node : other.data_.Path->node_id_){
                data_.Path->node_id_.push_back(node);
            }
            for(auto edge : other.data_.Path->edge_id_){
                data_.Path->edge_id_.push_back(edge);
            }
            for(auto ty : other.data_.Path->edge_type_){
                data_.Path->edge_type_.push_back(ty);
            }
            break;
        case PGStore::Value::LIST:
            data_.List = new vector<Value *>();
            for(const PGStore::Value *v : *other.data_.List){
                data_.List->push_back(ValueDeepCopy(v));
            }
            break;
        case PGStore::Value::MAP:
            data_.Map = new map<std::string, Value *>();
            for(const auto &p : *other.data_.Map){
                data_.Map->insert(make_pair(p.first, ValueDeepCopy(p.second)));
            }
            break;
        case PGStore::Value::NO_VALUE:
            break;
    }
    return;
}

bool PGStore::Value::CompareIntWith(const PGStore::Value &other) const{
    Type ty = other.getType();
    if(ty == INTEGER ){
        return data_.Int < other.data_.Int;
    } else if( ty == FLOAT) {
        if(isinf(other.data_.Float) == 1 || isnan(other.data_.Float))
            return true;
        if(isinf(other.data_.Float) == -1)
            return false;
        return (double)data_.Int < other.data_.Float;
    } else if(ty == NO_VALUE){
        return true;
    } else {
        return false;
    }
}

bool PGStore::Value::CompareFloatWith(const Value &other) const{
    Type ty = other.getType();
    if(ty == INTEGER ){
        if(isinf(data_.Float) == 1 || isnan(data_.Float))
            return false;
        if(isinf(data_.Float) == -1)
            return true;
        return data_.Float < (double)other.data_.Int;
    } else if( ty == FLOAT) {
        if(isnan(other.data_.Float)){
            return !isnan(data_.Float);
        }
        if(isinf(other.data_.Float) == 1)
            return !(isinf(data_.Float) == 1 || isnan(data_.Float));
        if(isinf(other.data_.Float) == -1)
            return false;
        if(isnan(data_.Float) || isinf(data_.Float) == 1) return false;
        if(isinf(data_.Float) == -1)return true;
        return data_.Float < other.data_.Float;
    } else if(ty == NO_VALUE){
        return true;
    } else {
        return false;
    }
}

bool PGStore::Value::CompareStringWith(const Value &other) const{
    Type ty = other.getType();
    if(ty == STRING){
        return *data_.String < *other.data_.String;
    } else if (ty == FLOAT || ty == INTEGER || ty == NO_VALUE || ty == BOOLEAN){
        return true;
    } else {
        return false;
    }
}

bool PGStore::Value::CompareBooleanWith(const Value &other) const{
    Type ty = other.getType();
    if(ty == INTEGER || ty == FLOAT || ty == NO_VALUE) {
        return true;
    } else if(ty != BOOLEAN){
        return false;
    } else {
        return data_.Boolean ? false : other.data_.Boolean;
    }
}

bool PGStore::Value::CompareNodeWith(const Value &other) const{
    Type ty = other.getType();
    if(ty == MAP){
        return false;
    } else if(ty == NODE){
        return data_.Node < other.data_.Node;
    } else {
        return true;
    }
}

bool PGStore::Value::CompareEdgeWith(const Value &other) const{
    Type ty = other.getType();
    if(ty == MAP || ty == NODE){
        return false;
    } else if(ty == EDGE){
        return data_.Edge < other.data_.Edge;
    } else {
        return true;
    }
}

bool PGStore::Value::ComparePathWith(const Value &other) const{
    int m = data_.Path->edge_id_.size(), n = other.data_.Path->edge_id_.size();
    int l = m < n ? m : n;
    for(int i = 0; i < l; ++i){
        if(data_.Path->node_id_[i] != other.data_.Path->node_id_[i]) 
        return data_.Path->node_id_[i] < other.data_.Path->node_id_[i];
        if(data_.Path->edge_id_[i] != other.data_.Path->edge_id_[i]) continue;
        return data_.Path->edge_id_[i] < other.data_.Path->edge_id_[i];
    }
    if(data_.Path->node_id_[l] != other.data_.Path->node_id_[l])
        return data_.Path->node_id_[l] < other.data_.Path->node_id_[l];
    return m < n;
}

bool PGStore::Value::CompareListWith(const Value &other) const{
    Type ty = other.getType();
    if(ty == MAP || ty == NODE || ty == EDGE){
        return false;
    } else if(ty != LIST){
        return true;
    }
    // ty is LIST
    uint_64 m = data_.List->size(), n = other.data_.List->size();
    uint_64 l = m > n ? n : m;
    for(uint_64 i = 0; i < l; ++i){
        if(*data_.List->at(i) == *other.data_.List->at(i)){
            continue;
        }
        return *data_.List->at(i) < *other.data_.List->at(i);
    }
    return m < n;
}

bool PGStore::Value::CompareMapWith(const Value &other) const{
    Type ty = other.getType();
    if(ty != MAP)
        return true;
    // Not define yet
    return false;
}

bool PGStore::Value::CompareNoValueWith(const Value &other) const{
    return false;
}


bool PGStore::Value::IntEqualTo(const Value &other) const{
    return other.getType() == INTEGER && data_.Int == other.data_.Int ||
        other.getType() == FLOAT && data_.Int == other.data_.Float;
}

bool PGStore::Value::FloatEqualTo(const Value &other) const{
    return other.getType() == FLOAT && data_.Float == other.data_.Float ||
        other.getType() == INTEGER && data_.Float == other.data_.Int;
}

bool PGStore::Value::StringEqualTo(const Value &other) const{
    return other.getType() == STRING && *data_.String == *other.data_.String;
}

bool PGStore::Value::BooleanEqualTo(const Value &other) const{
    return other.getType() == BOOLEAN && data_.Boolean == other.BOOLEAN;
}

bool PGStore::Value::NodeEqualTo(const Value &other) const{
    return other.getType() == NODE && other.data_.Node == data_.Node;
}

bool PGStore::Value::EdgeEqualTo(const Value &other) const{
    return other.getType() == EDGE && data_.Edge == other.data_.Edge;
}

bool PGStore::Value::PathEqualTo(const Value &other) const{
    // just check [n0 e1 n1 e2 n2 .. ek nk]
    if(other.data_.Path->edge_id_.size() != data_.Path->edge_id_.size()) return false;
    uint_64 n = data_.Path->edge_id_.size();

    for(int i = 0; i < n; ++i){
        if(other.data_.Path->edge_id_[i] != data_.Path->edge_id_[i] || 
           other.data_.Path->node_id_[i] != data_.Path->node_id_[i]){
            return false;
        }
    }

    return other.data_.Path->node_id_[n] == data_.Path->node_id_[n];
}

bool PGStore::Value::ListEqualTo(const Value &other) const{
    uint_64 n = data_.List->size();
    if(other.data_.List->size() != n){
        return false;
    }
    for(uint_64 i = 0; i < n; ++i){
        if( !( *other.data_.List->at(i) == *data_.List->at(i) ) ){
            return false;
        }
    }
    return true;
}

bool PGStore::Value::MapEqualTo(const Value &other) const{
    uint_64 m = data_.Map->size(), n = other.data_.Map->size();
    if(m != n) {
        return false;
    }
    for(const auto &p : *data_.Map){
        const string & k = p.first;
        Value *v = p.second;
        if(other.data_.Map->find(k) == other.data_.Map->end() ||
            !(*other.data_.Map->at(k) == *v) ){
                return false;
        }
    }
    return true;
}

bool PGStore::Value::NoValueEqualTo(const Value &other) const{
    return other.getType() == NO_VALUE;
}

void PGStore::Value::Destruct(){
    switch (type_)
    {
        case Value::STRING:
            delete data_.String;
            break;
        case Value::PATH:
            delete data_.Path;
            break;
        case Value::LIST:
            for(Value *v : *data_.List){
                if(v != nullptr){
                    delete v;
                }
            }
            delete data_.List;
            break;
        case Value::MAP:
            for(const auto &p : *data_.Map){
                if(p.second != nullptr){
                    delete p.second;
                }
            }
            delete data_.Map;
            break;
        default:
            break;
    }
    return;
}

