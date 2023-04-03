#include <string>
#include <vector>
#include <map>
#include <set>

class Pattern;
class PatternPart;
class QueryTree;
class Expression;
class AtomPropertyLabels;
class Atom;
/**
 * 表达式类
 * oprt!= EMPTY_OP，则内部结点，关注oprt和children
 * oprt== EMPTY_OP，则叶子节点，关注atom（以及可能的property_label)
 * 逻辑运算符OR XOR AND NOT组织成多叉树(e.g. 多个孩子用AND连起来)
 * 其他的运算符组织成二叉树(i.e. children.size() == 2)
*/
class Expression{
public:
	enum OperatorType{
        OR,
        XOR, 
        AND, 
        NOT, 
        EQUAL, NOT_EQUAL, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, 
        IN,
        STARTS_WITH, ENDS_WITH, CONTAINS,
        IS_NULL, IS_NOT_NULL,
        ADD, SUB,
        MUL, DIV, MOD,
        POW,
        IDENTITY, NEGATION, // 正负号
        INDEX, SLICE, // a[10], a["age"], or m[1:4]
        // 最后一种是oC_PropertyOrLabelsExpression，存在propery_label里
        EMPTY_OP    // no op, it's leaf node
    };

    OperatorType oprt;
	std::vector<Expression *> children;	// children.size()==0 implies it's leaf node(i.e. atom)
	Atom* atom;
    AtomPropertyLabels* property_label;

    // 变量覆盖集合
    std::set<std::string> covered_vars;
    std::set<unsigned long long> covered_vars_id; // 解析完，执行中，给当前的WithBlock中的变量分配的ID。运行中变量的id，并不是sid oid eid这种。
    
    Expression();
    ~Expression();

    bool isLeafNode();
    void addChildExp(Expression *exp);
    void setOprt(OperatorType op);
    void setAtom(Atom *_atom);
    void setAtomPropLabels(AtomPropertyLabels *apl);
    static std::string OprtToString(OperatorType op);
    Expression *deepCopy();
    void buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id);

    void print(int dep);
};

// 属性标签表达式，用于 p.props.age; a:Person 这类表达式
class AtomPropertyLabels{
public:
    std::vector<std::string> key_names;
    std::vector<std::string> node_labels;
    AtomPropertyLabels();
    AtomPropertyLabels(const AtomPropertyLabels &other);
    void addKeyName(const std::string &k);
    void addNodeLabel(const std::string &l);
    void print(int dep);
};

class Atom{
public:
	enum AtomType{LITERAL, PARAMETER, CASE_EXPRESSION, COUNT, LIST_COMPREHENSION, PATTERN_COMPREHENSION,
	QUANTIFIER, PATTERN_PREDICATE, PARENTHESIZED_EXPRESSION, FUNCTION_INVOCATION, EXISTENTIAL_SUBQUERY, VARIABLE};
	AtomType atom_type;
    std::set<std::string> covered_vars;
    std::set<unsigned long long> covered_vars_id;
    Atom() = default;
    virtual ~Atom() = 0;
    virtual void buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) = 0;
    virtual Atom * deepCopy() = 0;
    virtual void print(int dep) = 0;
};

class Literal: public Atom{
public:
	enum LiteralType{BOOLEAN_LITERAL, NULL_LITERAL, INT_LITERAL, DOUBLE_LITERAL, STRING_LITERAL, LIST_LITERAL, MAP_LITERAL};
	LiteralType literal_type;
	double d;
	long long i;
	bool b;
	std::string s;
	std::vector<Expression *> list_literal;
	std::map<std::string, Expression *> map_literal;
    Literal();
    Literal(LiteralType lt);
    ~Literal();
    void setLiteralType(LiteralType literal_t);
    void append(Expression *list_elem);
    void insert(const std::string &key, Expression *value);
    void buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) override;
    Atom * deepCopy() override;
    void print(int dep) override;
};

