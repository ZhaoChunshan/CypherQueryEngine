#ifndef PQUERY_PQUERYOPERATOR_H
#define PQUERY_PQUERYOPERATOR_H

#include <vector>
#include <string>
#include <set>

#include "../PParser/Pattern.h"
#include "PVarset.h"

/**
 * @brief class PQueryOperator: node of the PlanTree.
 * @warning Copy construct function and operator = only copy the content of the PQueryOperator; 
 * DONOT copy left, right, parent Pointer.
 * DONOT copy maximal_varset_, minimal_varset_
*/
class PQueryOperator{
public:
    enum OperatorType {
        BGP, FILTER, 
        AND, OPTIONAL, UNION, MINUS,    // 4 binary-operators
        PROJECTION, SHORTEST_PATH,
        ORDER_BY,
        GROUP_BY, AGGREGATION,
        UNWIND,
        // Not implement. 
        HAVING, SCOPE, BIND, TABLE
    };

    enum UnionType { SPARQL_UNION, CYPHER_UNION, CYPHER_UNION_ALL };

    OperatorType type_;
    PQueryOperator *left_, *right_;
    PQueryOperator *parent_;

    /* For optimization, since we may drop some vars that won't be used. */
    PVarset<unsigned> maximal_varset_, minimal_varset_;

    /* only used for BGP */
    std::vector<GPStore::RigidPattern> pattern_;
    PVarset<std::pair<unsigned, unsigned>> edge_conflict_;

    /* only used for operator union */
    UnionType union_ty_;

    /* Mainly used for filter, the var occurs in the exp is string not id
     * exp = f1 AND f2 AND f3 ... AND fn 
     * We can inject Filters to other Node such as BGP , AND */
    std::vector<GPStore::Expression> filters_;

    /* only used for shortestPath */
    bool is_all_shortest_;
    unsigned src_, tgt_, path_var_id_;
    GPStore::EdgePattern edge_pattern_;
    
    /* only used for projection */
    std::vector<GPStore::Expression> proj_exps_;
    std::vector<unsigned> var_id_;

    /* only used for order by */
    std::vector<GPStore::Expression> order_exps_;
    std::vector<bool> ascending_;
    unsigned skip, limit; //default: 0, 0xffffffff
    bool distinct_;       // remove duplicated rows;
    
    /* only used for group by */
    std::vector<unsigned> group_by_key_;

    /* only used for aggregation */
    std::vector<GPStore::Expression> aggr_value_;
    std::vector<unsigned> aggr_value_var_id_;

    /* only used for unwind */
    std::unique_ptr<GPStore::Expression> unwind_;
    unsigned unwind_var_id_;

    PQueryOperator();
    PQueryOperator(OperatorType op_type);
    PQueryOperator(const PQueryOperator& that);
    PQueryOperator& operator=(const PQueryOperator& that);
    
    ~PQueryOperator();

    void print(int dep) const;

    void clipVarset(const PVarset<unsigned> & required);

    static PQueryOperator * mergeBGP(const std::vector<PQueryOperator *>& bgp);

    static PQueryOperator * mergeFilter(const PQueryOperator *filter1, const PQueryOperator *filter2);

    static PQueryOperator * partitionConnectedComponent(PQueryOperator *bgp, PQueryOperator *root, const PQueryOperator *filter = nullptr);

    static std::pair<std::map<unsigned, unsigned> *, unsigned> calculateVarConnectedComponent(const PQueryOperator *bgp);

    static GPStore::Expression * edgeConflictToExpression(unsigned e1, unsigned e2);

    static GPStore::Expression * propertyEqualityToExpression(unsigned var_id, const std::string & prop_name, unsigned prop_id, const GPStore::Expression & prop_val);

    static GPStore::Expression * varIdToExpression(unsigned var_id);

    static void rewriteShortestPathPattern(PQueryOperator *bgp);

    static PQueryOperator * generateRelatedFilters(PQueryOperator *root, std::set<const GPStore::Expression *> & filters);

    static PQueryOperator * generateBinaryOperator(PQueryOperator *left, PQueryOperator *right, PQueryOperator::OperatorType op);

    static PQueryOperator * generateShortestPath(PQueryOperator *root, const GPStore::RigidPattern &pattern);

    static PQueryOperator * generateProjectionVars(PQueryOperator *root, const std::vector<unsigned >& vars);
private:
};

#endif