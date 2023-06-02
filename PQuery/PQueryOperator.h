#ifndef PQUERY_PQUERYOPERATOR_H
#define PQUERY_PQUERYOPERATOR_H

#include <vector>
#include <string>
#include <set>

#include "../PParser/Pattern.h"
#include "PVarset.h"
#include "../PParser/CypherAST.h"
#include "../Util/Util.h"


/**
 * @brief Class PQueryOperator: An operator, or an action that should be performed.
 * */
class PQueryOperator{
public:
    enum OperatorType {
        BGP, FILTER, PROJECTION,        // three most important Operators
        AND, OPTIONAL, UNION, MINUS,    // 4 binary-operators
        MODIFIER,                       // handle order by, skip, limit, distinct
        UNWIND, CALL,                   // for cypher read clause unwind, call
        CREATE, DELETE, SET, REMOVE,    // for cypher update clause
        GROUP_BY, AGGREGATION,          // for aggregation
        SHORTEST_PATH,                  // for shortest path operator

        // Not implement. 
        HAVING, SCOPE, BIND, TABLE
    };

    OperatorType type_;

    /* For optimization(Projection Pushdown), since we may drop some vars that won't be used. */
    PVarset<unsigned> maximal_varset_, minimal_varset_;

    PQueryOperator() = default;
    PQueryOperator(OperatorType ty):type_(ty){ }
    virtual ~PQueryOperator() = default;
    virtual void print(int dep = 0) const = 0;
};

class BGPOperator: public PQueryOperator {
public:
    std::vector<std::unique_ptr<GPStore::RigidPattern>> pattern_;
    PVarset<std::pair<unsigned, unsigned>> edge_conflict_;
    std::vector<std::unique_ptr<GPStore::Expression>> filters_;
    BGPOperator():PQueryOperator(BGP){ }
    ~BGPOperator() override = default;
    void print(int dep = 0) const override;
};

class FilterOperator: public PQueryOperator {
public:
    std::vector<std::unique_ptr<GPStore::Expression>> filters_;
    FilterOperator():PQueryOperator(FILTER){ }
    ~FilterOperator() override = default;
    void print(int dep = 0) const override;
};

class ProjectionOperator: public PQueryOperator {
public:
    std::vector<std::unique_ptr<GPStore::Expression>> proj_exps_;
    std::vector<unsigned> var_id_;
    ProjectionOperator():PQueryOperator(PROJECTION){ }
    ~ProjectionOperator() override = default;
    void print(int dep = 0) const override;
};


class AndOperator : public PQueryOperator {
public:
    std::vector<std::unique_ptr<GPStore::Expression>> filters_;
    AndOperator():PQueryOperator(AND){ }
    ~AndOperator() override = default;
    void print(int dep = 0) const override;
};

class OptionalOperator : public PQueryOperator {
public:
    OptionalOperator():PQueryOperator(OPTIONAL){ }
    ~OptionalOperator() override = default;
    void print(int dep = 0) const override;
};

class UnionOperator : public PQueryOperator {
public:
    enum UnionType { SPARQL_UNION, CYPHER_UNION};
    UnionType union_ty_;
    UnionOperator(UnionType union_ty = SPARQL_UNION):PQueryOperator(UNION), union_ty_(union_ty){ }
    ~UnionOperator() override = default;
    void print(int dep = 0) const override;
};

class MinusOperator : public PQueryOperator {
public:
    MinusOperator():PQueryOperator(MINUS){ }
    ~MinusOperator() override = default;
    void print(int dep = 0) const override;
};

class ModifierOperator : public PQueryOperator {
public:
    std::vector<std::unique_ptr<GPStore::Expression>> order_exps_;
    std::vector<bool> ascending_;
    unsigned skip_, limit_; //default: 0, 0xffffffff
    bool distinct_;       // remove duplicated rows;
    std::vector<unsigned > distinct_vars;
    ModifierOperator():PQueryOperator(MODIFIER), skip_(0), limit_(INVALID), distinct_(false){ }
    ~ModifierOperator() override = default;
    void print(int dep = 0) const override;
};