class Parameter: public Atom{
public:
	/* Cypher中的参数'$' ( oC_SymbolicName | DecimalInteger )，总是$开头，后面是字母串或者自然数*/
	std::string symbolic_name;
	unsigned long long parameter_num;  // valid iff symbolic_name.length()==0
    Parameter() ;
    Parameter(unsigned long long  n);
    Parameter(const std::string &sym_name);
    void buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) override;
    Atom * deepCopy() override;
    void print(int dep) override;
};

class CaseExpression: public Atom{
public:
	enum CaseType{SIMPLE, GENERIC};
    CaseType case_type;
	Expression *test_expr;  // not null if case_type == SIMPLE
	std::vector<Expression *> when_exprs;
	std::vector<Expression *> then_exprs;
	Expression *else_expr;

    CaseExpression();
    CaseExpression(CaseType ct);
    ~CaseExpression();

    void setCaseType(CaseType case_t);
    
    void addWhen(Expression *exp);
    void addThen(Expression *exp);

    void buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) override;
    Atom * deepCopy() override;
    void print(int dep) override;
};

class Count : public Atom{
public:
    /* only for aggregate func count(*) */
    Count();
    ~Count();
    void buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) override;
    Atom * deepCopy() override;
    void print(int dep) override;
};

class ListComprehension: public Atom{
public:
    /* [var in expression where filter | trans]*/
	std::string variable_name;  // necessary
    Expression *expression;     // necessary
    Expression *filter;         // optional
	Expression *trans;          // optional

    ListComprehension();
    ~ListComprehension();

    void setVarName(const std::string &s);

    void buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) override;
    Atom * deepCopy() override;
    void print(int dep) override;
};

class PatternComprehension: public Atom{
public:
    // TODO: Comprehension涉及新的作用域的问题！现在好像还没考虑周到。
	std::string variable_name;	// optional
	PatternPart *pattern_part;  // necessary
	Expression *filter;         // optional
	Expression *trans;          // trans
    PatternComprehension();
    ~PatternComprehension();
    void setVarName(const std::string &s);
    void buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) override;
    Atom * deepCopy() override;
    void print(int dep)  override;
};

class Quantifier: public Atom{
public:
    /* all(variable IN list WHERE predicate) */
	enum QuantifierType {ALL, ANY, SINGLE, NONE};
	QuantifierType quantifier_type;
	std::string variable_name;
    Expression *expression;
    Expression *predicate;
    Quantifier(): expression(nullptr), predicate(nullptr){}
    Quantifier(QuantifierType qt): quantifier_type(qt), expression(nullptr), predicate(nullptr){}
    ~Quantifier();
    void setQtfType(QuantifierType qt);
    void setVarName(const std::string &name);
    void print(int dep)  override;
};

class PatternPredicate: public Atom{
public:
	PatternPart *pattern_part;
    PatternPredicate(): pattern_part(nullptr){}
    ~PatternPredicate();
    void print(int dep)  override;
};

class ParenthesizedExpression : public Atom{
public:
	Expression *exp;
    ParenthesizedExpression():exp(nullptr){}
    ~ParenthesizedExpression();
    void print(int dep)  override;
};

class FunctionInvocation : public Atom{
public:
	std::vector<std::string> function_name;
	bool distinct;	// for example, count(DISTINCT p.city)
	std::vector<Expression *> args;
    FunctionInvocation():distinct(false){}
    ~FunctionInvocation();
    void setDistinct(bool dis);
    void addArgExp(Expression *exp);
    void print(int dep) override;
};

class ExistentialSubquery : public Atom{
public:
	//EXISTS SP? '{' SP? ( oC_RegularQuery | ( oC_Pattern ( SP? oC_Where )? ) ) SP? '}' ;
	QueryTree *regular_query;
	Pattern *pattern;
	Expression *where_part;
    ExistentialSubquery():regular_query(nullptr), pattern(nullptr), where_part(nullptr){}

    ~ExistentialSubquery();
    void print(int dep) override;
};

class Variable: public Atom{
public:
	std::string name;
    Variable(){}
    Variable(const std::string &s):name(s){}
    void setName(const std::string &s);
    void print(int dep) override;
};