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
typedef int TYPE_PREDICATE_ID;



typedef int Transaction;
typedef int KVstore;
typedef int PStore;
typedef int StringIndex;
typedef int Optimizer;
typedef int AllEntityId;

#endif //CYPHERQUERYENGINE_UTIL_H
