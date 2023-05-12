#include <algorithm>
#include <cstdlib>
#include "PCalculator.h"

GPStore::Value
PCalculator::evaluateExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    if(exp == nullptr) {
        return GPStore::Value::ERROR_VALUE;
    }
    if(exp->isAtom()){
        return evaluateAtomExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                      value_embeddings, value_id2col, var_prop_id2col, params, pStore );
    }
    switch (exp->oprt_) {
        case GPStore::Expression::OR:
        case GPStore::Expression::XOR:
        case GPStore::Expression::AND:
            return evaluateBinaryLogicalExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                                   value_embeddings, value_id2col, var_prop_id2col, params, pStore );
        case GPStore::Expression::NOT:
            return evaluateNotExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                         value_embeddings, value_id2col, var_prop_id2col, params, pStore );
        case GPStore::Expression::EQUAL:
        case GPStore::Expression::NOT_EQUAL:
        case GPStore::Expression::LESS:
        case GPStore::Expression::GREATER:
        case GPStore::Expression::LESS_EQUAL:
        case GPStore::Expression::GREATER_EQUAL:
            return evaluateBinaryCompareExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                         value_embeddings, value_id2col, var_prop_id2col, params, pStore );

        case GPStore::Expression::IN:
            return evaluateInExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                                   value_embeddings, value_id2col, var_prop_id2col, params, pStore );

        case GPStore::Expression::STARTS_WITH:
        case GPStore::Expression::ENDS_WITH:
        case GPStore::Expression::CONTAINS:
            return evaluateStringExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                        value_embeddings, value_id2col, var_prop_id2col, params, pStore );

        case GPStore::Expression::IS_NULL:
        case GPStore::Expression::IS_NOT_NULL:
            return evaluateIsNullExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                            value_embeddings, value_id2col, var_prop_id2col, params, pStore );

        case GPStore::Expression::ADD:
        case GPStore::Expression::SUB:
        case GPStore::Expression::MUL:
        case GPStore::Expression::DIV:
        case GPStore::Expression::MOD:
        case GPStore::Expression::POW:
            return evaluateBinaryArithmeticExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                            value_embeddings, value_id2col, var_prop_id2col, params, pStore );

        case GPStore::Expression::IDENTITY:
        case GPStore::Expression::NEGATION:
            return evaluateUnaryAddMinusExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                                      value_embeddings, value_id2col, var_prop_id2col, params, pStore );

        case GPStore::Expression::INDEX:
        case GPStore::Expression::SLICE:
            return evaluateIndexSliceExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                                   value_embeddings, value_id2col, var_prop_id2col, params, pStore );

    }
    return GPStore::Value(GPStore::Value::ERROR_VALUE);
}

/**
 * @brief evaluate a const expression.No Variable, No Node Edge, No PropertyLabel, No param
 * */
GPStore::Value
PCalculator::evaluateConstExpression(const GPStore::Expression *exp){
    std::vector<unsigned > empty_spo;
    std::map<unsigned ,unsigned >empty_col;
    std::vector<unsigned long long > empty_edge;
    std::vector<GPStore::Value > empty_val;
    std::map<std::pair<unsigned ,unsigned >,unsigned > empty_var_prop2col;
    std::unordered_map<std::string, GPStore::Value> empty_param;
    return evaluateExpression(exp, empty_spo, empty_col, empty_edge, empty_col, empty_val,
                              empty_col, empty_var_prop2col,empty_param, nullptr);
}

GPStore::Value
PCalculator::evaluateBinaryLogicalExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    std::vector<GPStore::Value> values;
    for(const auto child : exp->children_){
        values.emplace_back(
                evaluateExpression(exp, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                                   value_id2col, var_prop_id2col, params, pStore)
                );
        auto ty = values.back().type_;
        if(ty != GPStore::Value::NO_VALUE && ty != GPStore::Value::BOOLEAN)
            return GPStore::Value(GPStore::Value::ERROR_VALUE);
    }
    GPStore::Value res = values[0];
    for(int i = 1; i < (int)values.size(); ++i){
        if(exp->oprt_ == GPStore::Expression::AND){
            res = logicalAnd(res, values[i]);
        } else if(exp->oprt_ == GPStore::Expression::OR){
            res = logicalOr(res, values[i]);
        } else if(exp->oprt_ == GPStore::Expression::XOR){
            res = logicalXor(res, values[i]);
        }
    }
    return res;
}

