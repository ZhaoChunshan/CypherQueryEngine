//
// Created by zcs on 5/17/23.
//

#ifndef CYPHERQUERYENGINE_UTIL_H
#define CYPHERQUERYENGINE_UTIL_H

// copy from util.h of gpstore 1.2 branch

typedef unsigned long long TYPE_TRIPLE_NUM;
typedef unsigned TYPE_ENTITY_LITERAL_ID;
typedef unsigned TYPE_PROPERTY_ID;
typedef unsigned long long TYPE_EDGE_ID;
static const TYPE_ENTITY_LITERAL_ID INVALID_ENTITY_LITERAL_ID = 0xffffffff;
static const TYPE_PROPERTY_ID INVALID_PROPERTY_ID = 0xffffffff;
static const TYPE_EDGE_ID INVALID_EDGE_ID = 0xffffffffffffffff;
static const unsigned INVALID = 0xffffffffU;
typedef int TYPE_PREDICATE_ID;

typedef int Transaction;
typedef int PStore;
typedef int StringIndex;
typedef int Optimizer;
typedef int AllEntityId;

class KVstore{
public:
    TYPE_ENTITY_LITERAL_ID getIDByString(std::string _str){return 666;}
    TYPE_PROPERTY_ID getpropIDBypropStr(const std::string &_propStr) const{return 2333;}
};

class Util {
public:

    static const char EDGE_IN = 'i';
    static const char EDGE_OUT = 'o';
    static const char EDGE_UNDIRECT = 'u';
};


#endif //CYPHERQUERYENGINE_UTIL_H
