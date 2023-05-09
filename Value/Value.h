#ifndef VALUE_VALUE_H
#define VALUE_VALUE_H
/**
 * 所有的值都组织为Value。 一切赋值，构造都是深拷贝。
 * 警告：
 * (1)重载的'<'运算符，适用于order by的排序，和表达式中比较大小的'<'不是同一概念
 * (2)重载的'=='运算符，适用于Distinct，Groupby，而不适用与表达式的相等‘=’
 * (3) '<'号中，不支持Map之间的比较（Cypher规范未定义），但'=='支持Map之间的相等判断
 * (4) order by排序，用<即可
 * (5) Distinct，可以先排序再去重，但注意Map之间的去重，只能用暴力的(n^2)的方法，因为Map上没定义'<'关系。
 * (6) hashCode函数暂时保留接口，不用！因为有些古怪。(Map, null, 以及浮点与整形相等...)
*/

#include <string>
#include <map>
#include <vector>

namespace GPStore{
typedef long long int_64;
typedef unsigned long long uint_64;
typedef unsigned char byte;

class Value {
public:
    enum Type {
        INTEGER, FLOAT, STRING, BOOLEAN,  // above && their array are storable
        NODE, EDGE, PATH,
        LIST, MAP,
        NO_VALUE,   // Cypher null
        ERROR_VALUE // ERROR
    };


    struct PathContent{
        std::vector<unsigned > node_id_;
        std::vector<uint_64> edge_id_;
    };

    union ValueUnion{
        int_64 Int;
        double Float;
        std::string *String;
        bool Boolean;

        uint_64 Node;
        uint_64 Edge;
        PathContent *Path;
        std::vector<Value *> *List;
        std::map<std::string, Value *> *Map;
    };

    Type type_;
    ValueUnion data_;

    Value();
    Value(Type _type_);
    Value(const Value &other);
    
    Value(int_64 int_);
    Value(double float_);
    Value(const std::string& str);
    Value(const char* s);
    Value(bool b);
    /* Construct Node or Edge */
    Value(Type _type, uint_64 _id);
    /* Construct Path */
    Value(const PathContent &path_);
    Value(const std::vector<unsigned >& node_id, const std::vector<uint_64> &edge_id);

    /* Construct List */
    Value(const std::vector<Value *> &list_, bool deep_copy = true);

    /* Construct Map */
    Value(const std::vector<std::string> &keys, const std::vector<Value *> &values, bool deep_copy = true);

    ~Value();

    bool isNull() const;
    bool storable() const;

    bool isIntArray() const;
    bool isFloatArray() const;
    bool isStringArray() const;
    bool isBooleanArray() const;

    uint_64 convertToBytes(void * ptr);

    void constructFromBytes(const void * ptr, uint_64 n);

    Type getType() const;
    int_64 hashCode() const ;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY

    Value& operator=(const Value&other);

    /* get a read-only pointer the the content of a list value */
    const std::vector<GPStore::Value*>* getListContent();

    /* append an element to a list */
    void append(const Value& value);

    /* get a list element by index(must be valid) */
    Value &operator[](uint_64 index);
    
    /* insert a (key, value) pair to a map */
    void insert(const std::string &key, const Value &value);

    /* find value by key, return nullptr if key doesnot exist */
    Value *search(const std::string &key);

    uint_64 size();
    
    std::string toString() const ;

    static Value * ValueDeepCopy(const Value *value);

private:
    /* Construct Functions */
    void ConstructFrom(const Value& other);

    /* for order by */
    bool CompareIntWith(const Value &other) const;
    bool CompareFloatWith(const Value &other) const;
    bool CompareStringWith(const Value &other) const;
    bool CompareBooleanWith(const Value &other) const;
    bool CompareNodeWith(const Value &other) const;
    bool CompareEdgeWith(const Value &other) const;
    bool ComparePathWith(const Value &other) const;
    bool CompareListWith(const Value &other) const;
    bool CompareMapWith(const Value &other) const;
    bool CompareNoValueWith(const Value &other) const;

    /* for distinct, group by */
    bool IntEqualTo(const Value &other) const;
    bool FloatEqualTo(const Value &other) const;
    bool StringEqualTo(const Value &other) const;
    bool BooleanEqualTo(const Value &other) const;
    bool NodeEqualTo(const Value &other) const;
    bool EdgeEqualTo(const Value &other) const;
    bool PathEqualTo(const Value &other) const;
    bool ListEqualTo(const Value &other) const;
    bool MapEqualTo(const Value &other) const;
    bool NoValueEqualTo(const Value &other) const;

    /* destruct functions */
    void Destruct();
};


/* helper functions */
}
#endif