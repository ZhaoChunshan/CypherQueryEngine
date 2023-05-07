#include "Expression.h"
#include <stdexcept>
#include <algorithm>
/**
 * helper functions
*/
void GPStore::Expression::printHead(int dep, const char *name, bool colon , bool endline){
    for(int i = 0; i < dep; ++i) printf("\t");
    printf(name);
    colon ? putchar(':') : 0;
    endline ? putchar('\n') : 0;
}


GPStore::Atom * GPStore::Expression::AtomDeepCopy(GPStore::Atom *atom){
    Atom *new_atom = nullptr;
    switch (atom->atom_type_){
        case Atom::LITERAL:
            new_atom = new Literal(*(Literal *)atom);
            break;
        case Atom::PARAMETER:
            new_atom = new Parameter(*(Parameter *)atom);
            break;
        case Atom::CASE_EXPRESSION:
            new_atom = new CaseExpression(*(CaseExpression *)atom);
            break;
        case Atom::COUNT:
            new_atom = new Count(*(Count *)atom);
            break;
        case Atom::LIST_COMPREHENSION:
            new_atom = new ListComprehension(*(ListComprehension *)atom);
            break;
        case Atom::PATTERN_COMPREHENSION:
            new_atom = new PatternComprehension(*(PatternComprehension *)atom);
            break;
        case Atom::QUANTIFIER:
            new_atom = new Quantifier(*(Quantifier *) atom);
            break;
        case Atom::PATTERN_PREDICATE: 
            new_atom = new PatternPredicate(*(PatternPredicate *)atom);
            break;
        case Atom::FUNCTION_INVOCATION:
            new_atom = new FunctionInvocation(*(FunctionInvocation *)atom);
            break;
        case Atom::EXISTENTIAL_SUBQUERY:
            new_atom = new ExistentialSubquery(*(ExistentialSubquery *)atom);
            break;
        case Atom::VARIABLE:
            new_atom = new Variable(*(Variable *)atom);
            break;
    }
    return new_atom;
}

