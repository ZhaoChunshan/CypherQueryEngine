/**
 * 所有的值都组织为Value。
 * 一切赋值，构造都是深拷贝。
*/

#include <string>
#include <map>
#include <vector>
typedef long long int_64;
typedef unsigned long long uint_64;
typedef unsigned char byte;


class Value {
public:
    enum Type {
        INTEGER, FLOAT, STRING, BOOLEAN, 
        INTEGER_ARRAY, FLOAT_ARRAY, STRING_ARRAY, BOOLEAN_ARRAY, 
        BYTE_ARRAY,
        NODE, EDGE, PATH,
        LIST, MAP,
        NO_VALUE   // Cypher null
    };
    
    enum EdgeType{
        LEFT_EDGE, RIGHT_EDGE, UNDIRECTED
    };

    struct PathContent{
        std::vector<EdgeType> edgeType;
        std::vector<uint_64> edgeId;
        std::vector<uint_64> nodeId;
    };

    union ValueUnion{
        int_64 Int;
        double Float;
        std::string *String;
        bool Boolean;
        std::vector<int_64> *IntArray;
        std::vector<double> *FloatArray;
        std::vector<std::string> *StringArray;
        std::vector<bool> *BooleanArray;
        uint_64 Node;
        uint_64 Edge;
        PathContent *Path;
        std::vector<Value *> *List;
        std::map<std::string, Value *> *Map;
    };

    Type type_;
    ValueUnion data_;
    Value(){}
    virtual ~Value() {}

    bool isNull() const;
    bool storable() const;

    virtual Type getType() const = 0;
    virtual int_64 hashCode() const = 0;
    virtual bool operator==(const Value& other) const = 0;    // check equivalence for DISTINCT
    virtual bool operator<(const Value& other) const = 0;     // used for ORDER BY

    virtual std::string toString() const = 0;
};

class IntValue : public Value{
public:
    IntValue();
    IntValue(int_64 v);
    IntValue(const Value& other);
    ~IntValue();

    Value& operator=(Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value & other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY 
    std::string toString() const;
};

class FloatValue : public Value {
public:
    FloatValue();
    FloatValue(double v);
    FloatValue(const Value &other);
    ~FloatValue();

    Value& operator=(Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY 

    std::string toString() const;
};

class StringValue : public Value {
public:
    StringValue();
    StringValue(const std::string &s);
    StringValue(const Value& other);
    ~StringValue();

    Value& operator=(Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY 

    std::string toString() const;
};

class BooleanValue : public Value {
public:
    BooleanValue();
    BooleanValue(bool v);
    BooleanValue(const Value& other);
    ~BooleanValue();

    Value& operator=(Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY

    std::string toString() const;
};

// Array Type Only used for Storage.
class IntArray : public Value {
public:
    IntArray();
    IntArray(const Value &v);
    IntArray(const std::vector<int_64> &int_vec);
    ~IntArray();

    Value& operator=(Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;

    void append(int_64 integer);
};

// Array Type Only used for Storage.
class FloatArray : public Value {
public:
    FloatArray();
    FloatArray(const Value &v);
    FloatArray(const std::vector<double> &double_vec);
    ~FloatArray();

    Value& operator=(Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;

    void append(double _float);

};

// Array Type Only used for Storage.
class StringArray : public Value {
public:
    StringArray();
    StringArray(const Value &v);
    StringArray(const std::vector<std::string> &string_vec);
    ~StringArray();

    Value& operator=(Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;

    void append(const std::string &str);
};

// Array Type Only used for Storage.
class BooleanArray : public Value {
public:
    BooleanArray();
    BooleanArray(const std::vector<bool> &bool_vec);
    BooleanArray(const Value &other);
    ~BooleanArray();

    Value& operator=(Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;

    void append(bool b);
};


class Node : public Value {
public:
    Node();
    Node(uint_64 nodeId);
    Node(const Value& other);
    ~Node();

    Value& operator=(Value const&  other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;

};

class Edge : public Value {
public:
    Edge();
    Edge(uint_64 edgeId);
    Edge(const Value& other);
    ~Edge();

    Value& operator=( Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;
};

class Path : public Value {
public:
    Path();
    Path(const Value &other);
    Path(const std::vector<uint_64> &_edge_id, const std::vector<uint_64> &_node_id, const std::vector<EdgeType> &_edge_type);
    ~Path();

    Value& operator=( Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;
};

class List : public Value {
public:
    List();
    List(const Value &other);
    ~List();

    Value& operator=( Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;

    void append(const Value&other);

    bool canConvertIntArray();
    bool canConvertFloatArray();
    bool canConvertStringArray();
    bool canConvertBooleanArray();
    
};

class Map : public Value {
public:
    Map();
    Map(const Value &other);
    ~Map();

    Value& operator=( Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;

    void insert(const std::string &k, const Value &v);
};

class NoValue : public Value {
public:
    NoValue();
    ~NoValue();
    
    Value& operator=( Value const& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
    std::string toString() const;
};

/* helper functions */

Value * ValueDeepCopy(const Value *value);
