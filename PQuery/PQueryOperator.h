#ifndef PQUERY_PQUERYOPERATOR_H
#define PQUERY_PQUERYOPERATOR_H

#include <vector>
#include <string>
#include <set>

#include "../PParser/Pattern.h"
#include "PVarset.h"

class PQueryOperator{
public:
    enum OperatorType {
        BGP, FILTER, 
        AND, OPTIONAL, UNION, MINUS,    // 4 binary-operators
        PROJECTION, SHORTEST_PATH,
        ORDER_BY,
        GROUP_BY, AGGREGATION,
        // Not implement. 
        HAVING,  SCOPE ,BIND, TABEL
    };

    enum UnionType { SPARQL_UNION, CYPHER_UNION, CYPHER_UNION_ALL };

    OperatorType type_;
    PQueryOperator *left_, *right_;
    PQueryOperator *parent_;

    /* For optimization, since we may drop some vars that won't be used. */
    PVarset<unsigned> maximal_varset_, minial_varset_;

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
    unsigned skip, limit;
    
    /* only used for group by && aggregation */
    std::vector<unsigned> group_by_key_;

    /* only used for aggregation */
    std::vector<GPStore::Expression> aggr_value_;
    std::vector<unsigned> aggr_value_var_id_;

    PQueryOperator();
    PQueryOperator(OperatorType op_type);
    PQueryOperator(const PQueryOperator& that);
    PQueryOperator& operator=(const PQueryOperator& that);
    
    ~PQueryOperator();

    void print(int dep) const;
public:
    /**
     * @brief Merge two BGPs and their edge conflict and filters are remained.
     *  */
    static PQueryOperator * mergeBGP(const PQueryOperator *bgp1, const PQueryOperator *bgp2);

    /**
     * @brief Merge two Filters .
     */
    static PQueryOperator * mergeFilter(const PQueryOperator *filter1, const PQueryOperator *filter2);

    /**
     * @brief Partition a BGP to Connected Components: e.g. BGP => BGP1 AND BGP2 AND BGP3.
     * Filters will be done as early as possible.
     * @return Root of the plan tree.
     */
    static PQueryOperator * partitionConnectedComponent(const PQueryOperator *bgp, const PQueryOperator *filter = nullptr);


private:
};

#endif