#include "Expression.h"
#include <stdexcept>
#include <algorithm>

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
        case Atom::PARENTHESIZED_EXPRESSION:
            new_atom = new ParenthesizedExpression(*(ParenthesizedExpression *) atom);
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
        case IDENTITY:          return "+";
        case NEGATION:          return "-";
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
        for(auto & child : exp->children_){
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


GPStore::Expression * GPStore::Expression::VarNonEqualToExpression(const std::string& var1, const std::string& var2, unsigned id1, unsigned id2){
    GPStore::Variable * v1 = new GPStore::Variable(var1, id1);
    GPStore::Variable * v2 = new GPStore::Variable(var2, id2);
    GPStore::Expression *exp1 = new GPStore::Expression;
    GPStore::Expression *exp2 = new GPStore::Expression;
    GPStore::Expression *exp = new GPStore::Expression;
    exp1->oprt_ = exp2->oprt_ = GPStore::Expression::EMPTY_OP;
    exp1->atom_ = v1;
    exp1->covered_var_id_.addVar(id1);
    exp2->covered_var_id_.addVar(id2);
    exp->oprt_ = GPStore::Expression::NOT_EQUAL;
    exp->children_.push_back(exp1);
    exp->children_.push_back(exp2);
    exp->covered_var_id_ = exp->children_[0]->covered_var_id_ + exp->children_[1]->covered_var_id_;
    return exp;
}

/**
 * @brief Transform `var.prop = exp` to an expression. After the call, exp can't be used.
 */
GPStore:: Expression*
GPStore::Expression::VarPropertyToExpression(unsigned var_id, const std::string & var_name, unsigned prop_id,
                                             const std::string & prop_key_name, GPStore::Expression *exp){
    Expression *left = new GPStore::Expression;
    left->oprt_ = GPStore::Expression::EMPTY_OP;
    Variable * var = new Variable;
    var->id_ = var_id;
    var->var_ = var_name;
    var->covered_var_id_.addVar(var_id);
    left->atom_ = var;
    left->property_label_ = new GPStore::AtomPropertyLabels;
    left->property_label_->prop_key_names_.emplace_back(prop_key_name);
    left->property_label_->prop_ids_.push_back(prop_id);

    left->covered_var_id_.addVar(var_id);
    left->covered_props_.addVar(std::make_pair(var_id, prop_id));

    Expression *right = new GPStore::Expression(*exp);
    Expression *res = new GPStore::Expression;
    res->oprt_ = GPStore::Expression::EQUAL;
    res->children_.push_back(left);
    res->children_.push_back(right);
    res->covered_var_id_ = left->covered_var_id_ + right->covered_var_id_;
    res->covered_props_ = left->covered_props_ + right->covered_props_;

    return res;
}

/**
 * @brief Join some Expressions use oprt, oprt must be one of AND, OR, XOR. After the call, exprs cant be used.
 *
 * */
GPStore::Expression*
GPStore::Expression::JoinExpressionBy(const std::vector<Expression* > & exprs,OperatorType oprt){
    Expression *res = new Expression;
    res->oprt_ = oprt;
    for(auto e : exprs){
        res->children_.push_back(e);
        res->covered_var_id_ += e->covered_var_id_;
        res->covered_props_ += e->covered_props_;
    }
    return res;
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
            if(e != nullptr)
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
            if(e != nullptr)
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

bool GPStore::Expression::isVariableProp() const{
    return oprt_ == EMPTY_OP && atom_ != nullptr && atom_->atom_type_ == Atom::VARIABLE && property_label_ != nullptr
        && property_label_->prop_ids_.size() == 1;
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
                if(lit->literal_type_ == Literal::LIST_LITERAL){
                    for(auto e : lit->list_literal_){
                        if(e->containsAggrFunc()) return true;
                    }
                }else if(lit->literal_type_ == Literal::MAP_LITERAL){
                    for(auto p : lit->map_literal_){
                        if(p.second->containsAggrFunc()) return true;
                    }
                }
        } else if(atom_ty == Atom::PARAMETER){
            
        } else if(atom_ty == Atom::CASE_EXPRESSION){
                auto case_exp = dynamic_cast<CaseExpression*>(atom_);
                if(case_exp->case_type_ == CaseExpression::SIMPLE && \
                case_exp->test_exp_->containsAggrFunc()) return true;
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

        } else if(atom_ty == Atom::PARENTHESIZED_EXPRESSION){
            auto par_exp = dynamic_cast<ParenthesizedExpression*>(atom_);
            if(par_exp->exp_->containsAggrFunc())
                return true;
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

void GPStore::Expression::print() const{

    if(oprt_ == EMPTY_OP){
        atom_->print();
        if(property_label_ != nullptr){
            property_label_->print();
        }
        return;
    }

    if(oprt_ == OR || oprt_ == XOR || oprt_ == AND ||
    oprt_ == EQUAL || oprt_ == NOT_EQUAL || oprt_ == LESS || oprt_ ==  GREATER || oprt_ == LESS_EQUAL || oprt_ ==  GREATER_EQUAL ||
    oprt_ == IN ||
    oprt_ == STARTS_WITH || oprt_ == ENDS_WITH || oprt_ ==  CONTAINS ||
    oprt_ == ADD || oprt_ == SUB|| oprt_ == MUL || oprt_ == DIV || oprt_ == MOD || oprt_ == POW){
        printf("(");
        children_[0]->print();
        printf(" %s ", oprt2String(oprt_).c_str());
        children_[1]->print();
        printf(")");
    } else if(oprt_ == NOT || oprt_ == IDENTITY || oprt_ == NEGATION){
        printf("(");
        printf(" %s ", oprt2String(oprt_).c_str());
        children_[0]->print();
        printf(")");
    } else if(oprt_ == IS_NULL || oprt_ == IS_NOT_NULL){
        printf("(");
        children_[0]->print();
        printf(" %s ", oprt2String(oprt_).c_str());
        printf(")");
    } else if(oprt_ == INDEX){
        children_[0]->print();
        printf("[");
        children_[1]->print();
        printf("]");
    } else if(oprt_ == SLICE){
        children_[0]->print();
        printf("[");
        children_[1]->print();
        printf("..");
        children_[2]->print();
        printf("]");
    }
    return;
}


/* class AtomPropertyLabels */

GPStore::AtomPropertyLabels::AtomPropertyLabels(){

}

GPStore::AtomPropertyLabels::AtomPropertyLabels(const AtomPropertyLabels &that){
    prop_key_names_ = that.prop_key_names_;
    labels_ = that.labels_;
    prop_ids_ = that.prop_ids_;
}

GPStore::AtomPropertyLabels& 
GPStore::AtomPropertyLabels:: operator=(const GPStore::AtomPropertyLabels &that){
    if(this == &that) return *this;
    prop_key_names_ = that.prop_key_names_;
    labels_ = that.labels_;
    prop_ids_ = that.prop_ids_;
    return *this;
}



void GPStore::AtomPropertyLabels::print()const{

    for(const auto &p : prop_key_names_){
        printf(".%s", p.c_str());
    }

    for(const auto &l : labels_){
        printf(":%s", l.c_str());
    }
}

/* class Atom */

/* class Literal */

GPStore::Literal::Literal(){
    atom_type_ = LITERAL;
    literal_type_ = NULL_LITERAL;
}

GPStore::Literal::Literal(LiteralType lt){
    atom_type_ = LITERAL;
    literal_type_ = lt;
}

GPStore::Literal::Literal(const Literal& that){
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    literal_type_ = that.literal_type_;
    switch (that.literal_type_)
    {
    case BOOLEAN_LITERAL:
        b_ = that.b_;
        break;
    case NULL_LITERAL:
        break;
    case INT_LITERAL:
        i_ = that.i_;
        break;
    case DOUBLE_LITERAL:
        d_ = that.d_;
        break;
    case STRING_LITERAL:
        s_ = that.s_;
        break;
    case LIST_LITERAL:
        for(auto e : that.list_literal_){
            list_literal_.push_back(new Expression(*e));
        }
        break;
    case MAP_LITERAL:
        for(const auto& p: that.map_literal_){
            map_literal_.insert(make_pair(p.first, new Expression(*p.second)));
        }
        break;
    default:
        break;
    }
}

GPStore::Literal::~Literal(){
    for(Expression *e : list_literal_)
        if(e != nullptr)
            delete e;
    for(auto &p : map_literal_)
        if(p.second != nullptr)
            delete p.second;
}

void GPStore::Literal::print() const{
    if(literal_type_ == BOOLEAN_LITERAL){
        printf(b_ ? "true" : "false");
    }else if(literal_type_ == NULL_LITERAL){
        printf("NULL");
    }else if(literal_type_ == INT_LITERAL){
        printf("%lld", i_);
    }else if(literal_type_ == DOUBLE_LITERAL){
        printf("%lf", d_);
    }else if(literal_type_ == STRING_LITERAL){
        printf("%s", s_.c_str());
    }else if(literal_type_ == LIST_LITERAL){
        int n = (int)list_literal_.size();
        printf("[");
        if(n != 0) list_literal_[0]->print();
        for(int i = 1; i < n; ++i){
            printf(", ");
            list_literal_[i]->print();
        }
        printf("]");
    }else if(literal_type_ == MAP_LITERAL){
        printf("{ ");
        if(!map_literal_.empty()){
            auto it = map_literal_.begin();
            printf("%s: ", it->first.c_str());
            it->second->print();
            for(++it; it != map_literal_.end(); ++it){
                printf(", ");
                printf("%s: ", it->first.c_str());
                it->second->print();
            }
        }
        printf(" }");
    }
    // DONE.
}

/* class: Parameter */

GPStore::Parameter::Parameter(){
    atom_type_ = PARAMETER;
}



GPStore::Parameter::Parameter(const Parameter& that){
    this->atom_type_ = that.atom_type_;
    param_name_ = that.param_name_;
    param_num_ = that.param_num_;
}

GPStore::Parameter::~Parameter(){ }


void GPStore::Parameter::print() const{
    std::string s =  std::string("$" ) +  (param_name_.length () != 0 ? param_name_ : std::to_string(param_num_));
    printf("%s",s.c_str());
}

/* class: CaseExpression */

GPStore::CaseExpression::CaseExpression(): test_exp_(nullptr), else_exp_(nullptr) {
    atom_type_ = CASE_EXPRESSION;
}

GPStore::CaseExpression::CaseExpression(CaseType ct): case_type_(ct), test_exp_(nullptr), else_exp_(nullptr) {
    atom_type_ = CASE_EXPRESSION;
}

GPStore::CaseExpression::CaseExpression(const CaseExpression &that):test_exp_(nullptr), else_exp_(nullptr){
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    case_type_ = that.case_type_;
    if(that.case_type_ == SIMPLE){
        test_exp_ = new Expression(*that.test_exp_);
    }
    for(auto e : that.when_exps_){
        when_exps_.push_back(new Expression(*e));
    }
    for(auto e : that.then_exps_){
        then_exps_.push_back(new Expression(*e));
    }
    if(that.else_exp_ != nullptr){
        else_exp_ = new Expression(*that.else_exp_);
    }
}

GPStore::CaseExpression::CaseExpression::~CaseExpression(){
    if(test_exp_ != nullptr)
        delete test_exp_;
    for(Expression *e : when_exps_)
        if(e != nullptr)
            delete e;
    for(Expression *e : then_exps_)
        if(e != nullptr)
            delete e;
    if(else_exp_ != nullptr)
        delete else_exp_;
}



void GPStore::CaseExpression::print() const {
    printf("( CASE ");
    if(case_type_ == SIMPLE){
        test_exp_->print();
        printf(" ");
    }
    for(int i = 0; i < when_exps_.size(); ++i){
        printf(" WHEN ");
        when_exps_[i]->print();
        printf( " THEN ");
        then_exps_[i]->print();
    }
    if(else_exp_ != nullptr){
        printf( " ELSE ");
        else_exp_->print();
    }
    printf(" END )");
}

/* class Count */

GPStore::Count::Count():cnt(0){
    atom_type_ = COUNT;
}   

GPStore::Count::Count(const Count& that){
    cnt = that.cnt;
    atom_type_ = COUNT;
}

GPStore::Count::~Count(){

}


void GPStore::Count::print() const{
    printf("COUNT (*)");
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



void GPStore::ListComprehension::print() const{
    printf("[ %s IN ", var_name_.c_str());
    exp_->print();
    printf(" ");
    if(filter_ != nullptr){
        printf("WHERE ");
        filter_->print();
        printf(" ");
    }
    if(trans_ != nullptr){
        printf("| ");
        trans_->print();
        printf(" ");
    }
    printf("]");
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


void GPStore::PatternComprehension::print()  const {
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


void GPStore::Quantifier::print() const{
    const char *s[4]={
        "ALL", "ANY", "SINGLE", "NONE"
    };
    printf("%s( ", s[(int)quantifier_type_]);
    printf("%s IN ", var_name_.c_str());
    container_->print();
    printf(" ");
    if(exp_ != nullptr){
        printf("WHERE ");
        exp_->print();
        printf(" ");
    }
    printf(")");
}


GPStore::PatternPredicate::PatternPredicate(){
    atom_type_ = PATTERN_PREDICATE;
}

GPStore::PatternPredicate::PatternPredicate(const PatternPredicate& that){
    atom_type_ = PATTERN_PREDICATE;
    this->pattern_.reset(new GPStore::RigidPattern(*that.pattern_));
    this->covered_var_id_ = that.covered_var_id_;
    this->covered_props_ = that.covered_props_;
}   

GPStore::PatternPredicate::~PatternPredicate(){
}


void GPStore::PatternPredicate::print() const {
    pattern_->print();
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

bool GPStore::FunctionInvocation::isAggregationFunction()const{
    if(func_name_.size() != 1) return false;

    std::string str = func_name_[0];
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::vector<std::string> aggr_func{"avg", "collect", "count", "max", "min", "percentilecont", "percentiledisc", "stdev", "stdevp", "sum"};
    
    return (std::find(aggr_func.begin(), aggr_func.end(), str) != aggr_func.end());
}

void GPStore::FunctionInvocation::print() const {
    // Print Head && Function Name

    printf("%s", func_name_[0].c_str());
    for(int i = 1; i < func_name_.size(); ++i)
        printf(".%s", func_name_[i].c_str());
    printf("( ");
    // Distinct
    if(distinct)
        printf("DISTINCT ");
    // Print args
    for(auto e : args){
        e->print();
        printf(", ");
    }
    printf(")");
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

void GPStore::ExistentialSubquery::print()const{
    throw std::runtime_error("[ERROR] Not implemented.");
}

/* class Variable */

GPStore::Variable::Variable(){
    atom_type_ = VARIABLE;
    id_ = ID_NONE;
}


GPStore::Variable::Variable(const Variable& that){
    atom_type_ = that.atom_type_;
    covered_var_id_ = that.covered_var_id_;
    covered_props_ = that.covered_props_;
    var_ = that.var_;
    id_ = that.id_;
}

GPStore::Variable::Variable(const std::string & var_name, unsigned var_id ){
    atom_type_ = VARIABLE;
    var_ = var_name;
    id_ = var_id;
    covered_var_id_.addVar(var_id);
}

GPStore::Variable::~Variable(){

}

void GPStore::Variable::print() const {
    printf("%s", var_.c_str());
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

void GPStore::ParenthesizedExpression::print() const {
    printf("( ");
    exp_->print();
    printf(" )");
}