#include "Expression.h"
using namespace std;

/**
 * helper functions for print
 * 
*/
void printHead(int dep, const char *name, bool colon = true, bool endline = true){
    for(int i = 0; i < dep; ++i) printf("\t");
    printf(name);
    colon ? putchar(':') : 0;
    endline ? putchar('\n') : 0;
}

/* class: Expression */

Expression::Expression():oprt(EMPTY_OP), atom(nullptr), property_label(nullptr){

}   

Expression::~Expression(){
    for(Expression *e : children)
        if(e != nullptr)
            delete e;
    if(atom != nullptr)
        delete atom;
    if(property_label != nullptr)
        delete property_label;
}

bool Expression::isLeafNode(){
    return oprt == EMPTY_OP;
}

void Expression::addChildExp(Expression *exp){
    children.push_back(exp);
}

void Expression::setOprt(OperatorType op){
    oprt = op;
}

void Expression::setAtom(Atom *_atom){
    atom = _atom;
}

void Expression::setAtomPropLabels(AtomPropertyLabels *apl){
    property_label = apl;
}

std::string Expression::OprtToString(OperatorType op){
    switch (op){
        case OR:                return "OR";
        case XOR:               return "XOR";
        case AND:               return "AND";
        case NOT:               return "NOT";
        case EQUAL:             return "=";
        case NOT_EQUAL:         return "<>";
        case LESS:              return "<";
        case GREATER:           return ">";
        case LESS_EQUAL:        return "<=";
        case GREATER_EQUAL:     return ">=";
        case IN:                return "IN";
        case STARTS_WITH:       return "STARTS_WITH";
        case ENDS_WITH:         return "ENDS_WITH";
        case CONTAINS:          return "CONTAINS";
        case IS_NULL:           return "IS NULL";
        case IS_NOT_NULL:       return "IS NOT NULL";
        case ADD:               return "+";
        case SUB:               return "-";
        case MUL:               return "*";
        case DIV:               return "/";
        case MOD:               return "%";
        case POW:               return "^";
        case IDENTITY:          return "u+";
        case NEGATION:          return "u-";
        case INDEX:             return "[]";
        case SLICE:             return "[]";        
    }
    return "EMPTY OP";
}

Expression *Expression::deepCopy(){
    Expression *exp = new Expression();
    exp->setOprt(oprt);
    for(const string& s : covered_vars){
            exp->covered_vars.insert(s);
    }
    for(auto id : covered_vars_id){
        exp->covered_vars_id.insert(id);
    }
    if(oprt == EMPTY_OP){
        if(atom != nullptr){
            exp->setAtom(atom->deepCopy());
            exp->setAtomPropLabels(new AtomPropertyLabels(*property_label));
        }
        
    } else{
        for(Expression *child : children){
            exp->children.push_back(child->deepCopy());
        }
    }
    return exp;
}


// Assume each node in the expression true has covered_vars.
// we just need to map var->id along the tree.
void Expression::buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id){
    for(const string &var : covered_vars){
        covered_vars_id.insert(var2id.at(var));
    }
    if(oprt == EMPTY_OP){
        atom->buildCoveredVarsId(var2id);
    } else {
        for(Expression *child : children){
            child->buildCoveredVarsId(var2id);
        }
    }
    return;
}

void Expression::print(int dep){
    printHead(dep, "Expression");
    if(oprt == EMPTY_OP){
        // 这是一个Atom结点！
        atom->print(dep + 1);
        if(property_label != nullptr){
            property_label->print(dep + 1);
        }
        return;
    }
    // 处理各类Oprt结点！
    printHead(dep + 1, OprtToString(oprt).c_str(), false);
    for(Expression *child : children){
        child->print(dep + 1);
    }
}


/* class AtomPropertyLabels */

AtomPropertyLabels::AtomPropertyLabels(){

}

AtomPropertyLabels::AtomPropertyLabels(const AtomPropertyLabels &other){
    for(const string& k : other.key_names){
        key_names.push_back(k);
    }
    for(const string& l : other.node_labels){
        node_labels.push_back(l);
    }
}

void AtomPropertyLabels::addKeyName(const std::string &k){
    key_names.push_back(k);
}
void AtomPropertyLabels::addNodeLabel(const std::string &l){
    node_labels.push_back(l);
}

void AtomPropertyLabels::print(int dep){
    printHead(dep, "Property Loop Up: ", false, false);
    for(const auto &p : key_names){
        printf(".%s", p.c_str());
    }
    putchar('\n');
    printHead(dep, "Labels: ", false, false);
    for(const auto &l : node_labels){
        printf(":%s", l.c_str());
    }
    putchar('\n');
}

/* class Atom */

/* class Literal */

Literal::Literal(){
    atom_type = LITERAL;
    literal_type = NULL_LITERAL;
}

Literal::Literal(LiteralType lt){
    atom_type = LITERAL;
    literal_type = lt;
}

Literal::~Literal(){
    for(Expression *e : list_literal)
        if(e != nullptr)
            delete e;
    for(auto &p : map_literal)
        if(p.second != nullptr)
            delete p.second;
}

