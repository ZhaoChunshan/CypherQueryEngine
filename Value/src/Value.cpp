#include "Value.h"
#include <cassert>
#include <math.h>
using namespace std;

/* Class: Value */

bool Value::isNull() const{
    return this->getType() == NO_VALUE;
}

bool Value::storable() const{
    Type ty = this->getType();
    return ty == INTEGER || ty == FLOAT || ty == STRING || ty == BOOLEAN || ty == INTEGER_ARRAY 
    || ty == FLOAT_ARRAY || ty ==  STRING_ARRAY || ty ==  BOOLEAN_ARRAY|| ty == BYTE_ARRAY;
}
/* Class: IntValue */

IntValue::IntValue() {

}

IntValue::IntValue(int_64 v) {
    data.Int = v;
}

IntValue::IntValue(const Value& other) {
    assert(other.getType() == INTEGER);
    data.Int = other.data.Int;
}


IntValue::~IntValue() {

}

Value& IntValue::operator=(const Value& other){
    assert(other.getType() == INTEGER);
    data.Int = other.data.Int;
    return *this;
}

Value::Type IntValue::getType() const{
    return Value::INTEGER;
}

int_64 IntValue::hashCode() const {
    return data.Int & 0x7FFFFFFFFFFFFFFF;
}

bool IntValue::operator==(const Value& other) const {
    return other.getType() == INTEGER && data.Int == other.data.Int;
}

bool IntValue::operator<(const Value& other) const {
    Type ty = other.getType();
    if(ty == INTEGER ){
        return data.Int < other.data.Int;
    } else if( ty == FLOAT) {
        if(isinf(other.data.Float) == 1 || isnan(other.data.Float))
            return true;
        if(isinf(other.data.Float) == -1)
            return false;
        return data.Int < other.data.Float;
    } else if(ty == NO_VALUE){
        return true;
    } else {
        return false;
    }
}

/* Class: FloatValue */

FloatValue::FloatValue(){

}

FloatValue::FloatValue(double v) {
    data.Float = v;
}

/**
 * @param other: Integer Value or Float Value
*/
FloatValue::FloatValue(const Value &other) {
    Type ty = other.getType();
    assert(ty == INTEGER || ty == FLOAT);
    if(ty == INTEGER){
        data.Float = (double)other.data.Int;
    } else {
        data.Float = other.data.Float;
    }
}

FloatValue::~FloatValue(){

}

Value& FloatValue::operator=(const Value& other){
    Type ty = other.getType();
    assert(ty == INTEGER || ty == FLOAT);
    if(ty == INTEGER){
        data.Float = (double)other.data.Int;
    } else {
        data.Float = other.data.Float;
    }
    return *this;
}

Value::Type FloatValue::getType() const{
    return Value::FLOAT;
}

int_64 FloatValue::hashCode() const{
    return (*(int_64 *) (&data.Float) & 0x7FFFFFFFFFFFFFFF);
}

bool FloatValue::operator==(const Value& other) const{
    return other.getType() == FLOAT && data.Float == other.data.Float;
}

bool FloatValue::operator<(const Value& other) const{
    Type ty = other.getType();
    if(ty == INTEGER ){
        if(isinf(data.Float) == 1 || isnan(data.Float))
            return false;
        if(isinf(data.Float) == -1)
            return true;
        return data.Float < other.data.Int;
    } else if( ty == FLOAT) {
        if(isnan(other.data.Float)){
            return !isnan(data.Float);
        }
        if(isinf(other.data.Float) == 1)
            return !(isinf(data.Float) == 1 || isnan(data.Float));
        if(isinf(other.data.Float) == -1)
            return false;
        if(isnan(data.Float) || isinf(data.Float) == 1) return false;
        if(isinf(data.Float) == -1)return true;
        return data.Float < other.data.Float;
    } else if(ty == NO_VALUE){
        return true;
    } else {
        return false;
    }
}

/* Class: StringValue */

StringValue::StringValue(){
    data.String = new string();
}

StringValue::StringValue(const std::string &s){
    data.String = new string(s);
}

StringValue::StringValue(const Value& other){
    assert(other.getType() == STRING);
    data.String = new string(*other.data.String);
}

StringValue::~StringValue(){
    if(data.String != nullptr)
        delete data.String;
}

Value& StringValue::operator=(const Value& other){
    assert(other.getType() == STRING);
    *data.String = *other.data.String;
    return *this;
}

Value::Type StringValue::getType() const{
    return Value::STRING;
}

