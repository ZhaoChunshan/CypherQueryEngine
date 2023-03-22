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
        struct {
            std::vector<uint_64>* edgeId;
            std::vector<uint_64>* nodeId;
        }Path;

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

    Type getType();
    int_64 hashCode();
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY

};

class IntArray : public Value {
public:
    std::vector<int_64> value;

    IntArray();
    IntArray(const Value &v);
    IntArray(const std::vector<uint_64> &int_vec);
    ~IntArray();

    Type getType();
    int_64 hashCode();
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};

class FloatArray : public Value {
public:
    std::vector<double> value;
    FloatArray();
    FloatArray(const Value &v);
    FloatArray(const std::vector<double> &double_vec);
    ~FloatArray();

    Type getType();
    int_64 hashCode();
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY

};

class StringArray : public Value {
public:
    std::vector<std::string> value;
    StringArray();
    StringArray(const Value &v);
    StringArray(const std::vector<std::string> &string_vec);
    ~StringArray();

    Type getType();
    int_64 hashCode();
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};

class BooleanArray : public Value {
public:
    std::vector<bool> value;
    BooleanArray();
    BooleanArray(const std::vector<bool> &bool_vec);
    BooleanArray(const Value &other);
    ~BooleanArray();

    Type getType();
    int_64 hashCode();
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};


class Node : public Value {
public:
    uint_64 id;
    Node();
    Node(uint_64 nodeId);
    Node(const Value& other);
    ~Node();

    Type getType();
    int_64 hashCode();
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};

class Edge : public Value {
public:
    uint_64 id;
    Edge();
    Edge(uint_64 edgeId);
    Edge(const Value& other);
    ~Edge();

    Type getType();
    int_64 hashCode();
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};

class Path : public Value {
public:
    std::vector<uint_64> edgeId;    // length of n
    std::vector<uint_64> nodeId;    // length of n + 1
    Path();
    Path(const Value &other);
    Path(const std::vector<uint_64> &_edge_id, const std::vector<uint_64> &_node_id);
    ~Path();

    Type getType();
    int_64 hashCode();
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};

class List : public Value {
public:
    std::vector<Value *> values;

    List();
    List(const Value &other);
    ~List();

    Type getType();
    int_64 hashCode();
    Value& operator=(const Value& other);
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};

class Map : public Value {
public:
    std::map<std::string, Value *> mp;

    Map();
    Map(const Value &other);
    ~Map();

    Type getType();
    int_64 hashCode();
    Value& operator=(const Value& other);
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};

class NoValue : public Value {
    NoValue();
    ~NoValue();
    
    Type getType();
    int_64 hashCode();
    Value& operator=(const Value& other);
    bool operator==(const Value& other);    // check equivalence for DISTINCT
    bool operator<(const Value& other);     // used for ORDER BY
};