void Literal::setLiteralType(LiteralType literal_t){
    literal_type = literal_t;
}

void Literal::append(Expression *list_elem){
    list_literal.push_back(list_elem);
}

void Literal::insert(const std::string &key, Expression *value){
    map_literal.insert(make_pair(key, value));
}

void Literal::buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id){
    for(const string& s : covered_vars){
        covered_vars_id.insert(var2id.at(s));
    }
    if(literal_type == LIST_LITERAL){
        for(Expression *e : list_literal){
            e->buildCoveredVarsId(var2id);
        }
    }else if(literal_type == MAP_LITERAL){
        for(const auto&p : map_literal){
            p.second->buildCoveredVarsId(var2id);
        }
    } 
    return;
}

Atom * Literal::deepCopy() {
    Literal *l = new Literal(literal_type);
    switch(literal_type){
        case BOOLEAN_LITERAL:
            l->b = b;
            break;
        case NULL_LITERAL:
            break;
        case INT_LITERAL:
            l->i = i;
            break;
        case DOUBLE_LITERAL:
            l->d = d;
            break;
        case STRING_LITERAL:
            l->s = s;
            break;
        case LIST_LITERAL:
            for(Expression *e : list_literal){
                l->list_literal.push_back(e->deepCopy());
            }
            break;
        case MAP_LITERAL:
            for(const auto& p: map_literal){
                l->map_literal.insert(make_pair(p.first, p.second->deepCopy()));
            }
            break;
    }
    return (Atom *)l;
}

void Literal::print(int dep) {
    printHead(dep, "Literal: ", false, false);
    if(literal_type == BOOLEAN_LITERAL){
        printf(b ? "true" : "false");
        printf("(type: boolean)\n");
    }else if(literal_type == NULL_LITERAL){
        printf("NULL\n");
    }else if(literal_type == INT_LITERAL){
        printf("%d(type: integer)\n", i);
    }else if(literal_type == DOUBLE_LITERAL){
        printf("%lf(type: double)\n", d);
    }else if(literal_type == STRING_LITERAL){
        printf("%s(type: string)\n", s.c_str());
    }else if(literal_type == LIST_LITERAL){
        printf("list\n");
        printHead(dep + 1, "[", false);
        for(auto &exp : list_literal){
            exp->print(dep + 2);
        }
        printHead(dep + 1, "]", false);
    }else if(literal_type == MAP_LITERAL){
        printf("map\n");
        printHead(dep + 1, "{", false);
        if(map_literal.size()){
            auto it = map_literal.begin();
            printHead(dep + 2, "KeyName", true, false);
            printf(" %s\n", it->first.c_str());
            it->second->print(dep + 2);
            for(++it; it != map_literal.end(); ++it){
                printHead(dep + 2, ",", false, true);
                printHead(dep + 2, "KeyName", true, false);
                printf(" %s\n", it->first.c_str());
                it->second->print(dep + 2);
            }
        }
        printHead(dep + 1, "}", false);
    }
    // DONE.
}

/* class: Parameter */

Parameter::Parameter(){

}

Parameter::Parameter(unsigned long long  n){
    parameter_num = n;
}

Parameter::Parameter(const std::string &sym_name):symbolic_name(sym_name){

}

void Parameter::buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) {
    // A parameter doesnot cover any variable, just return
    return;    
}

Atom * Parameter::deepCopy() {
    Atom *a;
    if(symbolic_name.length()){
        a = new Parameter(symbolic_name);
    }else{
        a = new Parameter(parameter_num);
    }
    return a;
}

void Parameter::print(int dep) {
    string s = "Paramter: " + (symbolic_name.length () != 0 ? symbolic_name : "$" + to_string(parameter_num));
    printHead(dep, s.c_str(), false, true);
}

/* class: CaseExpression */

CaseExpression::CaseExpression(): test_expr(nullptr), else_expr(nullptr) { }

CaseExpression::CaseExpression(CaseType ct): case_type(ct), test_expr(nullptr), else_expr(nullptr) { }

CaseExpression::~CaseExpression(){
    if(test_expr != nullptr)
        delete test_expr;
    for(Expression *e : when_exprs)
        delete e;
    for(Expression *e : then_exprs)
        delete e;
    if(else_expr != nullptr)
        delete else_expr;
}

void CaseExpression::setCaseType(CaseType case_t){
    case_type = case_t;
}


void CaseExpression::addWhen(Expression *exp){
    when_exprs.push_back(exp);
}

void CaseExpression::addThen(Expression *exp){
    then_exprs.push_back(exp);
}

void CaseExpression::buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id){
    for(const string &s : covered_vars){
        covered_vars_id.insert(var2id.at(s));
    }
    if(test_expr != nullptr)
        test_expr->buildCoveredVarsId(var2id);
    for(Expression *w : when_exprs){
        w->buildCoveredVarsId(var2id);
    }
    for(Expression *t : then_exprs){
        t->buildCoveredVarsId(var2id);
    }
    if(else_expr != nullptr){
        else_expr->buildCoveredVarsId(var2id);
    }
    return;
}