std::string GPStore::Expression::oprt2String(OperatorType op){
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

/**
 * @brief split exp by operator oprt. SPLIT(e1 AND e2 AND e3) = [e1, e2, e3]
 * @param exp the Expression will be splited
 * @warning exp will de deleted, you cant use it after split.
*/
std::vector<GPStore::Expression*> 
GPStore::Expression::split(GPStore::Expression *exp, OperatorType oprt){
    std::vector<GPStore::Expression *> split_exps;
    if(exp->oprt_ != oprt) {
        split_exps.push_back(exp);
    } else {
        for(auto child : exp->children_){
            if(child->oprt_ != oprt){
                split_exps.push_back(child);
            } else {
                auto split_ = GPStore::Expression::split(child, oprt);
                for(auto sp : split_)
                    split_exps.push_back(sp);
            }
            child = nullptr;
        }
        delete exp;
    }
    return split_exps;
}

/* class: Expression */


GPStore::Expression::Expression():oprt_(EMPTY_OP), atom_(nullptr), property_label_(nullptr){

}   

GPStore::Expression::Expression(const Expression& that):oprt_(EMPTY_OP), atom_(nullptr), property_label_(nullptr){
    if(that.isAtom()){ 
        atom_ = AtomDeepCopy(that.atom_);
        if(that.property_label_ != nullptr){
            property_label_ = new AtomPropertyLabels(*that.property_label_);
        }
    }else{
        for(Expression *e : that.children_){
            children_.push_back(new Expression(*e));
        }
    }
    oprt_ = that.oprt_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
}

GPStore::Expression& GPStore::Expression::operator=(const Expression& that){
    if(&that == this) return *this;
    release();
    if(that.isAtom()){ 
        atom_ = GPStore::Expression::AtomDeepCopy(that.atom_);
        if(that.property_label_ != nullptr){
            property_label_ = new GPStore::AtomPropertyLabels(*that.property_label_);
        }
    }else{
        for(GPStore::Expression *e : that.children_){
            children_.push_back(new GPStore::Expression(*e));
        }
    }
    oprt_ = that.oprt_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    return *this;
}

GPStore::Expression::~Expression(){
    release();
}

/* release allocated memory */
void GPStore::Expression::release(){
    if(isAtom()){
        if(atom_ != nullptr)
            delete atom_;    
        if(property_label_ != nullptr)
            delete property_label_;
    }else{
        for(Expression *e : children_)
            if(e != nullptr)
                delete e;
        std::vector<Expression*>().swap(children_);
    }
    
    oprt_ = EMPTY_OP;
    atom_ = nullptr;
    property_label_ = nullptr;
    std::vector<unsigned>().swap(covered_var_id_.vars);
    std::vector<std::pair<unsigned, unsigned>>().swap(covered_props_.vars);
}

bool GPStore::Expression::isAtom() const{
    return oprt_ == EMPTY_OP;
}

bool GPStore::Expression::isVariable() const{
    return oprt_ == EMPTY_OP && atom_ != nullptr && atom_->atom_type_ == Atom::VARIABLE && property_label_ == nullptr;
}

bool GPStore::Expression::containsAggrFunc() const{
    if(oprt_ != EMPTY_OP){
        for(auto child : children_){
            if(child->containsAggrFunc())
                return true;
        }
    } else {
        auto atom_ty = atom_->atom_type_;
        if(atom_ty == Atom::LITERAL){
                auto lit = dynamic_cast<Literal*>(atom_);
                if(lit->literal_type == Literal::LIST_LITERAL){
                    for(auto e : lit->list_literal){
                        if(e->containsAggrFunc()) return true;
                    }
                }else if(lit->literal_type == Literal::MAP_LITERAL){
                    for(auto p : lit->map_literal){
                        if(p.second->containsAggrFunc()) return true;
                    }
                }
        } else if(atom_ty == Atom::PARAMETER){
            
        } else if(atom_ty == Atom::CASE_EXPRESSION){
                auto case_exp = dynamic_cast<CaseExpression*>(atom_);
                if(case_exp->case_type == CaseExpression::SIMPLE && \
                case_exp->test_expr->containsAggrFunc()) return true;
        } else if(atom_ty == Atom::COUNT){
                return true;
        } else if(atom_ty ==Atom::LIST_COMPREHENSION){

        } else if(atom_ty == Atom::PATTERN_COMPREHENSION){

        } else if(atom_ty ==Atom::QUANTIFIER){

        } else if(atom_ty == Atom::PATTERN_PREDICATE){

        } else if(atom_ty == Atom::FUNCTION_INVOCATION){
            auto func = dynamic_cast<FunctionInvocation*>(atom_);
            if(func->isAggregationFunction()) return true;
            for(auto arg: func->args)
                if(arg->containsAggrFunc()) return true;
        } else if(atom_ty ==  Atom::EXISTENTIAL_SUBQUERY){

        } else if(atom_ty ==  Atom::VARIABLE){

        }
    }
    return false;
}

std::string GPStore::Expression::getVariableName() const{
    return dynamic_cast<GPStore::Variable *>(atom_)->var_;
}

unsigned GPStore::Expression::getVariableId() const{
    return dynamic_cast<GPStore::Variable *>(atom_)->id_;
}

void GPStore::Expression::print(int dep) const{
    printHead(dep, "Expression");
    if(oprt_ == EMPTY_OP){
        // 这是一个Atom结点！
        atom_->print(dep + 1);
        if(property_label_ != nullptr){
            property_label_->print(dep + 1);
        }
        return;
    }
    // 处理各类Oprt结点！
    printHead(dep + 1, oprt2String(oprt_).c_str(), false);
    for(Expression *child : children_){
        child->print(dep + 1);
    }
}


/* class AtomPropertyLabels */

GPStore::AtomPropertyLabels::AtomPropertyLabels(){

}

GPStore::AtomPropertyLabels::AtomPropertyLabels(const AtomPropertyLabels &that){
    key_names_ = that.key_names_;
    node_labels_ = that.node_labels_;
    prop_id_ = that.prop_id_;
}

GPStore::AtomPropertyLabels& 
GPStore::AtomPropertyLabels:: operator=(const GPStore::AtomPropertyLabels &that){
    if(this == &that) return *this;
    key_names_ = that.key_names_;
    node_labels_ = that.node_labels_;
    prop_id_ = that.prop_id_;
    return *this;
}

void GPStore::AtomPropertyLabels::addKeyName(const std::string &k){
    key_names_.push_back(k);
}
void GPStore::AtomPropertyLabels::addNodeLabel(const std::string &l){
    node_labels_.push_back(l);
}

void GPStore::AtomPropertyLabels::print(int dep)const{
    Expression::printHead(dep, "Property Loop Up: ", false, false);
    for(const auto &p : key_names_){
        printf(".%s", p.c_str());
    }
    putchar('\n');
    Expression::printHead(dep, "Labels: ", false, false);
    for(const auto &l : node_labels_){
        printf(":%s", l.c_str());
    }
    putchar('\n');
}

/* class Atom */

/* class Literal */

GPStore::Literal::Literal(){
    atom_type_ = LITERAL;
    literal_type = NULL_LITERAL;
}

GPStore::Literal::Literal(LiteralType lt){
    atom_type_ = LITERAL;
    literal_type = lt;
}

GPStore::Literal::Literal(const Literal& that){
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    literal_type = that.literal_type;
    switch (that.literal_type)
    {
    case BOOLEAN_LITERAL:
        b = that.b;
        break;
    case NULL_LITERAL:
        break;
    case INT_LITERAL:
        i = that.i;
        break;
    case DOUBLE_LITERAL:
        d = that.d;
        break;
    case STRING_LITERAL:
        s = that.s;
        break;
    case LIST_LITERAL:
        for(auto e : that.list_literal){
            list_literal.push_back(new Expression(*e));
        }
        break;
    case MAP_LITERAL:
        for(const auto& p: that.map_literal){
            map_literal.insert(make_pair(p.first, new Expression(*p.second)));
        }
        break;
    default:
        break;
    }
}

GPStore::Literal::~Literal(){
    for(Expression *e : list_literal)
        if(e != nullptr)
            delete e;
    for(auto &p : map_literal)
        if(p.second != nullptr)
            delete p.second;
}

void GPStore::Literal::print(int dep) const{
    Expression::printHead(dep, "Literal: ", false, false);
    if(literal_type == BOOLEAN_LITERAL){
        printf(b ? "true" : "false");
        printf("(type: boolean)\n");
    }else if(literal_type == NULL_LITERAL){
        printf("NULL\n");
    }else if(literal_type == INT_LITERAL){
        printf("%lld(type: integer)\n", i);
    }else if(literal_type == DOUBLE_LITERAL){
        printf("%lf(type: double)\n", d);
    }else if(literal_type == STRING_LITERAL){
        printf("%s(type: string)\n", s.c_str());
    }else if(literal_type == LIST_LITERAL){
        printf("list\n");
        Expression::printHead(dep + 1, "[", false);
        for(auto &exp : list_literal){
            exp->print(dep + 2);
        }
        Expression::printHead(dep + 1, "]", false);
    }else if(literal_type == MAP_LITERAL){
        printf("map\n");
        Expression::printHead(dep + 1, "{", false);
        if(map_literal.size()){
            auto it = map_literal.begin();
            Expression::printHead(dep + 2, "KeyName", true, false);
            printf(" %s\n", it->first.c_str());
            it->second->print(dep + 2);
            for(++it; it != map_literal.end(); ++it){
                Expression::printHead(dep + 2, ",", false, true);
                Expression::printHead(dep + 2, "KeyName", true, false);
                printf(" %s\n", it->first.c_str());
                it->second->print(dep + 2);
            }
        }
        Expression::printHead(dep + 1, "}", false);
    }
    // DONE.
}

/* class: Parameter */

GPStore::Parameter::Parameter(){
    atom_type_ = PARAMETER;
}

GPStore::Parameter::Parameter(unsigned n){
    atom_type_ = PARAMETER;
    parameter_num = n;
}

GPStore::Parameter::Parameter(const std::string &sym_name){
    atom_type_ = PARAMETER;
    symbolic_name = sym_name;
}

GPStore::Parameter::Parameter(const Parameter& that){
    this->atom_type_ = that.atom_type_;
    symbolic_name = that.symbolic_name;
    parameter_num = that.parameter_num;
}

GPStore::Parameter::~Parameter(){ }


void GPStore::Parameter::print(int dep) const{
    std::string s = "Paramter: " + (symbolic_name.length () != 0 ? symbolic_name : "$" + std::to_string(parameter_num));
    Expression::printHead(dep, s.c_str(), false, true);
}

/* class: CaseExpression */

GPStore::CaseExpression::CaseExpression(): test_expr(nullptr), else_expr(nullptr) { 
    atom_type_ = CASE_EXPRESSION;
}

GPStore::CaseExpression::CaseExpression(CaseType ct): case_type(ct), test_expr(nullptr), else_expr(nullptr) {
    atom_type_ = CASE_EXPRESSION;
}

GPStore::CaseExpression::CaseExpression(const CaseExpression &that):test_expr(nullptr), else_expr(nullptr){
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    case_type = that.case_type;
    if(that.case_type == SIMPLE){
        test_expr = new Expression(*that.test_expr);
    }
    for(auto e : that.when_exprs){
        when_exprs.push_back(new Expression(*e));
    }
    for(auto e : that.then_exprs){
        then_exprs.push_back(new Expression(*e));
    }
    if(that.else_expr != nullptr){
        else_expr = new Expression(*that.else_expr);
    }
}

GPStore::CaseExpression::CaseExpression::~CaseExpression(){
    if(test_expr != nullptr)
        delete test_expr;
    for(Expression *e : when_exprs)
        if(e != nullptr)
            delete e;
    for(Expression *e : then_exprs)
        if(e != nullptr)
            delete e;
    if(else_expr != nullptr)
        delete else_expr;
}



void GPStore::CaseExpression::print(int dep) const {
    Expression::printHead(dep, "Case");
    if(case_type == SIMPLE){
        Expression::printHead(dep + 1, "TEST");
        test_expr->print(dep + 1);
    }
    for(int i = 0; i < when_exprs.size(); ++i){
        Expression::printHead(dep + 1, "WHEN");
        when_exprs[i]->print(dep + 1);
        Expression::printHead(dep + 1, "THEN");
        then_exprs[i]->print(dep + 1);
    }
    if(else_expr != nullptr){
        Expression::printHead(dep + 1, "ELSE");
        else_expr->print(dep + 1);
    }
}

/* class Count */

GPStore::Count::Count(){
    atom_type_ = COUNT;
}   

GPStore::Count::Count(const Count& that){
    atom_type_ = COUNT;
}

GPStore::Count::~Count(){

}


void GPStore::Count::print(int dep) const{
    Expression::printHead(dep, "COUNT (*)", false);
}

GPStore::ListComprehension::ListComprehension():exp_(nullptr), filter_(nullptr), trans_(nullptr){
    atom_type_ = LIST_COMPREHENSION;
}

GPStore::ListComprehension::ListComprehension(const ListComprehension& that):exp_(nullptr), filter_(nullptr), trans_(nullptr){
    atom_type_ = LIST_COMPREHENSION;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    var_name_ = that.var_name_;
    exp_ = new Expression(*that.exp_);
    if(that.filter_ != nullptr)
        filter_ = new Expression(*that.filter_);
    if(that.trans_ != nullptr)
        trans_ = new Expression(*that.trans_);
}

GPStore::ListComprehension::ListComprehension::~ListComprehension(){
    if(exp_ != nullptr)
        delete exp_;
    if(filter_ != nullptr)
        delete filter_;
    if(trans_ != nullptr)
        delete trans_;
}



void GPStore::ListComprehension::print(int dep) const{
    Expression::printHead(dep, "ListComprehension");
    Expression::printHead(dep + 1, "[", false, true);
    Expression::printHead(dep + 2, var_name_.c_str(), false);
    Expression::printHead(dep + 2, "IN", false);
    exp_->print(dep + 2);
    if(filter_ != nullptr){
        Expression::printHead(dep + 2, "WHERE", false);
        filter_->print(dep + 2);
    }
    if(trans_ != nullptr){
        Expression::printHead(dep + 2, "|", false);
        trans_->print(dep + 2);
    }
    Expression::printHead(dep + 1, "]", false);
    return;
}

GPStore::PatternComprehension::PatternComprehension(): filter_(nullptr), trans_(nullptr){
    atom_type_ = PATTERN_COMPREHENSION;
    throw std::runtime_error("[ERROR] Not implemented.");
}

GPStore::PatternComprehension::PatternComprehension(const PatternComprehension& that){
    throw std::runtime_error("[ERROR] Not implemented.");
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    var_name_ = that.var_name_;
    //TODO pattern_part_ = that.pattern_part_; 
    filter_ = new Expression(*that.filter_);
    trans_ = new Expression(*that.trans_); 
    
}

GPStore::PatternComprehension::~PatternComprehension(){
    // throw std::runtime_error("[ERROR] Not implemented.");
}


void GPStore::PatternComprehension::print(int dep)  const {
    throw std::runtime_error("[ERROR] Not implemented.");
}

GPStore::Quantifier::Quantifier():container_(nullptr), exp_(nullptr){
    atom_type_ = QUANTIFIER;
}


GPStore::Quantifier::Quantifier(QuantifierType qt):container_(nullptr), exp_(nullptr), quantifier_type_(qt){
    atom_type_ = QUANTIFIER;
}

GPStore::Quantifier::Quantifier(const Quantifier& that):container_(nullptr), exp_(nullptr) {
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    var_name_ = that.var_name_;
    quantifier_type_ = that.quantifier_type_;
    if(that.container_ != nullptr){
        container_ = new Expression(*that.container_);
    }
    if(that.exp_ != nullptr){
        exp_ = new Expression(*that.exp_);
    }
}

GPStore::Quantifier::~Quantifier(){
    if(container_ != nullptr){
        delete container_;
    }
    if(exp_ != nullptr){
        delete exp_;
    }
}


void GPStore::Quantifier::print(int dep) const{
    const char *s[4]={
        "ALL", "ANY", "SINGLE", "NONE"
    };
    Expression::printHead(dep, s[(int)quantifier_type_],false,false);
    printf("(\n");
    Expression::printHead(dep + 1, var_name_.c_str(), false);
    Expression::printHead(dep + 1, "IN",false);
    container_->print(dep + 1);
    if(exp_ != nullptr){
        Expression::printHead(dep + 1, "WHERE", false);
        exp_->print(dep + 1);
    }
    Expression::printHead(dep, ")", false);
}

GPStore::PatternPredicate::PatternPredicate(){
    throw std::runtime_error("[ERROR] Not implemented.");
}

GPStore::PatternPredicate::PatternPredicate(const PatternPredicate& that){
    throw std::runtime_error("[ERROR] Not implemented.");
}   

GPStore::PatternPredicate::~PatternPredicate(){
    throw std::runtime_error("[ERROR] Not implemented.");
}


void GPStore::PatternPredicate::print(int dep) const {
    throw std::runtime_error("[ERROR] Not implemented.");
}


GPStore::FunctionInvocation::FunctionInvocation():distinct(false){
    atom_type_ = FUNCTION_INVOCATION;
}

GPStore::FunctionInvocation::FunctionInvocation(const FunctionInvocation& that){
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    func_name_ = that.func_name_;
    distinct = that.distinct;
    for(auto e : that.args){
        args.push_back(new Expression(*e));
    }
}

GPStore::FunctionInvocation::~FunctionInvocation(){
    for(Expression *e : args)
        if(e != nullptr)
            delete e;
}

bool GPStore::FunctionInvocation::isAggregationFunction(){
    if(func_name_.size() != 1) return false;

    std::string str = func_name_[0];
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::vector<std::string> aggr_func{"avg", "collect", "count", "max", "min", "percentilecont", "percentiledisc", "stdev", "stdevp", "sum"};
    
    return (std::find(aggr_func.begin(), aggr_func.end(), str) != aggr_func.end());
}

void GPStore::FunctionInvocation::print(int dep) const {
    // Print Head && Function Name
    Expression::printHead(dep, "Function: ", false, false);
    printf("%s", func_name_[0].c_str());
    for(int i = 1; i < func_name_.size(); ++i)
        printf(".%s", func_name_[i].c_str());
    printf("(\n");
    // Distinct
    if(distinct)
        Expression::printHead(dep + 1, "DISTINCT", false);
    // Print args
    for(auto e : args){
        e->print(dep + 1);
    }
    Expression::printHead(dep, ")", false, true);
}


GPStore::ExistentialSubquery::ExistentialSubquery(){
    throw std::runtime_error("[ERROR] Not implemented.");
}

GPStore::ExistentialSubquery::ExistentialSubquery(const ExistentialSubquery& that){
    throw std::runtime_error("[ERROR] Not implemented.");
}

GPStore::ExistentialSubquery:: ~ExistentialSubquery(){
    throw std::runtime_error("[ERROR] Not implemented.");
}

void GPStore::ExistentialSubquery::print(int dep)const{
    throw std::runtime_error("[ERROR] Not implemented.");
}

/* class Variable */

GPStore::Variable::Variable(){
    atom_type_ = VARIABLE;
    id_ = ID_NONE;
}

GPStore::Variable::Variable(const std::string &s){
    atom_type_ = VARIABLE;
    var_ = s;
    id_ = ID_NONE;
}

GPStore::Variable::Variable(const Variable& that){
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    var_ = that.var_;
    id_ = that.id_;
}

GPStore::Variable::~Variable(){

}

void GPStore::Variable::print(int dep) const {
    Expression::printHead(dep, "Variable: ", false, false);
    printf("%s\n", var_.c_str());
}


GPStore::ParenthesizedExpression::ParenthesizedExpression(){
    atom_type_ = PARENTHESIZED_EXPRESSION;
    exp_ = nullptr;
}

GPStore::ParenthesizedExpression::ParenthesizedExpression(const ParenthesizedExpression& that){
    atom_type_ = that.atom_type_;
    exp_ = new Expression(*that.exp_);
}

GPStore::ParenthesizedExpression::~ParenthesizedExpression(){
    if(exp_ != nullptr)
        delete exp_;
}

void GPStore::ParenthesizedExpression::print(int dep) const {
    Expression::printHead(dep, "ParenthesizedExpression", true, true);
    exp_->print(dep + 1);
}