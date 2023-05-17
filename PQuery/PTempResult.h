#ifndef PQUERY_PTEMPRESULT_H
#define PQUERY_PTEMPRESULT_H

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include "../Value/Expression.h"
#include "../Value/Value.h"
#include "PVarset.h"

// copy from util.h of gpstore 1.2 branch
// if merge code, just remove this and #include "util.h"
using NodeType = unsigned ;
typedef unsigned TYPE_ENTITY_LITERAL_ID;
typedef unsigned TYPE_PROPERTY_ID;
typedef unsigned long long TYPE_EDGE_ID;
static const TYPE_ENTITY_LITERAL_ID INVALID_ENTITY_LITERAL_ID = 0xffffffff;
static const TYPE_PROPERTY_ID INVALID_PROPERTY_ID = 0xffffffff;
static const TYPE_EDGE_ID INVALID_EDGE_ID = 0xffffffffffffffff;

class PTempResult {
public:
    class Header{
    public:
        PVarset<unsigned> spo_var_;
        PVarset<unsigned> edge_var_;
        PVarset<unsigned> other_var_;
        PVarset<std::pair<unsigned, TYPE_PROPERTY_ID>> prop_;   // cache var property
        // Varset视作无序集合，不保证与Record的列对应，需要额外维护map记录对应关系
        std::map<unsigned, unsigned> spo_var_id2col_;
        std::map<unsigned, unsigned> edge_var_id2col_;
        std::map<unsigned, unsigned> value_var_id2col_;
        std::map<std::pair<unsigned,TYPE_PROPERTY_ID >, unsigned > var_propid2col_;
        Header() = default;
        Header(const Header & that);
        Header& operator=(const Header & that);
        ~Header() = default;
        void initColumnInfoByVarset();
        void setColumnVarName(const std::vector<unsigned > & spo_var, const std::vector<unsigned > & edge_var,
                        const std::vector<unsigned > & other_var);
    };
    class Record{
    public:
        std::vector<TYPE_ENTITY_LITERAL_ID > spo_id_;
        std::vector<TYPE_EDGE_ID> edge_id_;
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

    static int compareRow(const Record& x, const std::vector<unsigned > & x_cols,
                          const Record& y, const std::vector<unsigned > & y_cols);

    void sort(int l, int r, const std::vector<unsigned> & this_cols);
    void sort(int l, int r, const std::vector<unsigned> & this_cols, const std::vector<bool> &asc);

    void sort(int l, int r, const std::vector<const GPStore::Expression *> & exps,
              const std::vector<bool> &asc, const void * pStore, const std::unordered_map<std::string, GPStore::Value> & param);

    int findLeftBounder(const Record& x, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& this_cols) const;
    int findRightBounder(const Record& x, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& this_cols) const;

    std::vector<unsigned > extend(const std::vector<const GPStore::Expression *> & exps, const void * pstore,
                                  const std::unordered_map<std::string, GPStore::Value> & param);

    std::vector<unsigned > expsToCols(const std::vector<const GPStore::Expression *> & exps, const void * pstore,
                                      const std::unordered_map<std::string, GPStore::Value> & param);

    void doJoin(PTempResult &x, PTempResult &r, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& this_cols);
    void doCartesianProduct(PTempResult &x, PTempResult &r);
    void doUnion(PTempResult &r);
    void doOptional(PTempResult &x, PTempResult &r, const std::vector<unsigned >& x_cols,
                    const std::vector<unsigned >& this_cols);
    void doFilter(const GPStore::Expression * filter, PTempResult &r, const void * pstore,
                  const std::unordered_map<std::string, GPStore::Value> & param);
    void doProjection(const std::vector<GPStore::Expression> & proj_exp, const std::vector<unsigned > & alias, const void * pstore);
    void doDistinct(const std::vector<unsigned > & this_cols);
private:

    static std::vector<int> mapTo(const PVarset<unsigned > &from, const std::map<unsigned ,unsigned > & id2col);
    static std::vector<int> mapTo(const PVarset<std::pair<unsigned ,unsigned >> &from,
                     const std::map<std::pair<unsigned ,unsigned > ,unsigned > & id2col);
    static void generateRow(PTempResult &r, Record & x, Record & y,
                            const std::vector<int> & r_spo2x_col, const std::vector<int> & r_spo2y_col,
                            const std::vector<int> & r_edge2x_col, const std::vector<int> & r_edge2y_col,
                            const std::vector<int> & r_val2x_col, const std::vector<int> & r_val2y_col,
                            const std::vector<int> & r_prop2x_col,const std::vector<int> &  r_prop2y_col);
    static void generateRow(Record &r, Record & x, Record & y,
                            const std::vector<int> & r_spo2x_col, const std::vector<int> & r_spo2y_col,
                            const std::vector<int> & r_edge2x_col, const std::vector<int> & r_edge2y_col,
                            const std::vector<int> & r_val2x_col, const std::vector<int> & r_val2y_col,
                            const std::vector<int> & r_prop2x_col,const std::vector<int> &  r_prop2y_col);

    static void generateRow(Record &r, Record & x,
                            const std::vector<int> & r_spo2x_col,
                            const std::vector<int> & r_edge2x_col,
                            const std::vector<int> & r_val2x_col,
                            const std::vector<int> & r_prop2x_col);

};


#endif