Atom * CaseExpression::deepCopy() {
    CaseExpression *ce = new CaseExpression(case_type);
    if(test_expr != nullptr){
        ce->test_expr = test_expr->deepCopy();
    }
    for(Expression *e : when_exprs){
        ce->when_exprs.push_back(e->deepCopy());
    }
    for(Expression *e : then_exprs){
        ce->then_exprs.push_back(e->deepCopy());
    }
    if(else_expr != nullptr){
        ce->else_expr = else_expr->deepCopy();
    }
    return (Atom *)ce;
}

void CaseExpression::print(int dep) {
    printHead(dep, "Case");
    if(case_type == SIMPLE){
        printHead(dep + 1, "TEST");
        test_expr->print(dep + 1);
    }
    for(int i = 0; i < when_exprs.size(); ++i){
        printHead(dep + 1, "WHEN");
        when_exprs[i]->print(dep + 1);
        printHead(dep + 1, "THEN");
        then_exprs[i]->print(dep + 1);
    }
    if(else_expr != nullptr){
        printHead(dep + 1, "ELSE");
        else_expr->print(dep + 1);
    }
}

/* class Count */
Count::Count(){
    atom_type = COUNT;
}

Count::~Count(){

}

void Count::buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id){
    for(const string& s : covered_vars){
        covered_vars_id.insert(var2id.at(s));
    }
}

Atom * Count::deepCopy() {
    Count *cnt = new Count();
    for(const string& s : covered_vars){
        cnt->covered_vars.insert(s);
    }
    for(auto id : covered_vars_id){
        cnt->covered_vars_id.insert(id);
    }
    return (Atom *)cnt;
}
void Count::print(int dep) {
    printHead(dep, "COUNT (*)", false);
}

ListComprehension::ListComprehension():expression(nullptr), filter(nullptr), trans(nullptr){
    atom_type = LIST_COMPREHENSION;
}

ListComprehension::~ListComprehension(){
    if(expression != nullptr)
        delete expression;
    if(filter != nullptr)
        delete filter;
    if(trans != nullptr)
        delete trans;
}

void ListComprehension::setVarName(const std::string &s){
    variable_name = s;
}

void ListComprehension::buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id){
    for(const string& s : covered_vars){
        covered_vars_id.insert(var2id.at(s));
    }
    expression->buildCoveredVarsId(var2id);
    if(filter != nullptr){
        filter->buildCoveredVarsId(var2id);
    }
    if(trans != nullptr){
        trans->buildCoveredVarsId(var2id);
    }
}

Atom * ListComprehension::deepCopy() {
    ListComprehension *lsc = new ListComprehension();
    lsc->expression = expression->deepCopy();
    if(filter != nullptr)
        lsc->filter = filter->deepCopy();
    if(trans != nullptr)
        lsc->trans = trans->deepCopy();
}

void ListComprehension::print(int dep) {
    printHead(dep, "ListComprehension");
    printHead(dep + 1, "[", false, true);
    printHead(dep + 2, variable_name.c_str(), false);
    printHead(dep + 2, "IN", false);
    expression->print(dep + 2);
    if(filter != nullptr){
        printHead(dep + 2, "WHERE", false);
        filter->print(dep + 2);
    }
    if(trans != nullptr){
        printHead(dep + 2, "|", false);
        trans->print(dep + 2);
    }
    printHead(dep + 1, "]", false);
    return;
}

PatternComprehension::PatternComprehension(): pattern_part(nullptr), filter(nullptr), trans(nullptr){
    atom_type = PATTERN_COMPREHENSION;
}

PatternComprehension::~PatternComprehension(){
    if(pattern_part != nullptr)
        delete pattern_part;
    if(filter != nullptr)
        delete filter;
    if(trans != nullptr)
        delete trans;
}

void PatternComprehension::setVarName(const std::string &s){
    variable_name = s;
}

void PatternComprehension::buildCoveredVarsId(const std::map<std::string, unsigned long long>& var2id) override;
Atom * PatternComprehension::deepCopy() override;
void PatternComprehension::print(int dep)  override;

Quantifier::~Quantifier(){
    if(expression != nullptr)
        delete expression;
    if(predicate != nullptr)
        delete predicate;
}

void Quantifier::setQtfType(QuantifierType qt){
    quantifier_type = qt;
}

void Quantifier::setVarName(const std::string &name){
    variable_name = name;
}

PatternPredicate::~PatternPredicate(){
    if(pattern_part != nullptr)
        delete pattern_part;
}

ParenthesizedExpression::~ParenthesizedExpression(){
    if(exp != nullptr)
        delete exp;
}

FunctionInvocation::~FunctionInvocation(){
    for(Expression *e : args)
        delete e;
}

void FunctionInvocation::setDistinct(bool dis){
    distinct = dis;
}

void FunctionInvocation::addArgExp(Expression *exp){
    args.push_back(exp);
}

ExistentialSubquery::~ExistentialSubquery(){
    if(regular_query != nullptr)
        delete regular_query;
    if(pattern != nullptr)
        delete pattern;
    if(where_part != nullptr)
        delete where_part;
}

void Variable::setName(const std::string &s){
    name = s;
}