int_64 StringValue::hashCode() const{
    // BKDR Hash Function

    int_64 seed = 131; // 31 131 1313 13131 131313 etc..
    int_64 hash = 0;
    uint_64 l = data.String->length();
    // l = l > 100 ? 100 : l;
    for(uint_64 i = 0; i < l; ++i){
        hash = hash * seed + (data.String->at(i));
    }
    return (hash & 0x7FFFFFFFFFFFFFFF);
}

bool StringValue::operator==(const Value& other) const{
    return other.getType() == STRING && *data.String == *other.data.String;
}

bool StringValue::operator<(const Value& other) const{
    Type ty = other.getType();
    if(ty == STRING){
        return *data.String < *other.data.String;
    } else if (ty == FLOAT || ty == INTEGER || ty == NO_VALUE || ty == BOOLEAN){
        return true;
    } else {
        return false;
    }
}

/* Class: BooleanValue */

BooleanValue::BooleanValue(){

}

BooleanValue::BooleanValue(bool v){
    data.Boolean = v;
}

BooleanValue::BooleanValue(const Value& other){
    assert(other.getType() == BOOLEAN);
    data.Boolean = other.data.Boolean;
}

BooleanValue::~BooleanValue(){

}

Value& BooleanValue::operator=(const Value& other){
    assert(other.getType() == BOOLEAN);
    data.Boolean = other.data.Boolean;
    return *this;
}

Value::Type BooleanValue::getType() const{
    return BOOLEAN;
}

int_64 BooleanValue::hashCode() const{
    return data.Boolean ? 1 : 0;
}

bool BooleanValue::operator==(const Value& other) const{
    return other.getType() == BOOLEAN && data.Boolean == other.BOOLEAN;
}   

bool BooleanValue::operator<(const Value& other) const{
    Type ty = other.getType();
    if(ty == INTEGER || ty == FLOAT || ty == NO_VALUE) {
        return true;
    } else if(ty != BOOLEAN){
        return false;
    } else {
        return data.Boolean ? false : other.data.Boolean;
    }
}

/* Class: IntArray */

IntArray::IntArray(){
    data.IntArray = new vector<int_64>();
}

/**
 * @param v: another IntArray, or List of integer Value
*/
IntArray::IntArray(const Value &v){
    Type ty = v.getType();
    assert(ty == INTEGER_ARRAY || ty == LIST);
    data.IntArray = new vector<int_64>();
    if(ty == INTEGER_ARRAY){
        for(auto i : *v.data.IntArray){
            data.IntArray->push_back(i);
        }
    } else if(ty == LIST){
        uint_64 n = v.data.List->size();
        for(uint_64 i = 0; i < n; ++i){
            Value *elem = v.data.List->at(i);
            if(elem->getType() != INTEGER){
                delete data.IntArray;
                assert(false);
            } else {
                data.IntArray->push_back(elem->data.Int);
            }
        }
    }
}

IntArray::IntArray(const std::vector<int_64> &int_vec){
    data.IntArray = new vector<int_64>();
    for(auto in : int_vec){
        data.IntArray->push_back(in);
    }
}

IntArray::~IntArray(){
    if(data.IntArray != nullptr)
        delete data.IntArray;
}

/**
 * @param other: IntArray, or List of integer Value
*/
Value& IntArray::operator=(const Value& other){
    if(other.getType() == INTEGER_ARRAY){
        if(this == &other) return *this;
        data.IntArray->clear();
        for(int_64 i : *other.data.IntArray){
            data.IntArray->push_back(i);
        }
    } else if(other.getType() == LIST) {
        data.IntArray->clear();
        uint_64 n = other.data.List->size();
        for(uint_64 i = 0; i < n; ++i){
            Value *elem = other.data.List->at(i);
            if(elem->getType() != INTEGER){
                assert(false);
            } else {
                data.IntArray->push_back(elem->data.Int);
            }
        }
    } else {
        assert(false);
    }
    return *this;
}

Value::Type IntArray::getType() const{
    return INTEGER_ARRAY;
}

/* Array Type only used for storage */
int_64 IntArray::hashCode() const{
    assert(false);
    return 0;
}

/* Array Type only used for storage */
bool IntArray::operator==(const Value& other) const{
    assert(false);
    return true;
}

/* Array Type only used for storage */
bool IntArray::operator<(const Value& other) const{
    assert(false);
    return true;
}

void IntArray::append(int_64 integer){
    data.IntArray->push_back(integer);
}

/* Class: FloatArray */

FloatArray::FloatArray(){

}

