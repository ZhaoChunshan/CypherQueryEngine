#ifndef VALUE_EXPRESSION_H
#define VALUE_EXPRESSION_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
/* make it able to be compiled */
namespace GPStore{
    class Expression;
}
#include "../PQuery/PVarset.h"
#include "../PParser/Pattern.h"

namespace GPStore{
    
class Expression;
class AtomPropertyLabels;
class Atom;

/**
 * 表达式类
 * oprt!= EMPTY_OP，则内部结点，关注oprt和children
 * oprt== EMPTY_OP，则叶子节点，关注atom（以及可能的property_label)
 * 逻辑运算符OR XOR AND 组织成多叉树(e.g. 多个孩子用AND连起来)
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

    OperatorType oprt_;
	std::vector<Expression *> children_;	// children.size()==0 implies it's leaf node(i.e. atom)
	Atom* atom_;
    AtomPropertyLabels* property_label_;

    // 变量覆盖集合
    PVarset<unsigned> covered_var_id_;
    // 属性覆盖集合 a.age
    PVarset<std::pair<unsigned, unsigned>> covered_props_;

    Expression();
    Expression(const Expression& that);
    Expression& operator=(const Expression& that);
    ~Expression();
    void release();
    
    bool isAtom() const;
    bool isVariable() const;
    bool containsAggrFunc() const;
    /* if this is variable, return its name */
    std::string getVariableName() const;
    unsigned getVariableId() const;
    void print(int dep) const;

    
    /*  helper functions */ 
    static void printHead(int dep, const char *name, bool colon = true, bool endline = true);
    static Atom * AtomDeepCopy(Atom *atom);
    static std::string oprt2String(OperatorType op);
    
    static std::vector<Expression*> split(Expression *exp, OperatorType oprt);
};

// 属性标签表达式，用于 p.props.age; a:Person 这类表达式
class AtomPropertyLabels{
public:
    std::vector<std::string> key_names_;
    std::vector<std::string> node_labels_;
    unsigned prop_id_;  //keynames[0]
    AtomPropertyLabels();
    AtomPropertyLabels(const AtomPropertyLabels &that);
    AtomPropertyLabels& operator=(const AtomPropertyLabels &that);
    void addKeyName(const std::string &k);
    void addNodeLabel(const std::string &l);
    void print(int dep) const;
};

class Atom{
public:
	enum AtomType{LITERAL, PARAMETER, CASE_EXPRESSION, COUNT, LIST_COMPREHENSION, PATTERN_COMPREHENSION,
	QUANTIFIER, PATTERN_PREDICATE, FUNCTION_INVOCATION, EXISTENTIAL_SUBQUERY, VARIABLE,PARENTHESIZED_EXPRESSION};
	AtomType atom_type_;
    // 变量覆盖集合
    PVarset<unsigned> covered_var_id_;
    // 属性覆盖集合 a.age 暂未实现，因为要调用PStore
    PVarset<std::pair<unsigned, unsigned>> covered_props_;

    Atom() = default;
    virtual ~Atom() = default;
    virtual void print(int dep)const = 0;
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
    Literal(const Literal& that);

    ~Literal();
    void print(int dep)const override;
};

class Parameter: public Atom{
public:
	/* Cypher中的参数'$' ( oC_SymbolicName | DecimalInteger )，总是$开头，后面是字母串或者自然数*/
	std::string symbolic_name;
	unsigned  parameter_num;  // valid iff symbolic_name.length()==0
    Parameter() ;
    Parameter(unsigned n);
    Parameter(const std::string &sym_name);
    Parameter(const Parameter& that);

    ~Parameter();
    void print(int dep) const override;
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
    CaseExpression(const CaseExpression &that);
    ~CaseExpression();

    void print(int dep) const override;
};

/* only for aggregate func count(*) */
class Count : public Atom{
public:
    
    Count();
    Count(const Count& that);
    ~Count();

    void print(int dep) const override;
};

/* TODO: We dont support ListComprehension in this version */
class ListComprehension: public Atom{
public:
    /* [var in expression where filter | trans]*/
	std::string var_name_;  // necessary
    unsigned var_id_;       // id of var name
    Expression *exp_;     // necessary
    Expression *filter_;         // optional
	Expression *trans_;          // optional

    ListComprehension();
    ListComprehension(const ListComprehension& that);
    ~ListComprehension();


    void print(int dep) const override;
};

// TODO: We dont support pattern comprehension in this version.
class PatternComprehension: public Atom{
public:
	std::string var_name_;	// optional
    unsigned var_id_;
	std::unique_ptr<RigidPattern> pattern_;
	Expression *filter_;         // optional
	Expression *trans_;          // trans
    PatternComprehension();
    PatternComprehension(const PatternComprehension& that);
    ~PatternComprehension();

    void print(int dep) const override;
};

// TODO: We dont support quantifier in this version.
class Quantifier: public Atom{
public:
    /* all(variable IN list WHERE predicate) */
	enum QuantifierType {ALL, ANY, SINGLE, NONE};
	QuantifierType quantifier_type_;
	std::string var_name_;
    unsigned var_id_;
    Expression *container_;
    Expression *exp_;

    Quantifier();
    Quantifier(QuantifierType qt);
    Quantifier(const Quantifier& that);
    ~Quantifier();

    void print(int dep) const override;
};

// TODO: We dont support PatternPredicate in this version.
class PatternPredicate: public Atom{
public:
	std::unique_ptr<RigidPattern> pattern_;
    PatternPredicate();
    PatternPredicate(const PatternPredicate& that);
    ~PatternPredicate();

    void print(int dep) const override;
};

class FunctionInvocation : public Atom{
public:
	std::vector<std::string> func_name_;
	bool distinct;	// for example, count(DISTINCT p.city)
	std::vector<Expression *> args;

    FunctionInvocation();
    FunctionInvocation(const FunctionInvocation& that);
    ~FunctionInvocation();
    bool isAggregationFunction();
    void print(int dep) const override;
};

// TODO: We dont support ExistentialSubquery in this version.
class ExistentialSubquery : public Atom{
public:
	//EXISTS SP? '{' SP? ( oC_RegularQuery | ( oC_Pattern ( SP? oC_Where )? ) ) SP? '}' ;
	void *query_tree_;
	void *pattern_;
	Expression *where_;
    ExistentialSubquery();
    ExistentialSubquery(const ExistentialSubquery& that);
    ~ExistentialSubquery();

    void print(int dep) const override;
};

class Variable: public Atom{
public:
    static const unsigned ID_NONE = 0xffffffffU;
	std::string var_;
    unsigned id_;
    Variable();
    Variable(const std::string &s);
    Variable(const Variable& that);
    ~Variable();

    void print(int dep) const override;
};

class ParenthesizedExpression: public Atom{
public:
    Expression *exp_;
    ParenthesizedExpression();
    ParenthesizedExpression(const ParenthesizedExpression& that);
    ~ParenthesizedExpression();

    void print(int dep) const override;
};

}   // namespace GPStore

#endif