GPStore::Value
PCalculator::evaluateNotExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    auto v = evaluateExpression(exp->children_[0], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    if(!v.isNull() && v.getType() != GPStore::Value::BOOLEAN)
        return GPStore::Value(GPStore::Value::ERROR_VALUE);
    return logicalNot(v);
}

GPStore::Value
PCalculator::evaluateBinaryCompareExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    GPStore::Value x = evaluateExpression(exp->children_[0], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                          value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    GPStore::Value y = evaluateExpression(exp->children_[1], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,
                                          value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    GPStore::Value no_value(GPStore::Value::NO_VALUE);
    GPStore::Value true_value(true), false_value(false);

    if(x.isErrorValue() || y.isErrorValue())
        return GPStore::Value(GPStore::Value::ERROR_VALUE);

    if(x.isNull() || y.isNull()) return no_value;

    if(x.isNumber() ){
        if(!y.isNumber())  return no_value;
    } else if(x.type_ != y.type_) return no_value;
    int comp = compValue(x, y);
    switch (exp->oprt_) {
        case GPStore::Expression::EQUAL:
            return comp == 0 ? true_value : false_value;
        case GPStore::Expression::NOT_EQUAL:
            return comp == 0 ? false_value : true_value;
        case GPStore::Expression::GREATER:
            return comp > 0 ? true_value : false_value;
        case GPStore::Expression::LESS:
            return comp < 0 ? true_value : false_value;
        case GPStore::Expression::GREATER_EQUAL:
            return comp >= 0 ? true_value : false_value;
        case GPStore::Expression::LESS_EQUAL:
            return comp <= 0 ? true_value : false_value;
    }
    return GPStore::Value(GPStore::Value::ERROR_VALUE);
}

GPStore::Value
PCalculator::evaluateInExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    GPStore::Value x = evaluateExpression(exp->children_[0],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    GPStore::Value y = evaluateExpression(exp->children_[1],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    if(x.isErrorValue() || y.isErrorValue()) return GPStore::Value(GPStore::Value::ERROR_VALUE);

    if(x.isNull() || y.isNull()) return GPStore::Value(GPStore::Value::NO_VALUE);

    if(y.type_ != GPStore::Value::LIST) return GPStore::Value(GPStore::Value::ERROR_VALUE);

    int n = y.data_.List->size();
    for(int i = 0; i < n; ++i){
        if(x == *(y.data_.List->at(i)))
            return true;
    }
    return false;
}

GPStore::Value
PCalculator::evaluateStringExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    GPStore::Value x = evaluateExpression(exp->children_[0],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    GPStore::Value y = evaluateExpression(exp->children_[1],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);

    if(x.isErrorValue() || y.isErrorValue()) return GPStore::Value(GPStore::Value::ERROR_VALUE);
    if(x.isNull() || y.isNull()) return GPStore::Value(GPStore::Value::NO_VALUE);
    if(x.type_ != GPStore::Value::STRING || y.type_ != GPStore::Value::STRING)
        return GPStore::Value(GPStore::Value::ERROR_VALUE);
    const std::string & s1 = *x.data_.String;
    const std::string & s2 = *y.data_.String;
    int m = (int)s1.size(), n = (int)s2.size();
    if(m < n) return false;
    if(exp->oprt_ == GPStore::Expression::STARTS_WITH){
        for(int i = 0; i < n; ++i){
            if(s1[i] != s2[i])
                return false;
        }
        return true;
    } else if(exp->oprt_ == GPStore::Expression::ENDS_WITH){
        for(int i = 0; i < n; ++i){
            if(s2[n - 1 - i] != s1[m - 1 - i])
                return false;
        }
        return true;
    } else if(exp->oprt_ == GPStore::Expression::CONTAINS){
        if(n == 0) return true;
        // we know m >= n > 0
        for(int i = 0; i < m - n + 1; ++i){
            if(s1.substr(i, n) == s2)
                return true;
        }
        return false;
    }
    return GPStore::Value(GPStore::Value::ERROR_VALUE);
}

GPStore::Value
PCalculator::evaluateIsNullExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    GPStore::Value x = evaluateExpression(exp->children_[0],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);

    if(x.isErrorValue()) return GPStore::Value(GPStore::Value::ERROR_VALUE);
    return exp->oprt_ == GPStore::Expression::IS_NULL ? x.isNull() : !x.isNull();
}

GPStore::Value
PCalculator::evaluateBinaryArithmeticExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    GPStore::Value x = evaluateExpression(exp->children_[0],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    GPStore::Value y = evaluateExpression(exp->children_[1],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);

    if(x.isErrorValue() || y.isErrorValue()) return GPStore::Value(GPStore::Value::ERROR_VALUE);

    if(x.isNull() || y.isNull()) return GPStore::Value(GPStore::Value::NO_VALUE);

    if(!x.isNumber() || !y.isNumber()) return GPStore::Value(GPStore::Value::ERROR_VALUE);

    return arithmeticOperator(x, y, exp->oprt_);
}

GPStore::Value
PCalculator::evaluateUnaryAddMinusExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    GPStore::Value x = evaluateExpression(exp->children_[0],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);

    if(x.isErrorValue() || !x.isNumber()) return GPStore::Value(GPStore::Value::ERROR_VALUE);
    if(exp->oprt_ == GPStore::Expression::IDENTITY) return x;

    if(x.type_ == GPStore::Value::INTEGER)
        x.data_.Int = -x.data_.Int;
    else
        x.data_.Float = -x.data_.Float;
    return x;
}

