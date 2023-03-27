#include "Value.h"
#include <cassert>
#include <math.h>
#include <set>
#include <sstream>
#include <iostream>
using namespace std;

Value::Value(){
    type_ = NO_VALUE;
}

Value::Value(Type _type_):type_(_type_){
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

Value::Value(const Value &other){
    ConstructFrom(other);
}

Value::Value(int_64 int_){
    type_ = INTEGER;
    data_.Int = int_;
}

Value::Value(double float_):type_(FLOAT){
    data_.Float = float_;
}

Value::Value(const std::string& str):type_(STRING){
    data_.String = new string(str);
}   

Value::Value(const char* s):type_(STRING){
    data_.String = new string(s);
}

Value::Value(bool b):type_(BOOLEAN){
    data_.Boolean = b;
}

Value::Value(Type _type, uint_64 _id):type_(_type){
    if(_type == NODE)
        data_.Node = _id;
    else
        data_.Edge = _id;
}

Value::Value(const PathContent &path_):type_(PATH){
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

Value::Value(const std::vector<uint_64>& node_id, const std::vector<uint_64> &edge_id, const std::vector<EdgeType>& edge_type):type_(PATH){
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

Value::Value(const std::vector<Value *> &list_):type_(LIST){
    data_.List = new vector<Value *>();
    for(const Value *v : list_){
        data_.List->push_back(ValueDeepCopy(v));
    }
}

Value::Value(const std::vector<std::string> &keys, const std::vector<Value *> &values):type_(MAP) {
    data_.Map = new map<std::string, Value *>();
    uint_64 n = keys.size();
    assert(values.size() == n);
    for(uint_64 i = 0; i < n; ++i){
        data_.Map->insert(make_pair(keys[i], ValueDeepCopy(values[i])));
    }
}

Value::~Value(){
    Destruct();
}

bool Value::isNull() const{
    return type_ == NO_VALUE;
}

bool Value::storable() const{
    return type_ == INTEGER || type_ == FLOAT || type_ == STRING || type_ == BOOLEAN ||
        isIntArray() || isFloatArray() || isBooleanArray() || isStringArray();
}

bool Value::isIntArray() const{
    if(type_ != LIST) return false;

    for(const Value *v : *data_.List){
        if(v->type_ != INTEGER)
            return false;
    }

    return true;
}

bool Value::isFloatArray() const{
    if(type_ != LIST) return false;

    for(const Value *v : *data_.List){
        if(v->type_ != INTEGER && v->type_ != FLOAT)
            return false;
    }

    return true;
}

bool Value::isStringArray() const{
    if(type_ != LIST) return false;

    for(const Value *v : *data_.List){
        if(v->type_ != STRING)
            return false;
    }

    return true;
}

bool Value::isBooleanArray() const{
    if(type_ != LIST) return false;

    for(const Value *v : *data_.List){
        if(v->type_ != BOOLEAN)
            return false;
    }

    return true;
}

uint_64 Value::convertToBytes(void * ptr){
    //TODO
    return 0;
}

void Value::constructFromBytes(const void * ptr, uint_64 n){
    // TODO
    return;
}


Value::Type Value::getType() const{
    return type_;
}

int_64 Value::hashCode() const {
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
}

bool Value::operator==(const Value& other) const{
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
}


bool Value::operator<(const Value& other) const{
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
}

Value& Value::operator=(const Value&other){
    if(this == &other){
        return *this;
    }
    Destruct();
    ConstructFrom(other);
    return *this;
}

void Value::append(const Value& value){
    data_.List->push_back(ValueDeepCopy(&value));
    return;
}

Value& Value::operator[](uint_64 index){
    assert(type_ == LIST and data_.List->size() > index);
    return *data_.List->at(index);
}

void Value::insert(const std::string &key, const Value &value){
    assert(type_ == MAP);
    data_.Map->insert(make_pair(key, ValueDeepCopy(&value)));
}

Value * Value::search(const std::string &key){
    assert(type_ == MAP);
    auto end = data_.Map->end();
    auto it = data_.Map->find(key);
    if(it != end){
        return it->second;
    } else {
        return nullptr;
    }
}

uint_64 Value::size(){
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

std::string Value::toString() const {
    switch (type_)
    {
        case Value::INTEGER:
            return to_string(data_.Int);
        case Value::FLOAT:
            return to_string(data_.Float);
        case Value::STRING:
            return *data_.String;
        case Value::BOOLEAN:
            return data_.Boolean ? "true" : "false";
        case Value::NODE:
            return string("Node(") + to_string(data_.Node) + ")";
        case Value::EDGE:
            return string("Edge(") + to_string(data_.Edge) + ")";
        case Value::PATH:
            return "PATH";
        case Value::LIST:
            return "LIST";
        case Value::MAP:
            return "<MAP>";
        case Value::NO_VALUE:
            return "null";
    }
}

Value * Value::ValueDeepCopy(const Value *value){
    Value::Type ty = value->type_;
    Value *new_elem = nullptr;
    switch (ty)
    {
        case Value::INTEGER:
            new_elem = new Value(value->data_.Int);
            break;
        case Value::FLOAT:
            new_elem = new Value(value->data_.Float);
            break;
        case Value::STRING:
            new_elem = new Value(*value->data_.String);
            break;
        case Value::BOOLEAN:
            new_elem = new Value(value->data_.Boolean);
            break;
        case Value::NODE:
            new_elem = new Value(Value::NODE, value->data_.Node);
            break;
        case Value::EDGE:
            new_elem = new Value(Value::EDGE, value->data_.Edge);
            break;
        case Value::PATH:
            new_elem = new Value(value->data_.Path->node_id_, value->data_.Path->edge_id_, value->data_.Path->edge_type_);
            break;
        case Value::LIST:
            new_elem = new Value(Value::LIST);
            for(const Value * v: *value->data_.List){
                new_elem->data_.List->push_back(ValueDeepCopy(v));
            }
            break;
        case Value::MAP:
            new_elem = new Value(Value::MAP);
            for(const auto &p : *value->data_.Map){
                new_elem->data_.Map->insert(make_pair(p.first, ValueDeepCopy(p.second)));
            }
            break;
        case Value::NO_VALUE:
            new_elem = new Value(Value::NO_VALUE);
            break;
    }
    return new_elem;
}

//--------------------Private--------------------//

void Value::ConstructFrom(const Value& other){
    // called when no string, path, list, map is allocated.
    // we neednot free them
    type_ = other.type_;
    switch (type_)
    {
        case Value::INTEGER:
            data_.Int = other.data_.Int;
            break;
        case Value::FLOAT:
            data_.Float = other.data_.Float;
            break;
        case Value::STRING:
            data_.String = new string(*other.data_.String);
            break;
        case Value::BOOLEAN:
            data_.Boolean = other.data_.Boolean;
            break;
        case Value::NODE:
            data_.Node = other.data_.Node;
            break;
        case Value::EDGE:
            data_.Edge = other.data_.Edge;
            break;
        case Value::PATH:
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
        case Value::LIST:
            data_.List = new vector<Value *>();
            for(const Value *v : *other.data_.List){
                data_.List->push_back(ValueDeepCopy(v));
            }
            break;
        case Value::MAP:
            data_.Map = new map<std::string, Value *>();
            for(const auto &p : *other.data_.Map){
                data_.Map->insert(make_pair(p.first, ValueDeepCopy(p.second)));
            }
            break;
        case Value::NO_VALUE:
            break;
    }
    return;
}

// /* Class: Value */


// /* Class: IntValue */

// IntValue::IntValue() {

// }

// IntValue::IntValue(int_64 v) {
//     data.Int = v;
// }

// IntValue::IntValue(const Value& other) {
//     assert(other.getType() == INTEGER);
//     data.Int = other.data.Int;
// }


// IntValue::~IntValue() {

// }

// Value& IntValue::operator=(const Value& other){
//     assert(other.getType() == INTEGER);
//     data.Int = other.data.Int;
//     return *this;
// }

// Value::Type IntValue::getType() const{
//     return Value::INTEGER;
// }



// bool IntValue::operator==(const Value& other) const {
//     return other.getType() == INTEGER && data.Int == other.data.Int ||
//         other.getType() == FLOAT && data.Int == other.data.Float;
// }

// bool IntValue::operator<(const Value& other) const {
//     Type ty = other.getType();
//     if(ty == INTEGER ){
//         return data.Int < other.data.Int;
//     } else if( ty == FLOAT) {
//         if(isinf(other.data.Float) == 1 || isnan(other.data.Float))
//             return true;
//         if(isinf(other.data.Float) == -1)
//             return false;
//         return data.Int < other.data.Float;
//     } else if(ty == NO_VALUE){
//         return true;
//     } else {
//         return false;
//     }
// }

// std::string IntValue::toString() const{
//     return to_string(data.Int);
// }

// /* Class: FloatValue */

// FloatValue::FloatValue(){

// }

// FloatValue::FloatValue(double v) {
//     data.Float = v;
// }

// /**
//  * @param other: Integer Value or Float Value
// */
// FloatValue::FloatValue(const Value &other) {
//     Type ty = other.getType();
//     assert(ty == INTEGER || ty == FLOAT);
//     if(ty == INTEGER){
//         data.Float = (double)other.data.Int;
//     } else {
//         data.Float = other.data.Float;
//     }
// }

// FloatValue::~FloatValue(){

// }

// Value& FloatValue::operator=(const Value& other){
//     Type ty = other.getType();
//     assert(ty == INTEGER || ty == FLOAT);
//     if(ty == INTEGER){
//         data.Float = (double)other.data.Int;
//     } else {
//         data.Float = other.data.Float;
//     }
//     return *this;
// }

// Value::Type FloatValue::getType() const{
//     return Value::FLOAT;
// }



// bool FloatValue::operator==(const Value& other) const{
//     return other.getType() == FLOAT && data.Float == other.data.Float;
// }

// bool FloatValue::operator<(const Value& other) const{
//     Type ty = other.getType();
//     if(ty == INTEGER ){
//         if(isinf(data.Float) == 1 || isnan(data.Float))
//             return false;
//         if(isinf(data.Float) == -1)
//             return true;
//         return data.Float < other.data.Int;
//     } else if( ty == FLOAT) {
//         if(isnan(other.data.Float)){
//             return !isnan(data.Float);
//         }
//         if(isinf(other.data.Float) == 1)
//             return !(isinf(data.Float) == 1 || isnan(data.Float));
//         if(isinf(other.data.Float) == -1)
//             return false;
//         if(isnan(data.Float) || isinf(data.Float) == 1) return false;
//         if(isinf(data.Float) == -1)return true;
//         return data.Float < other.data.Float;
//     } else if(ty == NO_VALUE){
//         return true;
//     } else {
//         return false;
//     }
// }

// std::string FloatValue::toString() const{
//     return to_string(data.Float);
// }   

// /* Class: StringValue */

// StringValue::StringValue(){
//     data.String = new string();
// }

// StringValue::StringValue(const std::string &s){
//     data.String = new string(s);
// }

// StringValue::StringValue(const Value& other){
//     assert(other.getType() == STRING);
//     data.String = new string(*other.data.String);
// }

// StringValue::~StringValue(){
//     if(data.String != nullptr)
//         delete data.String;
// }

// Value& StringValue::operator=(const Value& other){
//     assert(other.getType() == STRING);
//     *data.String = *other.data.String;
//     return *this;
// }

// Value::Type StringValue::getType() const{
//     return Value::STRING;
// }


// bool StringValue::operator==(const Value& other) const{
//     return other.getType() == STRING && *data.String == *other.data.String;
// }

// bool StringValue::operator<(const Value& other) const{
//     Type ty = other.getType();
//     if(ty == STRING){
//         return *data.String < *other.data.String;
//     } else if (ty == FLOAT || ty == INTEGER || ty == NO_VALUE || ty == BOOLEAN){
//         return true;
//     } else {
//         return false;
//     }
// }

// std::string StringValue::toString() const{
//     return *data.String;
// }   


// /* Class: BooleanValue */

// BooleanValue::BooleanValue(){

// }

// BooleanValue::BooleanValue(bool v){
//     data.Boolean = v;
// }

// BooleanValue::BooleanValue(const Value& other){
//     assert(other.getType() == BOOLEAN);
//     data.Boolean = other.data.Boolean;
// }

// BooleanValue::~BooleanValue(){

// }

// Value& BooleanValue::operator=(const Value& other){
//     assert(other.getType() == BOOLEAN);
//     data.Boolean = other.data.Boolean;
//     return *this;
// }

// Value::Type BooleanValue::getType() const{
//     return BOOLEAN;
// }

// int_64 BooleanValue::hashCode() const{
//     return data.Boolean ? 1 : 0;
// }

// bool BooleanValue::operator==(const Value& other) const{
//     return other.getType() == BOOLEAN && data.Boolean == other.BOOLEAN;
// }   

// bool BooleanValue::operator<(const Value& other) const{
//     Type ty = other.getType();
//     if(ty == INTEGER || ty == FLOAT || ty == NO_VALUE) {
//         return true;
//     } else if(ty != BOOLEAN){
//         return false;
//     } else {
//         return data.Boolean ? false : other.data.Boolean;
//     }
// }

// std::string BooleanValue::toString() const{
//     return data.Boolean ? "true":"false";
// }

// /* Class: IntArray */

// IntArray::IntArray(){
//     data.IntArray = new vector<int_64>();
// }

// /**
//  * @param v: another IntArray, or List of integer Value
// */
// IntArray::IntArray(const Value &v){
//     Type ty = v.getType();
//     assert(ty == INTEGER_ARRAY || ty == LIST);
//     data.IntArray = new vector<int_64>();
//     if(ty == INTEGER_ARRAY){
//         for(auto i : *v.data.IntArray){
//             data.IntArray->push_back(i);
//         }
//     } else if(ty == LIST){
//         uint_64 n = v.data.List->size();
//         for(uint_64 i = 0; i < n; ++i){
//             Value *elem = v.data.List->at(i);
//             if(elem->getType() != INTEGER){
//                 delete data.IntArray;
//                 assert(false);
//             } else {
//                 data.IntArray->push_back(elem->data.Int);
//             }
//         }
//     }
// }

// IntArray::IntArray(const std::vector<int_64> &int_vec){
//     data.IntArray = new vector<int_64>();
//     for(auto in : int_vec){
//         data.IntArray->push_back(in);
//     }
// }

// IntArray::~IntArray(){
//     if(data.IntArray != nullptr)
//         delete data.IntArray;
// }

// /**
//  * @param other: IntArray, or List of integer Value
// */
// Value& IntArray::operator=(const Value& other){
//     if(other.getType() == INTEGER_ARRAY){
//         if(this == &other) return *this;
//         data.IntArray->clear();
//         for(int_64 i : *other.data.IntArray){
//             data.IntArray->push_back(i);
//         }
//     } else if(other.getType() == LIST) {
//         data.IntArray->clear();
//         uint_64 n = other.data.List->size();
//         for(uint_64 i = 0; i < n; ++i){
//             Value *elem = other.data.List->at(i);
//             if(elem->getType() != INTEGER){
//                 assert(false);
//             } else {
//                 data.IntArray->push_back(elem->data.Int);
//             }
//         }
//     } else {
//         assert(false);
//     }
//     return *this;
// }

// Value::Type IntArray::getType() const{
//     return INTEGER_ARRAY;
// }

// /* Array Type only used for storage */
// int_64 IntArray::hashCode() const{
//     assert(false);
//     return 0;
// }

// /* Array Type only used for storage */
// bool IntArray::operator==(const Value& other) const{
//     assert(false);
//     return true;
// }

// /* Array Type only used for storage */
// bool IntArray::operator<(const Value& other) const{
//     assert(false);
//     return true;
// }

// void IntArray::append(int_64 integer){
//     data.IntArray->push_back(integer);
// }

// std::string IntArray::toString() const{
//     stringstream buf;
//     buf << "IntArray(length: " << data.IntArray->size() <<")";
//     return buf.str();
// }

// /* Class: FloatArray */

// FloatArray::FloatArray(){

// }

// /**
//  * @param v: FLoatArray, or List containing Integer&Float
// */
// FloatArray::FloatArray(const Value &v){
//     Type ty = v.getType();
//     assert(ty == FLOAT_ARRAY || ty == LIST);
//     data.FloatArray = new vector<double>();
//     if(ty == FLOAT_ARRAY){
//         for(auto i : *v.data.FloatArray){
//             data.FloatArray->push_back(i);
//         }
//     } else if(ty == LIST){
//         uint_64 n = v.data.List->size();
//         for(uint_64 i = 0; i < n; ++i){
//             Value *elem = v.data.List->at(i);
//             if(elem->getType() == FLOAT){
//                 data.FloatArray->push_back(elem->data.Float);
//             } else if(elem->getType() == INTEGER){
//                 data.FloatArray->push_back((double)elem->data.Int);
//             }
//             else {
//                 delete data.FloatArray;
//                 assert(false);
//             }
//         }
//     }
// }

// FloatArray::FloatArray(const std::vector<double> &double_vec){
//     data.FloatArray = new vector<double>();
//     for(auto d : double_vec){
//         data.FloatArray->push_back(d);
//     }
// }

// FloatArray::~FloatArray(){
//     if(data.FloatArray != nullptr)
//         delete data.FloatArray;
// }

// /**
//  * @param other: FLoatArray, or List containing Integer&Float
// */
// Value& FloatArray::operator=(const Value& other){
//     Type ty = other.getType();
//     if(ty == FLOAT_ARRAY){
//         if(this == &other) return *this;
//         data.FloatArray->clear();
//         for(auto d : *other.data.FloatArray){
//             data.FloatArray->push_back(d);
//         }
//     } else if(ty == LIST){
//         uint_64 n = other.data.FloatArray->size();
//         data.FloatArray->clear();
//         for(uint_64 i = 0; i < n; ++i){
//             Value *elem = other.data.List->at(i);
//             if(elem->getType() == FLOAT){
//                 data.FloatArray->push_back(elem->data.Float);
//             } else if(elem->getType() == INTEGER){
//                 data.FloatArray->push_back((double)elem->data.Int);
//             }
//             else{
//                 assert(false);
//             }
//         }
//     } else {
//         assert(false);
//     }
// }

// Value::Type FloatArray::getType() const{
//     return FLOAT_ARRAY;
// }

// /* Array Type only used for storage */
// int_64 FloatArray::hashCode() const{
//     assert(false);
//     return 0;
// }

// /* Array Type only used for storage */
// bool FloatArray::operator==(const Value& other) const{
//     assert(false);
//     return true;
// }

// /* Array Type only used for storage */
// bool FloatArray::operator<(const Value& other) const{
//     assert(false);
//     return true;
// }

// void FloatArray::append(double _float){
//     data.FloatArray->push_back(_float);
// }

// std::string FloatArray::toString() const{
//     stringstream buf;
//     buf << "FloatArray(length: " << data.FloatArray->size() <<")";
//     return buf.str();
// }

// /* Class: StringArray */

// StringArray::StringArray(){
//     data.StringArray = new vector<string>();
// }

// /**
//  * @param v: StringArray, or List of String
// */
// StringArray::StringArray(const Value &v){
//     Type ty = v.getType();
//     if(ty == STRING_ARRAY){
//         data.StringArray = new vector<string>();
//         for(const string& s : *v.data.StringArray){
//             data.StringArray->emplace_back(s);
//         }
//     } else if (ty == LIST){
//         data.StringArray = new vector<string>();
//         for(Value *elem : *v.data.List){
//             if(elem->getType() == STRING){
//                 data.StringArray->emplace_back(*elem->data.String);
//             }
//         }
//     } else{
//         delete data.StringArray;
//         assert(false);
//     }
// }

// StringArray::StringArray(const std::vector<std::string> &string_vec){
//     data.StringArray = new vector<string>();
//     for(const string& s : string_vec){
//         data.StringArray->emplace_back(s);
//     }
// }

// StringArray::~StringArray(){
//     if(data.StringArray != nullptr)
//         delete data.StringArray;
// }

// /**
//  * @param other: StringArray, or List of String
// */
// Value& StringArray::operator=(const Value& other){
//     Type ty = other.getType();
//     if(ty == STRING_ARRAY){
//         if(this == &other) return *this;
//         data.StringArray->clear();
//         for(const string& s : *other.data.StringArray){
//             data.StringArray->emplace_back(s);
//         }
//     } else if (ty == LIST){
//         data.StringArray->clear();
//         for(Value *elem : *other.data.List){
//             if(elem->getType() == STRING){
//                 data.StringArray->emplace_back(*elem->data.String);
//             }
//         }
//     } else{
//         assert(false);
//     }
// }

// Value::Type StringArray::getType() const{
//     return STRING_ARRAY;
// }

// int_64 StringArray::hashCode() const{
//     assert(false);
//     return 0;

// }

// bool StringArray::operator==(const Value& other) const{
//     assert(false);
//     return false;
// }
// bool StringArray::operator<(const Value& other) const{
//     assert(false);
//     return false;
// }
// std::string StringArray::toString() const{
//     stringstream buf;
//     buf << "StringArray(length: " << data.StringArray->size() <<")";
//     return buf.str();
// }
// void StringArray::append(const std::string &str){
//     data.StringArray->emplace_back(str);
// }

// /* Class: BooleanArray */

// BooleanArray::BooleanArray(){
//     data.BooleanArray = new vector<bool>();
// }

// BooleanArray::BooleanArray(const std::vector<bool> &bool_vec){
//     data.BooleanArray = new vector<bool>();
//     for(bool b : bool_vec){
//         data.BooleanArray->emplace_back(b);
//     }
// }

// /**
//  * @param other: BooleanArray, or List of boolean
// */
// BooleanArray::BooleanArray(const Value &other){
//     data.BooleanArray = new vector<bool>();
//     Type ty = other.getType();
//     if(ty == BOOLEAN_ARRAY){
//         for(bool b : *other.data.BooleanArray){
//             data.BooleanArray->push_back(b);
//         }
//     } else if(ty == LIST){
//         for(Value *elem : *other.data.List){
//             if(elem->getType() == BOOLEAN){
//                 data.BooleanArray->push_back(elem->data.Boolean);
//             }else{
//                 delete data.BooleanArray;
//                 assert(false);
//             }
//         }
//     }
// }

// BooleanArray::~BooleanArray(){
//     if(data.BooleanArray != nullptr)
//         delete data.BooleanArray;
// }

// /**
//  * @param other: BooleanArray, or List of boolean
// */
// Value& BooleanArray::operator=(const Value& other){
//     Type ty = other.getType();
//     if(ty == BOOLEAN_ARRAY){
//         if(this == &other) return *this;
//         data.BooleanArray->clear();
//         for(bool b : *other.data.BooleanArray){
//             data.BooleanArray->push_back(b);
//         }
//     } else if(ty == LIST){
//         data.BooleanArray->clear();
//         for(Value *elem : *other.data.List){
//             if(elem->getType() == BOOLEAN){
//                 data.BooleanArray->push_back(elem->data.Boolean);
//             }else{
//                 assert(false);
//             }
//         }
//     }
// }

// Value::Type BooleanArray::getType() const{
//     return BOOLEAN_ARRAY;
// }

// /* Array Type only used for storage */
// int_64 BooleanArray::hashCode() const{
//     assert(false);
//     return 0;
// }

// /* Array Type only used for storage */
// bool BooleanArray::operator==(const Value& other) const{
//     assert(false);
//     return true;
// }

// /* Array Type only used for storage */
// bool BooleanArray::operator<(const Value& other) const{
//     assert(false);
//     return true;
// }

// std::string BooleanArray::toString() const{
//     stringstream buf;
//     buf << "BooleanArray(length: " << data.BooleanArray->size() <<")";
//     return buf.str();
// }

// void BooleanArray::append(bool b){
//     data.BooleanArray->push_back(b);
// }

// /* Class: Node */

// Node::Node(){

// }

// Node::Node(uint_64 nodeId){
//     data.Node = nodeId;
// }

// Node::Node(const Value& other){
//     assert(other.getType() == NODE);
//     data.Node = other.data.Node;
// } 

// Node::~Node(){

// }

// Value& Node::operator=(const Value& other){
//     assert(other.getType() == NODE);
//     data.Node = other.data.Node;
//     return *this;
// }

// Value::Type Node::getType() const{
//     return NODE;
// }

// int_64 Node::hashCode() const{
//     return data.Node & (0x7FFFFFFFFFFFFFFF);
// }

// bool Node::operator==(const Value& other) const{
//     return other.getType() == NODE && other.data.Node == data.Node;
// }

// bool Node::operator<(const Value& other) const{
//     Type ty = other.getType();
//     if(ty == MAP){
//         return false;
//     } else if(ty == NODE){
//         return data.Node < other.data.Node;
//     } else {
//         return true;
//     }
// }

// std::string Node::toString() const{
//     stringstream buf;
//     buf << "Node" <<"(" << data.Node <<")";
//     return buf.str();
// }

// /* Class: Edge */

// Edge::Edge(){

// }

// Edge::Edge(uint_64 edgeId){
//     data.Edge = edgeId;
// }

// Edge::Edge(const Value& other){
//     assert(other.getType() == EDGE);
//     data.Edge = other.data.Edge;
// }

// Edge::~Edge(){

// }

// Value& Edge::operator=(const Value& other){
//     assert(other.getType() == EDGE);
//     data.Edge = other.data.Edge;
// }

// Value::Type Edge::getType() const{
//     return EDGE;
// }

// int_64 Edge::hashCode() const{
//     return data.Edge & (0x7FFFFFFFFFFFFFFF);
// }

// bool Edge::operator==(const Value& other) const{
//     return other.getType() == EDGE && data.Edge == other.data.Edge;
// }

// bool Edge::operator<(const Value& other) const{
//     Type ty = other.getType();
//     if(ty == MAP || ty == NODE){
//         return false;
//     } else if(ty == EDGE){
//         return data.Edge < other.data.Edge;
//     } else {
//         return true;
//     }
// }

// std::string Edge::toString() const{
//     stringstream buf;
//     buf << "Edge" <<"(" << data.Edge <<")";
//     return buf.str();
// }

// /* Class: Path */

// Path::Path(){
//     data.Path = new PathContent();
// }

// Path::Path(const Value &other){
//     assert(other.getType() == PATH);
//     data.Path = new PathContent();
//     for(auto uint_ : other.data.Path->edgeId){
//         data.Path->edgeId.push_back(uint_);
//     }
//     for(auto uint_ : other.data.Path->nodeId){
//         data.Path->nodeId.push_back(uint_);
//     }
//     for(auto ty : other.data.Path->edgeType){
//         data.Path->edgeType.push_back(ty);
//     }
// }

// Path::Path(const std::vector<uint_64> &_edge_id, const std::vector<uint_64> &_node_id, const std::vector<EdgeType> &_edge_type){
//     cout << "In Path";
//     assert(_edge_id.size() + 1 == _node_id.size());
//     data.Path = new PathContent();
//     uint_64 n = _edge_id.size();
//     for(int i = 0; i < n; ++i){
//         data.Path->nodeId.push_back(_node_id[i]);
//         data.Path->edgeId.push_back(_edge_id[i]);
//         data.Path->edgeType.push_back(_edge_type[i]);
//     }
//     data.Path->nodeId.push_back(_node_id[n]);
//     cout << "OUT P";
// }

// Path::~Path(){
//     if(data.Path != nullptr)
//         delete data.Path;
// }

// Value& Path::operator=(const Value& other){
//     cout << "IN OP =";
//     if(&other == this) return *this;
//     assert(other.getType() == PATH);
//     data.Path->edgeId.clear();
//     data.Path->nodeId.clear();
//     data.Path->edgeType.clear();

//     for(auto uint_ : other.data.Path->edgeId){
//         data.Path->edgeId.push_back(uint_);
//     }
//     for(auto uint_ : other.data.Path->nodeId){
//         data.Path->nodeId.push_back(uint_);
//     }
//     for(auto ty : other.data.Path->edgeType){
//         data.Path->edgeType.push_back(ty);
//     }
//     cout << "OUT OP =";
//     return *this;
// }

// Value::Type Path::getType() const{
//     return PATH;
// }

// int_64 Path::hashCode() const{
//     int_64 seed = 131; // 31 131 1313 13131 131313 etc..
//     int_64 hash = 0;
//     uint_64 l = data.Path->edgeId.size();
//     // l = l > 100 ? 100 : l;
//     for(uint_64 i = 0; i < l; ++i){
//         hash = hash * seed + (data.Path->nodeId[i]);
//         hash = hash * seed + (data.Path->edgeId[i]);
//     }
//     hash = hash * seed + (data.Path->nodeId[l]);
//     return (hash & 0x7FFFFFFFFFFFFFFF);
// }   

// bool Path::operator==(const Value& other) const{
//     assert(other.getType() == PATH);
//     if(other.data.Path->edgeId.size() != data.Path->edgeId.size()) return false;
//     uint_64 n = data.Path->edgeId.size();
//     bool flag = true;

//     for(int i = 0; i < n; ++i){
//         if(other.data.Path->edgeId[i] != data.Path->edgeId[i] || 
//            other.data.Path->edgeType[i] != data.Path->edgeType[i] ||
//            other.data.Path->nodeId[i] != data.Path->nodeId[i]){
//             flag = false;
//             break;
//         }
//     }
//     if(other.data.Path->nodeId[n] != data.Path->nodeId[n])
//         flag = false;
//     if(flag)
//         return true;
    
//     for(int i = 0; i < n; ++i){
//         if(other.data.Path->edgeId[i] != data.Path->edgeId[n - i - 1] || 
//            other.data.Path->edgeType[i] != data.Path->edgeType[n - i - 1] ||
//            other.data.Path->nodeId[i] != data.Path->nodeId[n - i]){
//             flag = false;
//             break;
//         }
//     }
//     if(other.data.Path->nodeId[n] != data.Path->nodeId[0])
//         flag = false;
//     return flag;
// }

// bool Path::operator<(const Value& other) const{
//     int m = data.Path->edgeId.size(), n = other.data.Path->edgeId.size();
//     int l = m < n ? m : n;
//     for(int i = 0; i < l; ++i){
//         if(data.Path->nodeId[i] != other.data.Path->nodeId[i]) 
//         return data.Path->nodeId[i] < other.data.Path->nodeId[i];
//         if(data.Path->edgeId[i] != other.data.Path->edgeId[i]) continue;
//         return data.Path->edgeId[i] < other.data.Path->edgeId[i];
//     }
//     if(data.Path->nodeId[l] != other.data.Path->nodeId[l])
//         return data.Path->nodeId[l] < other.data.Path->nodeId[l];
//     return m < n;
// }

// std::string Path::toString() const{
//     stringstream buf;
//     return buf.str();
// }

// /* Class: List */

// List::List(){
//     data.List = new vector<Value *>();
// }

// /**
//  * Construct a List from other List or Array.
//  * @param other: List or [Boolean|Int|Float|String] Array 
//  * 
// */
// List::List(const Value &other){
//     data.List = new vector<Value *>();
//     Type ty = other.getType();
//     if(ty == LIST){
//         for(Value *elem : *other.data.List){
//             Type elem_ty = elem->getType();
//             Value *new_elem = ValueDeepCopy(elem);
//             data.List->push_back(new_elem);
//         }
//     } else if(ty == INTEGER_ARRAY){
//         for(auto int_ : *other.data.IntArray){
//             data.List->push_back(new IntValue(int_));
//         }
//     } else if(ty == FLOAT_ARRAY){
//         for(auto d : *other.data.FloatArray){
//             data.List->push_back(new FloatValue(d));
//         }
//     } else if(ty == STRING_ARRAY){
//         for(const string& s : *other.data.StringArray){
//             data.List->push_back(new StringValue(s));
//         }
//     }else if(ty == BOOLEAN_ARRAY){
//         for(bool b : *other.data.BooleanArray){
//             data.List->push_back(new BooleanValue(b));
//         }
//     }
// }

// List::~List(){
//     if(data.List != nullptr){
//         for(Value *v : *data.List){
//             if(v != nullptr)
//                 delete v;
//         }
//         delete data.List;
//     }
// }

// /**
//  * Construct a List from other List or Array.
//  * @param other: List or [Boolean|Int|Float|String] Array 
//  * 
// */
// Value& List::operator=(const Value& other){
//     if(this == &other) return *this;
//     for(Value *v : *data.List){
//         if(v != nullptr)
//             delete v;
//     }
//     data.List->clear();
//     Type ty = other.getType();
//     if(ty == LIST){
//         for(Value *elem : *other.data.List){
//             Type elem_ty = elem->getType();
//             Value *new_elem = ValueDeepCopy(elem);
//             data.List->push_back(new_elem);
//         }
//     } else if(ty == INTEGER_ARRAY){
//         for(auto int_ : *other.data.IntArray){
//             data.List->push_back(new IntValue(int_));
//         }
//     } else if(ty == FLOAT_ARRAY){
//         for(auto d : *other.data.FloatArray){
//             data.List->push_back(new FloatValue(d));
//         }
//     } else if(ty == STRING_ARRAY){
//         for(const string& s : *other.data.StringArray){
//             data.List->push_back(new StringValue(s));
//         }
//     }else if(ty == BOOLEAN_ARRAY){
//         for(bool b : *other.data.BooleanArray){
//             data.List->push_back(new BooleanValue(b));
//         }
//     }
//     return *this;
// }

// Value::Type List::getType() const{
//     return LIST;
// }

// int_64 List::hashCode() const{
//     int_64 seed = 131; // 31 131 1313 13131 131313 etc..
//     int_64 hash = 0;
//     uint_64 l = data.List->size();
//     // l = l > 100 ? 100 : l;
//     for(uint_64 i = 0; i < l; ++i){
//         hash = hash * seed + data.List->at(i)->hashCode();
//     }
//     return (hash & 0x7FFFFFFFFFFFFFFF);
// }

// bool List::operator==(const Value& other) const{
//     uint_64 n = data.List->size();
//     if(other.data.List->size() != n){
//         return false;
//     }
//     for(uint_64 i = 0; i < n; ++i){
//         if( !( *other.data.List->at(i) == *data.List->at(i) ) ){
//             return false;
//         }
//     }
//     return true;
// }

// bool List::operator<(const Value& other) const{
//     Type ty = other.getType();
//     if(ty == MAP || ty == NODE || ty == EDGE){
//         return false;
//     } else if(ty != LIST){
//         return true;
//     }
//     // ty is LIST
//     uint_64 m = data.List->size(), n = other.data.List->size();
//     uint_64 l = m > n ? n : m;
//     for(uint_64 i = 0; i < l; ++i){
//         if(*data.List->at(i) == *other.data.List->at(i)){
//             continue;
//         }
//         return *data.List->at(i) < *other.data.List->at(i);
//     }
//     return m < n;
// }

// std::string List::toString() const{
//     stringstream buf;
//     buf << "[ ";
//     for(Value *v : *data.List){
//         buf << v->toString() << ", ";
//     }
//     buf << "]";
//     return buf.str();
// }

// void List::append(const Value&other) {
//     data.List->push_back(ValueDeepCopy(&other));
// }

// bool List::canConvertIntArray(){
//     for(Value *v : *data.List){
//         if(v->getType() != INTEGER)
//             return false;
//     }
//     return true;
// }

// bool List::canConvertFloatArray(){
//     for(Value *v : *data.List){
//         if(v->getType() != INTEGER && v->getType() != FLOAT)
//             return false;
//     }
//     return true;
// }

// bool List::canConvertStringArray(){
//     for(Value *v : *data.List){
//         if(v->getType() != STRING)
//             return false;
//     }
//     return true;
// }

// bool List::canConvertBooleanArray(){
//     for(Value *v : *data.List){
//         if(v->getType() != BOOLEAN)
//             return false;
//     }
//     return true;
// }

// /* Class: Map */

// Map::Map(){
//     data.Map = new map<string, Value *>();
// }

// Map::Map(const Value &other){
//     assert(other.getType() == MAP);
//     data.Map = new map<string, Value *>();
//     for(const auto &p : *other.data.Map){
//         data.Map->insert(make_pair(p.first,ValueDeepCopy(p.second)));
//     }
// }

// Map::~Map(){
//     if(data.Map != nullptr){
//         for(const auto &p : *data.Map){
//             if(p.second != nullptr)
//                 delete p.second;
//         }
//     }
//     delete data.Map;
// }

// Value& Map::operator=(const Value& other){
//     assert(other.getType( ) == MAP);
//     if(this == &other) return *this;
//     if(data.Map != nullptr){
//         for(const auto &p : *data.Map){
//             if(p.second != nullptr)
//                 delete p.second;
//         }
//     }
//     data.Map->clear();
//     for(const auto &p : *other.data.Map){
//         data.Map->insert(make_pair(p.first,ValueDeepCopy(p.second)));
//     }
//     return *this;
// }

// Value::Type Map::getType() const{
//     return MAP;
// }

// int_64 Map::hashCode() const{
//     int_64 seed = 131; // 31 131 1313 13131 131313 etc..
//     int_64 hash = 0;
//     for(const auto &p : *data.Map){
//         StringValue s(p.first);
//         hash = hash * seed + s.hashCode();
//         hash = hash * seed + p.second->hashCode();
//     }
//     return (hash & 0x7FFFFFFFFFFFFFFF);
// }

// bool Map::operator==(const Value& other) const{
//     uint_64 m = data.Map->size(), n = other.data.Map->size();
//     if(m != n) {
//         return false;
//     }
//     for(const auto &p : *data.Map){
//         const string & k = p.first;
//         Value *v = p.second;
//         if(other.data.Map->find(k) == other.data.Map->end() ||
//             !(*other.data.Map->at(k) == *v) ){
//                 return false;
//         }
//     }
//     return true;
// }

// /* Not defined yet */
// bool Map::operator<(const Value& other) const{
//     return false;
// }

// std::string Map::toString() const{
//     stringstream buf;
//     buf << "{ ";
//     for(const auto &p : *data.Map){
//         buf << p.first << ": ";
//         buf << p.second->toString() << ", ";
//     }
//     buf << "}";
//     return buf.str();
// }

// void Map::insert(const std::string &k, const Value &v){
//     map<string, Value*>::iterator it = data.Map->find(k);
//     if(it == data.Map->end()){
//         data.Map->insert(make_pair(k, ValueDeepCopy(&v)));
//     }else{
//         it->second = ValueDeepCopy(&v);
//     }
//     return;
// }


// /* Class: NoValue */

// NoValue::NoValue(){

// }

// NoValue::~NoValue(){

// }

// Value& NoValue::operator=(const Value& other){
//     assert(other.getType() == NO_VALUE);
//     return *this;
// }

// Value::Type NoValue::getType() const{
//     return NO_VALUE;
// }
// int_64 NoValue::hashCode() const{
//     return 2; // TODO
// }

// bool NoValue::operator==(const Value& other) const{
//     return other.getType() == NO_VALUE;
// }

// bool NoValue::operator<(const Value& other) const{
//     return false;    
// }

// std::string NoValue::toString() const{
//     return "null";
// }

