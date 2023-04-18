#ifndef PTEMPRESULT_H
#define PTEMPRESULT_H

#include <vector>
#include <map>
#include <string>
#include "../Value/Value.h"
#include "Varset.h"
using NodeIdType = unsigned long long;
using EdgeIdType = unsigned long long;

class PTempResult {
public:
    class Header{
        Varset nodes_var_;
        Varset edges_var_;
        Varset other_var_;
    };
    class Record{
        std::vector<NodeIdType> nodes_id_;
        std::vector<EdgeIdType> edges_id_;
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
