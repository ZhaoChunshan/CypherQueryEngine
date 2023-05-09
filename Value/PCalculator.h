#ifndef VALUE_PCALCULATOR_H
#define VALUE_PCALCULATOR_H

#include "Value.h"
#include "Expression.h"

// We should use PStore later then
typedef void PStore;

class PCalculator{
public:

    /* For Executor, fit PIntermediateResult */
    static GPStore::Value
    evaluateExpression(
            const GPStore::Expression *exp,
            const std::vector<unsigned> & spo_vars,
            const std::map<unsigned, unsigned> & var_id2col,
            const std::vector<unsigned long long> & edge_vars,
            const std::map<unsigned, unsigned> & edge_id2col,
            const std::vector<GPStore::Value> & value_vars,
            const std::map<unsigned, unsigned> & value_id2col,
            const std::map<std::pair<unsigned ,unsigned >, unsigned > var_prop_id2col,
            const PStore * pStore
            );

    /* For Filters on PTempResult */
    static GPStore::Value
    evaluateExpression(
            const GPStore::Expression *exp,
            const std::vector<unsigned > & spo_vars,// colmn 0 ~ n - 1
            const std::vector<unsigned long long> & edge_vars,// colmn n ~ m + n - 1
            const std::vector<GPStore::Value> values,// column n + m ~ m + n + v  - 1
            const std::map<unsigned, unsigned> & var_id2col,
            const std::map<std::pair<unsigned,unsigned >, unsigned > var_propid2col,
            const PStore * pStore
            );
};




#endif VALUE_PCALCULATOR_H
