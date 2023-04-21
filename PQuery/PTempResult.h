#ifndef PTEMPRESULT_H
#define PTEMPRESULT_H

#include <vector>
#include <map>
#include <string>
#include "../Value/Value.h"
#include "PVarset.h"
using NodeIdType = unsigned;
using EdgeIdType = unsigned long long;

class PTempResult {
public:
    class Header{
        PVarset<unsigned> nodes_var_;
        PVarset<unsigned> edges_var_;
        PVarset<unsigned> other_var_;
        std::map<unsigned, unsigned> var_id2col_;
    };
    class Record{
        // colmn 0 ~ n - 1
        std::vector<NodeIdType> nodes_id_;
        // colmn n ~ m + n - 1
        std::vector<EdgeIdType> edges_id_;
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
};


#endif