/**
 * @param v: FLoatArray, or List containing Integer&Float
*/
FloatArray::FloatArray(const Value &v){
    Type ty = v.getType();
    assert(ty == FLOAT_ARRAY || ty == LIST);
    data.FloatArray = new vector<double>();
    if(ty == FLOAT_ARRAY){
        for(auto i : *v.data.FloatArray){
            data.FloatArray->push_back(i);
        }
    } else if(ty == LIST){
        uint_64 n = v.data.List->size();
        for(uint_64 i = 0; i < n; ++i){
            Value *elem = v.data.List->at(i);
            if(elem->getType() == FLOAT){
                data.FloatArray->push_back(elem->data.Float);
            } else if(elem->getType() == INTEGER){
                data.FloatArray->push_back((double)elem->data.Int);
            }
            else {
                delete data.FloatArray;
                assert(false);
            }
        }
    }
}

FloatArray::FloatArray(const std::vector<double> &double_vec){
    data.FloatArray = new vector<double>();
    for(auto d : double_vec){
        data.FloatArray->push_back(d);
    }
}

FloatArray::~FloatArray(){
    if(data.FloatArray != nullptr)
        delete data.FloatArray;
}

/**
 * @param other: FLoatArray, or List containing Integer&Float
*/
Value& FloatArray::operator=(const Value& other){
    Type ty = other.getType();
    if(ty == FLOAT_ARRAY){
        if(this == &other) return *this;
        data.FloatArray->clear();
        for(auto d : *other.data.FloatArray){
            data.FloatArray->push_back(d);
        }
    } else if(ty == LIST){
        uint_64 n = other.data.FloatArray->size();
        data.FloatArray->clear();
        for(uint_64 i = 0; i < n; ++i){
            Value *elem = other.data.List->at(i);
            if(elem->getType() == FLOAT){
                data.FloatArray->push_back(elem->data.Float);
            } else if(elem->getType() == INTEGER){
                data.FloatArray->push_back((double)elem->data.Int);
            }
            else{
                assert(false);
            }
        }
    } else {
        assert(false);
    }
}

Value::Type FloatArray::getType() const{
    return FLOAT_ARRAY;
}

/* Array Type only used for storage */
int_64 FloatArray::hashCode() const{
    assert(false);
    return 0;
}

/* Array Type only used for storage */
bool FloatArray::operator==(const Value& other) const{
    assert(false);
    return true;
}

/* Array Type only used for storage */
bool FloatArray::operator<(const Value& other) const{
    assert(false);
    return true;
}

void FloatArray::append(double _float){
    data.FloatArray->push_back(_float);
}

/* Class: StringArray */

StringArray::StringArray(){
    data.StringArray = new vector<string>();
}

/**
 * @param v: StringArray, or List of String
*/
StringArray::StringArray(const Value &v){
    Type ty = v.getType();
    if(ty == STRING_ARRAY){
        data.StringArray = new vector<string>();
        for(const string& s : *v.data.StringArray){
            data.StringArray->emplace_back(s);
        }
    } else if (ty == LIST){
        data.StringArray = new vector<string>();
        for(Value *elem : *v.data.List){
            if(elem->getType() == STRING){
                data.StringArray->emplace_back(*elem->data.String);
            }
        }
    } else{
        delete data.StringArray;
        assert(false);
    }
}

StringArray::StringArray(const std::vector<std::string> &string_vec){
    data.StringArray = new vector<string>();
    for(const string& s : string_vec){
        data.StringArray->emplace_back(s);
    }
}

StringArray::~StringArray(){
    if(data.StringArray != nullptr)
        delete data.StringArray;
}

/**
 * @param other: StringArray, or List of String
*/
Value& StringArray::operator=(const Value& other){
    Type ty = other.getType();
    if(ty == STRING_ARRAY){
        if(this == &other) return *this;
        data.StringArray->clear();
        for(const string& s : *other.data.StringArray){
            data.StringArray->emplace_back(s);
        }
    } else if (ty == LIST){
        data.StringArray->clear();
        for(Value *elem : *other.data.List){
            if(elem->getType() == STRING){
                data.StringArray->emplace_back(*elem->data.String);
            }
        }
    } else{
        assert(false);
    }
}

Value::Type StringArray::getType() const{
    return STRING_ARRAY;
}

int_64 StringArray::hashCode() const{
    assert(false);
    return 0;

}

bool StringArray::operator==(const Value& other) const{
    assert(false);
    return false;
}
bool StringArray::operator<(const Value& other) const{
    assert(false);
    return false;
}
void StringArray::append(const std::string &str){
    data.StringArray->emplace_back(str);
}

/* Class: BooleanArray */
