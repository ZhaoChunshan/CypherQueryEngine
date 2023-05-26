#ifndef VALUE_VALUE_H
#define VALUE_VALUE_H
/**
 * 所有的值都组织为Value。 一切赋值，构造都是深拷贝。
 * 警告：
 * (1)int comp(const Value & other) const兼适合比较大小，判断相等
 * (2)此处的大小只适用于order by的排序，和表达式中比较大小的'<'不是同一概念
 * (3)所谓相等，语义上适用于Distinct，Groupby，而不适用与表达式的相等‘=’
 * (4)hashCode函数暂时保留接口，不用
 * (5)
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
    bool isErrorValue() const;
    bool isNumber() const;
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
    bool operator<(const Value& other) const;     // used for ORDER
    int comp(const Value & other) const;    // return -1 if less than, 1 if greater, 0 if equal
    Value& operator=(const Value&other);

    /* get a read-only pointer the content of a list value */
    const std::vector<GPStore::Value*>* getListContent();

    /* append an element to a list */
    void append(const Value& value);    // deep copy
    void append(Value * value);         // shallow copy
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

    /* for order by return -1 if less than, 1 if greater, 0 if equal */
    int CompareIntWith(const Value &other) const;
    int CompareFloatWith(const Value &other) const;
    int CompareStringWith(const Value &other) const;
    int CompareBooleanWith(const Value &other) const;
    int CompareNodeWith(const Value &other) const;
    int CompareEdgeWith(const Value &other) const;
    int ComparePathWith(const Value &other) const;
    int CompareListWith(const Value &other) const;
    int CompareMapWith(const Value &other) const;
    int CompareNoValueWith(const Value &other) const;

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
public:
    /* destruct functions */
    void Destruct();
};


/* helper functions */
}
#endif