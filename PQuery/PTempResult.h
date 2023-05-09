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
#define SPO_INVALID 0xffffffffU
#define EDGE_INVALID 0xffffffffffffffffULL

class PTempResult {
public:
    class Header{
        PVarset<unsigned> spo_var_;
        PVarset<unsigned> edge_var_;
        PVarset<unsigned> other_var_;
        PVarset<std::pair<unsigned, unsigned>> prop_;   // cache var property
        // Varset视作无序集合，不保证与Record的列对应，需要额外维护map记录对应关系
        std::map<unsigned, unsigned> var_id2col_;
        std::map<std::pair<unsigned,unsigned >, unsigned > var_propid2col_;
    };
    class Record{
        // colmn 0 ~ n - 1
        std::vector<NodeType > spo_id_;
        // colmn n ~ m + n - 1
        std::vector<EdgeIdType> edge_id_;
        // column n + m ~ m + n + v  - 1
        std::vector<GPStore::Value> values_;
        Record();
        Record(const Record& that);
        Record& operator=(const Record& that);
        ~Record();
        void swap(Record& that);
    };
    
    std::vector<Record> table_rows_;
    Header table_head_;

    PTempResult();
    PTempResult(const PTempResult& that);
    PTempResult& operator=(const PTempResult& that);
    ~PTempResult();

    static int compareRow(const Record& x, const std::vector<unsigned > & x_cols,
                          const Record& y, const std::vector<unsigned > & y_cols);

    void sort(int l, int r, const std::vector<unsigned> & this_pos);

    void sort(int l, int r, const std::vector<const GPStore::Expression *> & exps,
              const std::vector<bool> asc, const void * pstore );

    std::vector<unsigned > extend(const std::vector<const GPStore::Expression *> & exps, const void * pstore);
};


#endif