GPStore::Value
PCalculator::evaluateIndexSliceExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    GPStore::Value x = evaluateExpression(exp->children_[0],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    GPStore::Value y = evaluateExpression(exp->children_[1],  spo_embeddings, spo_id2col, edge_embeddings,
                                          edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
    GPStore::Value z;
    if(x.isErrorValue() || y.isErrorValue()) return GPStore::Value(GPStore::Value::ERROR_VALUE);
    if(x.isNull() || y.isNull()) return GPStore::Value(GPStore::Value::NO_VALUE);
    if(x.type_ != GPStore::Value::LIST && x.type_ != GPStore::Value::MAP)
        return GPStore::Value(GPStore::Value::ERROR_VALUE);

    if(exp->oprt_ == GPStore::Expression::INDEX){
        if(x.type_ == GPStore::Value::LIST){
            if(y.type_ != GPStore::Value::INTEGER) return GPStore::Value(GPStore::Value::ERROR_VALUE);

            long long n = (long long) x.data_.List->size(), idx = y.data_.Int < 0 ? n + y.data_.Int : y.data_.Int;
            if(idx < 0 || idx >= n) return GPStore::Value(GPStore::Value::NO_VALUE);
            return *(x.data_.List->at(idx));
        } else {
            if(y.type_ != GPStore::Value::STRING) return GPStore::Value(GPStore::Value::ERROR_VALUE);
            auto it = x.data_.Map->find(*y.data_.String);
            if(it == x.data_.Map->end()) return GPStore::Value(GPStore::Value::NO_VALUE);
            return *(it->second);
        }
    } else {    // SLICE
        z = evaluateExpression(exp->children_[2],  spo_embeddings, spo_id2col, edge_embeddings,
                               edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
        if(z.isErrorValue() || z.isNull()) return z;
        if(x.type_ != GPStore::Value::LIST || y.type_ != GPStore::Value::INTEGER || z.type_ != GPStore::Value::INTEGER)
            return GPStore::Value(GPStore::Value::ERROR_VALUE);

        GPStore::Value ls(GPStore::Value::LIST);

        long long n = (long long) x.data_.List->size();
        long long idx1 = y.data_.Int < 0 ? n + y.data_.Int : y.data_.Int;
        long long idx2 = z.data_.Int < 0 ? n + z.data_.Int : z.data_.Int;

        if(idx1 >= idx2 || idx2 <= 0 || idx1 >= n) return ls;
        // then idx1 < idx2; idx2 > 0 && idx1 < n
        idx1 = idx1 < 0 ? 0 : idx1;
        idx2 = idx2 <= n ? idx2 : n;
        for(int i = idx1; i < idx2; ++i){
            ls.append(*x.data_.List->at(i));
        }

        return ls;
    }
}

GPStore::Value PCalculator::evaluateAtomExpression(
        const GPStore::Expression *exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    auto val = evaluateAtom(exp->atom_, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                            value_id2col, var_prop_id2col, params, pStore);
    if(val.isErrorValue() || val.isNull()) return val;
    if(exp->property_label_ == nullptr)
        return val;
    if(!exp->property_label_->key_names_.empty()){
        return evaluatePropertyOrMapKey(val, exp->property_label_->key_names_, pStore);
    } else if(!exp->property_label_->node_labels_.empty()){
        // a:Person:Student
        // TODO:we should check the existence of those labels.
        // call KVStore here
        return std::rand()% 2 == 0 ? true : false;
    } else {
        return val;
    }
}

GPStore::Value
PCalculator::evaluateAtom(
        const GPStore::Atom *atom,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    switch (atom->atom_type_) {
        case GPStore::Atom::LITERAL:
            return evaluateLiteral(dynamic_cast<const GPStore::Literal *>(atom),spo_embeddings, spo_id2col,edge_embeddings,
                                   edge_id2col,value_embeddings,value_id2col,var_prop_id2col,params,pStore);

        case GPStore::Atom::PARAMETER:
            return evaluateParameter(dynamic_cast<const GPStore::Parameter *>(atom), params);

        case GPStore::Atom::VARIABLE:
            return evaluateVariable(dynamic_cast<const GPStore::Variable *>(atom), spo_embeddings, spo_id2col,
                                    edge_embeddings, edge_id2col, value_embeddings, value_id2col);
        case GPStore::Atom::PARENTHESIZED_EXPRESSION:
            return evaluateParenthesizedExpression(dynamic_cast<const GPStore::ParenthesizedExpression*>(atom),
                   spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings, value_id2col,
                   var_prop_id2col, params, pStore);
        case GPStore::Atom::FUNCTION_INVOCATION:
            return evaluateFunctionInvocation(dynamic_cast<const GPStore::FunctionInvocation*>(atom), spo_embeddings,
                                              spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                                              value_id2col, var_prop_id2col, params, pStore);

        case GPStore::Atom::CASE_EXPRESSION:
            return evaluateCaseExpression(dynamic_cast<const GPStore::CaseExpression*>(atom), spo_embeddings, spo_id2col,
                                          edge_embeddings, edge_id2col, value_embeddings , value_id2col, var_prop_id2col,
                                          params, pStore);
        case GPStore::Atom::COUNT:
            std::cerr << "[ERROR] Aggr COUNT(*): Control Flow should never reach here." << std::endl;
            return GPStore::Value::ERROR_VALUE;
        case GPStore::Atom::PATTERN_PREDICATE:
        case GPStore::Atom::LIST_COMPREHENSION:
        case GPStore::Atom::PATTERN_COMPREHENSION:
        case GPStore::Atom::QUANTIFIER:
        case GPStore::Atom::EXISTENTIAL_SUBQUERY:
            std::cerr << "[ERROR] We dont support this expression." << std::endl;
    }
    return GPStore::Value::ERROR_VALUE;
}

GPStore::Value
PCalculator::evaluateLiteral( const GPStore::Literal *literal,
            const std::vector<unsigned> & spo_embeddings,
            const std::map<unsigned, unsigned> & spo_id2col,
            const std::vector<unsigned long long> & edge_embeddings,
            const std::map<unsigned, unsigned> & edge_id2col,
            const std::vector<GPStore::Value> & value_embeddings,
            const std::map<unsigned, unsigned> & value_id2col,
            const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
            const std::unordered_map<std::string, GPStore::Value> & params,
            const PStore * pStore)
{
    auto ty = literal->literal_type;
    if(ty == GPStore::Literal::BOOLEAN_LITERAL){
        return literal->b;
    }else if(ty == GPStore::Literal::NULL_LITERAL){
        return GPStore::Value::NO_VALUE;
    }else if(ty == GPStore::Literal::INT_LITERAL){
        return literal->i;
    }else if(ty == GPStore::Literal::DOUBLE_LITERAL){
        return literal->d;
    }else if(ty == GPStore::Literal::STRING_LITERAL){
        return literal->s;
    }else if(ty == GPStore::Literal::LIST_LITERAL){
        GPStore::Value ls(GPStore::Value::LIST);
        for(auto & e : literal->list_literal){
            ls.append(evaluateExpression(e, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col,value_embeddings,
                                         value_id2col, var_prop_id2col, params, pStore));
        }
        return ls;
    }else if(ty == GPStore::Literal::MAP_LITERAL){
        GPStore::Value map_value(GPStore::Value::MAP);
        for(auto &p : literal->map_literal){
            map_value.insert(p.first, evaluateExpression(p.second, spo_embeddings, spo_id2col,edge_embeddings,edge_id2col,
                                                         value_embeddings,value_id2col,var_prop_id2col,params,pStore));
        }
        return map_value;
    }
    return GPStore::Value::ERROR_VALUE;
}

GPStore::Value
PCalculator::evaluateParameter( const GPStore::Parameter * p, const std::unordered_map<std::string, GPStore::Value> & params)
{
    if(!p->symbolic_name.empty()){
        auto it = params.find(p->symbolic_name);
        if(it == params.end()){
            return GPStore::Value::ERROR_VALUE;
        } else {
            return it->second;
        }
    } else {
        std::cerr << "[ERROR] We dont support $DecimalInteger in this version." << std::endl;
    }
    return GPStore::Value::ERROR_VALUE;
}

GPStore::Value PCalculator::evaluateVariable(
        const GPStore::Variable *var,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col
){
    unsigned  var_id = var->id_;
    GPStore::Value ret;
    if(spo_id2col.find(var_id) != spo_id2col.end()){
        ret.type_ = GPStore::Value::NODE;
        ret.data_.Node = spo_embeddings[spo_id2col.at(var_id)];
    } else if(edge_id2col.find(var_id) != edge_id2col.end()){
        ret.type_ = GPStore::Value::EDGE;
        ret.data_.Edge = edge_embeddings[edge_id2col.at(var_id)];
    } else if(value_id2col.find(var_id) != value_id2col.end()){
        return value_embeddings[value_id2col.at(var_id)];
    } else {
        return GPStore::Value::ERROR_VALUE; // unbinding var!
    }
    return ret;
}

GPStore::Value PCalculator::evaluateParenthesizedExpression(
        const GPStore::ParenthesizedExpression *par_exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    return evaluateExpression(par_exp->exp_, spo_embeddings, spo_id2col, edge_embeddings,edge_id2col,value_embeddings,
                              value_id2col, var_prop_id2col, params, pStore);
}

/**
 * @brief Evaluate a function invocation expression. Regular function only, we dont deal with aggregation function here.
 * In this version, we support those most frequently used functions.
 * */
GPStore::Value
PCalculator::evaluateFunctionInvocation(
        const GPStore::FunctionInvocation *func,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    int n = (int)func->func_name_.size();
    if(n != 1) {
        std::cerr << "[ERROR] We dont support user-defined function in this version." << std::endl;
        return GPStore::Value::ERROR_VALUE;
    }
    std::string func_name = func->func_name_[0];
    std::transform(func_name.begin(), func_name.end(), func_name.begin(), ::tolower);
    GPStore::Value v;

    if(func_name == "coalesce"){
        for(auto & arg : func->args){
            v = evaluateExpression(arg, spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                                   value_id2col, var_prop_id2col, params, pStore);
            if(v.isErrorValue()) return v;
            if(v.isNull()) continue;
            return v;
        }
        return GPStore::Value::NO_VALUE;
    }
    else if(func_name == "tointeger"){
        if(func->args.size() != 1) return GPStore::Value::ERROR_VALUE;

        v = evaluateExpression(func->args[0], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                               value_id2col, var_prop_id2col, params, pStore);
        if(v.isErrorValue() || v.isNull()) return v;

        if(!v.isNumber() && v.type_ != GPStore::Value::BOOLEAN &&  v.type_ != GPStore::Value::STRING){
            return GPStore::Value::ERROR_VALUE;
        }

        return toInteger(v);
    } else if(func_name == "tofloat"){
        if(func->args.size() != 1) return GPStore::Value::ERROR_VALUE;

        v = evaluateExpression(func->args[0], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                               value_id2col, var_prop_id2col, params, pStore);
        if(v.isErrorValue() || v.isNull()) return v;

        if(!v.isNumber() && v.type_ != GPStore::Value::STRING){
            return GPStore::Value::ERROR_VALUE;
        }

        return toFloat(v);
    } else if(func_name == "floor"){
        if(func->args.size() != 1) return GPStore::Value::ERROR_VALUE;

        v = evaluateExpression(func->args[0], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                               value_id2col, var_prop_id2col, params, pStore);
        if(v.isErrorValue() || v.isNull()) return v;

        if(!v.isNumber() ){
            return GPStore::Value::ERROR_VALUE;
        }

        return floor(v);
    } else if(func_name == "head"){
        if(func->args.size() != 1) return GPStore::Value::ERROR_VALUE;

        v = evaluateExpression(func->args[0], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                               value_id2col, var_prop_id2col, params, pStore);
        if(v.isNull()) return v;
        if(v.type_ != GPStore::Value::LIST) return GPStore::Value::ERROR_VALUE;

        if(v.data_.List->empty()){
            return GPStore::Value::NO_VALUE;
        } else {
            return *(v.data_.List->at(0));
        }
    } else if(func_name == "size"){
        if(func->args.size() != 1) return GPStore::Value::ERROR_VALUE;

        v = evaluateExpression(func->args[0], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                               value_id2col, var_prop_id2col, params, pStore);
        if(v.isNull()) return v;
        if(v.type_ != GPStore::Value::LIST) return GPStore::Value::ERROR_VALUE;

        GPStore::Value ret(GPStore::Value::INTEGER);
        ret.data_.Int = v.data_.List->size();
        return ret;
    } else if(func_name == "length"){
        if(func->args.size() != 1) return GPStore::Value::ERROR_VALUE;

        v = evaluateExpression(func->args[0], spo_embeddings, spo_id2col, edge_embeddings, edge_id2col, value_embeddings,
                               value_id2col, var_prop_id2col, params, pStore);
        if(v.isNull()) return v;
        if(v.type_ != GPStore::Value::PATH) return GPStore::Value::ERROR_VALUE;

        GPStore::Value ret(GPStore::Value::INTEGER);
        ret.data_.Int = v.data_.Path->edge_id_.size();
        return ret;
    }
    return GPStore::Value::ERROR_VALUE;
}


GPStore::Value
PCalculator::evaluateCaseExpression(
        const GPStore::CaseExpression *case_exp,
        const std::vector<unsigned> & spo_embeddings,
        const std::map<unsigned, unsigned> & spo_id2col,
        const std::vector<unsigned long long> & edge_embeddings,
        const std::map<unsigned, unsigned> & edge_id2col,
        const std::vector<GPStore::Value> & value_embeddings,
        const std::map<unsigned, unsigned> & value_id2col,
        const std::map<std::pair<unsigned ,unsigned >, unsigned > & var_prop_id2col,
        const std::unordered_map<std::string, GPStore::Value> & params,
        const PStore * pStore
){
    if(case_exp->case_type == GPStore::CaseExpression::SIMPLE){
        GPStore::Value val = evaluateExpression(case_exp->test_expr, spo_embeddings, spo_id2col, edge_embeddings,
                                                edge_id2col, value_embeddings, value_id2col, var_prop_id2col,
                                                params, pStore);
        if(val.isErrorValue()) return val;
        int n = case_exp->when_exprs.size();
        for(int i = 0; i < n; ++i){
            auto v1 = evaluateExpression(case_exp->when_exprs[i], spo_embeddings, spo_id2col, edge_embeddings,
                                         edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);

            if(v1.isErrorValue()) return v1;
            if(!valueEquality(val, v1))
                continue;

            return evaluateExpression(case_exp->then_exprs[i], spo_embeddings, spo_id2col, edge_embeddings,
                                         edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
        }
    } else {
        int n = case_exp->when_exprs.size();
        for(int i = 0; i < n; ++i){
            auto v1 = evaluateExpression(case_exp->when_exprs[i], spo_embeddings, spo_id2col, edge_embeddings,
                                         edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);

            if(v1.isErrorValue()) return v1;
            if(v1.type_ != GPStore::Value::BOOLEAN || !v1.data_.Boolean)
                continue;

            return evaluateExpression(case_exp->then_exprs[i], spo_embeddings, spo_id2col, edge_embeddings,
                                      edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);
        }
    }
    if(case_exp->else_expr != nullptr)
        return evaluateExpression(case_exp->else_expr, spo_embeddings, spo_id2col, edge_embeddings,
                                  edge_id2col, value_embeddings, value_id2col, var_prop_id2col, params, pStore);

    return GPStore::Value::NO_VALUE;

}



/**
 * @brief resolve a (node/edge, property key) pair to a property value; Or a (map, mapkey) pair to a mapped value.
 * @param x GPStore::Value, of type Node, Edge, or Map.
 * @param keynames property name list(e.g. m.message.id)
 * @param pStore
 * */
GPStore::Value
PCalculator::evaluatePropertyOrMapKey(const GPStore::Value & x, const std::vector<std::string> & keynames,
                                      const PStore * pStore){
    /// TODO: Call Storage Engine to implement this function.
    const GPStore::Value * val = &x;
    std::unique_ptr<GPStore::Value> v;  // for dynamic alloc
    for(const auto & k : keynames){
        if(val->type_ == GPStore::Value::MAP){
            auto it = val->data_.Map->find(k);
            if(it == val->data_.Map->end()) return GPStore::Value::NO_VALUE;
            val = it->second;
        } else {
            unsigned key_id = (unsigned ) rand()% 10000; // todo: Call pStore here.
            if(key_id == 0xffffffffU) return GPStore::Value::NO_VALUE;
            if(val->type_ == GPStore::Value::NODE){
                unsigned  nid = val->data_.Node;
                v.reset(new GPStore::Value);    // todo:Call pStore here.
                val = v.get();
            } else if(val->type_ == GPStore::Value::EDGE){
                unsigned  eid = val->data_.Edge;
                v.reset(new GPStore::Value);    // todo:Call pStore here.
                val = v.get();
            } else {
                return  GPStore::Value::ERROR_VALUE;
            }
        }
    }

    return *val;
}


GPStore::Value
PCalculator::logicalAnd(const GPStore::Value & x, const GPStore::Value & y){
    if(x.isNull()){
        if(!y.isNull() && !y.data_.Boolean) return GPStore::Value(false);
        return GPStore::Value(GPStore::Value::NO_VALUE);
    } else if(x.data_.Boolean){
        return y;
    } else{
        return GPStore::Value(false);
    }
}

GPStore::Value
PCalculator::logicalOr(const GPStore::Value & x, const GPStore::Value & y){
    if(x.isNull()){
        if(!y.isNull() && y.data_.Boolean)  return GPStore::Value(true);
        return GPStore::Value(GPStore::Value::NO_VALUE);
    } else if(x.data_.Boolean){
        return GPStore::Value(true);
    } else {
        return y;
    }
}

GPStore::Value
PCalculator::logicalXor(const GPStore::Value & x, const GPStore::Value & y){
    if(x.isNull()){
        return GPStore::Value(GPStore::Value::NO_VALUE);
    } else if(x.data_.Boolean){
        return y.isNull() ? GPStore::Value(GPStore::Value::NO_VALUE)
            : GPStore::Value(!y.data_.Boolean);
    } else {
        return y;
    }
}

GPStore::Value
PCalculator::logicalNot(const GPStore::Value & x){
    return x.isNull() ? GPStore::Value(GPStore::Value::NO_VALUE)
        : GPStore::Value(!x.data_.Boolean);
}

GPStore::Value
PCalculator::arithmeticOperator(const GPStore::Value &x, const GPStore::Value &y, GPStore::Expression::OperatorType op){
    GPStore::Value ret(GPStore::Value::FLOAT);
    switch (op) {
        case GPStore::Expression::POW:
            if(x.type_ == GPStore::Value::INTEGER){
                if(y.type_ == GPStore::Value::INTEGER){
                    ret.data_.Float = pow((double)x.data_.Int, (double)y.data_.Int);
                } else {
                    ret.data_.Float = pow((double)x.data_.Int, y.data_.Float);
                }
            } else {
                ret.data_.Float = pow(x.data_.Float, y.type_ == GPStore::Value::INTEGER ?
                                        (double)y.data_.Int :  y.data_.Float);
            }
            break;
        case GPStore::Expression::ADD:
        case GPStore::Expression::SUB:
        case GPStore::Expression::MUL:
        case GPStore::Expression::DIV:
        case GPStore::Expression::MOD:
            if(x.type_ == GPStore::Value::INTEGER){
                if(y.type_ == GPStore::Value::INTEGER){
                    ret.type_ = GPStore::Value::INTEGER;
                    ret.data_.Int = intArithOperator(x.data_.Int, y.data_.Int, op);
                } else {
                    ret.data_.Float = doubleArithOperator((double)x.data_.Int, y.data_.Float, op);
                }
            } else {
                if(y.type_ == GPStore::Value::INTEGER){
                    ret.data_.Float = doubleArithOperator(x.data_.Float, (double)y.data_.Int, op);
                } else {
                    ret.data_.Float = doubleArithOperator(x.data_.Float, y.data_.Float, op);
                }
            }
            break;
    }
    return ret;
}

GPStore::Value PCalculator::toInteger(const GPStore::Value & x){
    GPStore::Value v(GPStore::Value::INTEGER);
    if(x.type_ == GPStore::Value::INTEGER){
        v.data_.Int = x.data_.Int;
    } else if(x.type_ == GPStore::Value::FLOAT) {
        v.data_.Int = (long long )x.data_.Float;
    } else if(x.type_ == GPStore::Value::BOOLEAN){
        v.data_.Int = x.data_.Boolean ? 1 : 0;
    } else if(x.type_ == GPStore::Value::STRING){
        v.data_.Int = std::atoll(x.data_.String->c_str());
    } else {
        return GPStore::Value::ERROR_VALUE;
    }
    return v;
}

GPStore::Value PCalculator::toFloat(const GPStore::Value & x){
    GPStore::Value v(GPStore::Value::FLOAT);
    if(x.type_ == GPStore::Value::INTEGER){
        v.data_.Float = (double) x.data_.Int;
    } else if(x.type_ == GPStore::Value::FLOAT) {
        v.data_.Float = x.data_.Float;
    } else if(x.type_ == GPStore::Value::STRING){
        v.data_.Float = std::stod(x.data_.String->c_str());
    } else {
        return GPStore::Value::ERROR_VALUE;
    }
}

GPStore::Value PCalculator::floor(const GPStore::Value & x){
    GPStore::Value v(GPStore::Value::FLOAT);
    if(x.type_ == GPStore::Value::INTEGER){
        v.data_.Float = (double) x.data_.Int;
    } else if(x.type_ == GPStore::Value::FLOAT){
        v.data_.Float = std::floor(x.data_.Float);
    } else {
        return GPStore::Value::ERROR_VALUE;
    }
    return v;
}

/**
     * @brief Support add, sub, mul, div, mod of two number
     * @param x one operand
     * @param y another operand
     * @warning The function don't support pow
     * */
long long PCalculator::intArithOperator(long long x,long long y, GPStore::Expression::OperatorType op){
    switch (op) {
        case GPStore::Expression::ADD:
            return x + y;
        case GPStore::Expression::SUB:
            return x - y;
        case GPStore::Expression::MUL:
            return x * y;
        case GPStore::Expression::DIV:
            return x / y;
        case GPStore::Expression::MOD:
            return x % y;
    }
    return 0xffffffffffffffffULL;
}

/**
 * @brief Support add, sub, mul, div, mod of two number
 * @param x one operand
 * @param y another operand
 * @warning The function don't support pow, please use <math.h>, pow
 * */
double PCalculator::doubleArithOperator(double x, double y, GPStore::Expression::OperatorType op){
    switch (op) {
        case GPStore::Expression::ADD:
            return (double)x + (double)y;
        case GPStore::Expression::SUB:
            return (double)x - (double)y;
        case GPStore::Expression::MUL:
            return (double)x * (double)y;
        case GPStore::Expression::DIV:
            return (double)x / (double)y;
        case GPStore::Expression::MOD:
            return fmod((double)x, (double)y);
    }
    return NAN;
}


//GPStore::Value
//PCalculator::listCat(GPStore::Value &x, GPStore::Value &y);

int
PCalculator::compValue(const GPStore::Value &x, const GPStore::Value &y){
    return x.comp(y);
}

bool PCalculator::valueEquality(const GPStore::Value &x, const GPStore::Value &y){
    if(x.isErrorValue() || y.isErrorValue()) return false;
    if(x.isNull() || y.isNull()) return false;
    return x.comp(y) == 0;
}
