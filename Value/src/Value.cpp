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