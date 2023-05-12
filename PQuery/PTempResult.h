#ifndef PQUERY_PTEMPRESULT_H
#define PQUERY_PTEMPRESULT_H

#include <vector>
#include <map>
#include <string>
#include "../Value/Expression.h"
#include "../Value/Value.h"
#include "PVarset.h"

using NodeType = unsigned ;
using EdgeIdType = unsigned long long;

class PTempResult {
public:
    class Header{
    public:
        PVarset<unsigned> spo_var_;
        PVarset<unsigned> edge_var_;
        PVarset<unsigned> other_var_;
        PVarset<std::pair<unsigned, unsigned>> prop_;   // cache var property
        // Varset视作无序集合，不保证与Record的列对应，需要额外维护map记录对应关系
        std::map<unsigned, unsigned> spo_var_id2col_;
        std::map<unsigned, unsigned> edge_var_id2col_;
        std::map<unsigned, unsigned> value_var_id2col_;
        std::map<std::pair<unsigned,unsigned >, unsigned > var_propid2col_;
        Header() = default;
        Header(const Header & that);
        Header& operator=(const Header & that);
        ~Header() = default;
        void setColumnVarName(const std::vector<unsigned > & spo_var, const std::vector<unsigned > & edge_var,
                        const std::vector<unsigned > & other_var);
    };
    class Record{
    public:
        std::vector<NodeType > spo_id_;
        std::vector<EdgeIdType> edge_id_;
        std::vector<GPStore::Value> values_;
        Record() = default;
        Record(const Record& that);
        Record& operator=(const Record& that);
        ~Record() = default;
        void swap(Record& that);
    };
    
    std::vector<Record> rows_;
    Header head_;

    PTempResult() = default;
    PTempResult(const PTempResult& that);
    PTempResult& operator=(const PTempResult& that);
    ~PTempResult() = default;

    PVarset<unsigned > getAllVarset() const;

    void print() const;

    static int compareRow(const Record& x, const std::vector<unsigned > & x_cols,
                          const Record& y, const std::vector<unsigned > & y_cols,
                          const std::vector<bool> & asc);

    void sort(int l, int r, const std::vector<unsigned> & this_cols);
    void sort(int l, int r, const std::vector<unsigned> & this_cols, const std::vector<bool> &asc);

    void sort(int l, int r, const std::vector<const GPStore::Expression *> & exps,
              const std::vector<bool> &asc, const void * pStore );

    std::vector<unsigned > extend(const std::vector<const GPStore::Expression *> & exps, const void * pstore);

    int findLeftBounder(const Record& x, const Header& x_head, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& y_cols) const;
    int findRightBounder(const Record& x, const Header& x_head, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& y_cols) const;

    void doJoin(PTempResult &x, PTempResult &r);
    void doUnion(PTempResult &r);
    void doOptional(PTempResult &x, PTempResult &r);
    void doFilter(const GPStore::Expression * filter, PTempResult &r, const void * pstore);
    void doProjection(const std::vector<GPStore::Expression> & proj_exp, const std::vector<unsigned > & alias, const void * pstore);

};


#endif