class UnwindOperator : public PQueryOperator {
public:
    std::unique_ptr<GPStore::Expression> unwind_;
    unsigned var_id_;
    UnwindOperator():PQueryOperator(UNWIND), var_id_(INVALID){ }
    ~UnwindOperator() override = default;
    void print(int dep = 0) const override;
};

class CallOperator : public PQueryOperator {
public:
    std::vector<std::string> procedure_name_;
    std::vector<std::unique_ptr<GPStore::Expression>> args_;
    std::vector<std::string> yield_items_;
    std::vector<unsigned > yield_var_id_;
    std::unique_ptr<GPStore::Expression> filter_;
    CallOperator():PQueryOperator(CALL){ }
    ~CallOperator() override = default;
    void print(int dep = 0) const override;
};


class CreateOperator : public PQueryOperator {
public:
    std::vector<std::unique_ptr<GPStore::RigidPattern>> pattern_;
    CreateOperator():PQueryOperator(CREATE){ }
    ~CreateOperator() override = default;
    void print(int dep = 0) const override;
};

class DeleteOperator : public PQueryOperator {
public:
    bool detach;
    std::vector<std::unique_ptr<GPStore::Expression>> exp_;
    DeleteOperator():PQueryOperator(DELETE), detach(false){ }
    ~DeleteOperator() override = default;
    void print(int dep = 0) const override;
};

class SetOperator : public PQueryOperator {
public:
    /**
     * ==================== var_names_ ====================
     * ====================  var_ids_  ====================
     * ========= labels =========||========= exps =========
     */
    std::vector<std::string> var_names_;
    std::vector<unsigned > var_ids_;
    // handle set node labels
    std::vector<std::vector<std::string>> labels_;
    // handle assign property && add property
    std::vector<bool> add_property_;        // True: add(e.g. n += MapValue} ; False: assign(e.g. n = MapValue}
    std::vector<std::unique_ptr<GPStore::Expression>> exps_;

    /**
     * ==================== prop_exps_ ====================
     * ==================== prop_vals_ ====================
     * */
    std::vector<std::unique_ptr<GPStore::Expression>> prop_exps_;
    std::vector<std::unique_ptr<GPStore::Expression>> prop_vals_;
    SetOperator():PQueryOperator(SET){ }
    ~SetOperator() override = default;
    void print(int dep = 0) const override;
};

class RemoveOperator : public PQueryOperator {
public:
    // remove var_names_[labels] OR remove prop_exp(e.g. a.age)
    std::vector<std::string> var_names_;
    std::vector<unsigned > var_ids_;
    std::vector<std::vector<std::string>> labels_;  // labels will be removed
    std::vector<std::unique_ptr<GPStore::Expression>> prop_exps_;   // prop will be removed
    RemoveOperator():PQueryOperator(REMOVE){ }
    ~RemoveOperator() override = default;
    void print(int dep = 0) const override;
};

class GroupByOperator : public PQueryOperator {
public:
    std::vector<unsigned> grouping_keys_;
    GroupByOperator():PQueryOperator(GROUP_BY){ }
    ~GroupByOperator() override = default;
    void print(int dep = 0) const override;
};

class AggregationOperator : public PQueryOperator {
public:
    std::vector<unsigned > grouping_keys_;
    std::vector<std::unique_ptr<GPStore::Expression>> aggr_value_;
    std::vector<unsigned> aggr_var_id_;
    AggregationOperator():PQueryOperator(AGGREGATION){ }
    ~AggregationOperator() override = default;
    void print(int dep = 0) const override;
};

class ShortestPathOperator : public PQueryOperator {
public:
    bool is_all_shortest_;
    unsigned src_, tgt_, path_var_id_;  // remember check if it's invalid
    std::unique_ptr<GPStore::EdgePattern> edge_pattern_;
    ShortestPathOperator():PQueryOperator(SHORTEST_PATH), is_all_shortest_(false), \
        src_(INVALID), tgt_(INVALID), path_var_id_(INVALID){ }
    ~ShortestPathOperator() override = default;
    void print(int dep = 0) const override;
};

#endif