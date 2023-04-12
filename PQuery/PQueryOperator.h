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

    /* only used for filter, the var occurs in the exp is string not id
     * exp = f1 AND f2 AND f3 ... AND fn */
    std::vector<GPStore::Expression> filters_;

    /* only used for shortestPath */
    bool is_all_shortest_;
    std::string src_, tgt_;
    GPStore::EdgePattern edge_pattern_;

    /* only used for projection */
    std::vector<GPStore::Expression> proj_exps_;
    Varset rename_cols_;

    /* only used for order by */
    Varset sorted_vars_;
    std::vector<OrderType> order_tys_;
    int skip, limit;
    
    PQueryOperator();
    PQueryOperator(const PQueryOperator& that);
    PQueryOperator& operator=(const PQueryOperator& that);
    
    void release();
    ~PQueryOperator();

    void print() const;
};
