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
        std::vector<uint_64>* Path;
        std::vector<Value *> *List;
        std::map<std::string, Value *> *Map;
    }data;

    virtual Value& operator=(const Value& other);

    bool isNull() const;
    bool storable() const;

    virtual Type getType() const;
    virtual int_64 hashCode() const;
    virtual bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    virtual bool operator<(const Value& other) const;     // used for ORDER BY
};

class IntValue : public Value{
public:
    IntValue();
    IntValue(int_64 v);
    IntValue(const Value& other);
    ~IntValue();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY 
};

class FloatValue : public Value {
public:
    FloatValue();
    FloatValue(double v);
    FloatValue(const Value &other);
    ~FloatValue();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY 
};

class StringValue : public Value {
public:
    StringValue();
    StringValue(const std::string &s);
    StringValue(const Value& other);
    ~StringValue();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY 
};

class BooleanValue : public Value {
public:
    BooleanValue();
    BooleanValue(bool v);
    BooleanValue(const Value& other);
    ~BooleanValue();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY

};

// Array Type Only used for Storage.
class IntArray : public Value {
public:
    IntArray();
    IntArray(const Value &v);
    IntArray(const std::vector<int_64> &int_vec);
    ~IntArray();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY

    void append(int_64 integer);
};

// Array Type Only used for Storage.
class FloatArray : public Value {
public:
    FloatArray();
    FloatArray(const Value &v);
    FloatArray(const std::vector<double> &double_vec);
    ~FloatArray();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY

    void append(double _float);

};

// Array Type Only used for Storage.
class StringArray : public Value {
public:
    StringArray();
    StringArray(const Value &v);
    StringArray(const std::vector<std::string> &string_vec);
    ~StringArray();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY

    void append(const std::string &str);
};

// Array Type Only used for Storage.
class BooleanArray : public Value {
public:
    BooleanArray();
    BooleanArray(const std::vector<bool> &bool_vec);
    BooleanArray(const Value &other);
    ~BooleanArray();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY

    void append(bool b);
};


class Node : public Value {
public:
    Node();
    Node(uint_64 nodeId);
    Node(const Value& other);
    ~Node();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
};

class Edge : public Value {
public:
    Edge();
    Edge(uint_64 edgeId);
    Edge(const Value& other);
    ~Edge();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
};

class Path : public Value {
public:
    Path();
    Path(const Value &other);
    Path(const std::vector<uint_64> &_edge_id, const std::vector<uint_64> &_node_id);
    ~Path();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
};

class List : public Value {
public:
    List();
    List(const Value &other);
    ~List();

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY

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

    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
};

class NoValue : public Value {
public:
    NoValue();
    ~NoValue();
    
    Value& operator=(const Value& other);

    Type getType() const;
    int_64 hashCode() const;
    bool operator==(const Value& other) const;    // check equivalence for DISTINCT
    bool operator<(const Value& other) const;     // used for ORDER BY
};

/* helper functions */

Value * ValueDeepCopy(const Value *value);
