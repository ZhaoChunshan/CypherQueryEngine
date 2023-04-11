#include <vector>
#include <string>
#include <set>

#include "Pattern.h"
#include "Varset.h"

using NodeIdType = unsigned long long;
using EdgeIdType = unsigned long long;

class PQueryOperator{
public:
    enum OperatorType {
        GRAPH_PATTERN, AND, OPTIONAL, UNION, MINUS, FILTER,
        PROJECTION, SORT, LIMIT, SKIP 
    };

    enum UnionType { SPARQL_UNION, CYPHER_UNION, CYPHER_UNION_ALL };
    enum OrderType { ASC, DSC };

    OperatorType type_;
    PQueryOperator *left_, *right_;
    PQueryOperator *parent_;

    /* For optimization, since we may drop some vars that won't be used. */
    Varset produce_tb_vars_;

    /* only used for graph pattern node */
    std::vector<NodeEdgePathVarInfo> vars_info_;
    std::set<std::pair<unsigned, unsigned>> edge_conflict_;

    /* only used for operator union */
    UnionType union_ty_;

    /* only used for filter, the var occurs in the exp is string not id
     * exp = f1 AND f2 AND f3 ... AND fn */
    std::vector<Expression> filters_;

    
    /* only used for projection */
    std::vector<Expression> proj_exps_;
    Varset renamed_cols_;
    
    /* only used for sort */
    Varset sorted_vars_;
    std::vector<OrderType> order_tys_;

    /* only used for skip, limit */
    Expression exp_;
    
    PQueryOperator();
    PQueryOperator(const PQueryOperator& that);
    PQueryOperator& operator=(const PQueryOperator& that);
    ~PQueryOperator();

    
};
