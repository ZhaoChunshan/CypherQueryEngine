#ifndef PQUERYOPERATOR_H
#define PQUERYOPERATOR_H

#include <vector>
#include <string>
#include <set>

#include "Pattern.h"
#include "Varset.h"

class PQueryOperator{
public:
    enum OperatorType {
        BGP, AND, OPTIONAL, UNION, MINUS,
        FILTER, SHORTEST_PATH,
        PROJECTION, ORDER_BY,
        // Not implement. 
        GROUP_BY, HAVING, AGGREGATION, SCOPE ,BIND, TABEL,
    };

    enum UnionType { SPARQL_UNION, CYPHER_UNION, CYPHER_UNION_ALL };
    enum OrderType { ASC, DSC };

    OperatorType type_;
    PQueryOperator *left_, *right_;
    PQueryOperator *parent_;

    /* For optimization, since we may drop some vars that won't be used. */
    Varset maximal_varset_, minial_varset_;

    /* only used for BGP node */
    std::vector<GPStore::RigidPattern> pattern_;
    std::set<std::pair<unsigned, unsigned>> edge_conflict_;

    /* only used for operator union */
    UnionType union_ty_;

    /* Mainly used for filter, the var occurs in the exp is string not id
     * exp = f1 AND f2 AND f3 ... AND fn 
     * We can inject Filters to other Node such as BGP , AND */
    std::vector<GPStore::Expression> filters_;

    /* only used for shortestPath */
    bool is_all_shortest_;
    std::string src_, tgt_, path_name_;
    GPStore::EdgePattern edge_pattern_;

    /* only used for projection */
    std::vector<GPStore::Expression> proj_exps_;
    std::vector<std::string> var_name_;

    /* only used for order by */
    std::vector<GPStore::Expression> order_exps_;
    std::vector<OrderType> order_tys_;
    int skip, limit;
    
    PQueryOperator();
    PQueryOperator(OperatorType op_type);
    PQueryOperator(const PQueryOperator& that);
    PQueryOperator& operator=(const PQueryOperator& that);
    
    void release();
    ~PQueryOperator();

    void print(int dep) const;
public:
    /* Merge two BGP and their edge conflict and filters are remained. */
    static PQueryOperator * mergeBGP(const PQueryOperator &bgp1, const PQueryOperator &bgp2);

    /* Partition a BGP to Connected Component: e.g. BGP = BGP1 AND BGP2 AND BGP3*/
    static PQueryOperator * partitionConnectedComponent(const PQueryOperator &bgp);

private:
};

#endif