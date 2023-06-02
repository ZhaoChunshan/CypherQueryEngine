#ifndef PQUERY_PTEMPRESULT_H
#define PQUERY_PTEMPRESULT_H

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include "../Value/Expression.h"
#include "../Value/Value.h"
#include "PVarset.h"
#include "../Util/Util.h"

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
        void setVarset(const std::vector<unsigned > & spo_var, const std::vector<unsigned > & edge_var,
                       const std::vector<unsigned > & other_var,const std::vector<std::pair<unsigned,unsigned>> & prop);
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
              const std::vector<bool> &asc, KVstore * _kvstore,
              const std::unordered_map<std::string, GPStore::Value> * params);

    int findLeftBounder(const Record& x, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& this_cols) const;
    int findRightBounder(const Record& x, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& this_cols) const;

    void extend(const GPStore::Expression * exp, KVstore * _kvstore, const std::unordered_map<std::string, GPStore::Value> * params);

    std::vector<unsigned > projectionView(const std::vector<const GPStore::Expression *> & exps, KVstore * _kvstore,
                                      const std::unordered_map<std::string, GPStore::Value> * params);

    void doJoin(PTempResult &x, PTempResult &r, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& this_cols);
    void doCartesianProduct(PTempResult &x, PTempResult &r);
    void doUnion(PTempResult &r);
    void doLeftOuterJoin(PTempResult &x, PTempResult &r, const std::vector<unsigned >& x_cols,
                    const std::vector<unsigned >& this_cols);
    void doFilter(PTempResult &r, const GPStore::Expression * filter, KVstore * _kvstore,
                  const std::unordered_map<std::string, GPStore::Value> * params);
    void doProjection(const std::vector<const GPStore::Expression *> & proj_exps, const std::vector<unsigned > & alias,
                      const std::vector<unsigned > & keep_vars,
                      KVstore * _kvstore, const std::unordered_map<std::string, GPStore::Value> * params);
    void doDistinct(PTempResult &r, const std::vector<unsigned > & dis_cols, const std::vector<unsigned > already_order);
    void doUnwind(PTempResult &r, const GPStore::Expression * exp,  unsigned var_id, KVstore * _kvstore,
                  const std::unordered_map<std::string, GPStore::Value> * params);
    std::vector<unsigned > doGroupBy(const std::vector<unsigned > & grouping_keys);
    void doAggregation(PTempResult &r, const std::vector<unsigned > & groups, const std::vector<const GPStore::Expression *> & aggr_val,
                       std::vector<unsigned > aggr_id,  KVstore * _kvstore,
                       const std::unordered_map<std::string, GPStore::Value> * params);
    void doLimit(PTempResult &r, unsigned limit = INVALID, unsigned skip = 0);
private:

    static std::vector<int> mapTo(const PVarset<unsigned > &from, const std::map<unsigned ,unsigned > & id2col);
    static std::vector<int> mapTo(const PVarset<std::pair<unsigned ,unsigned >> &from,
                     const std::map<std::pair<unsigned ,unsigned > ,unsigned > & id2col);
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
    void copyColumn(unsigned col_id, unsigned part_num);

    void
    evaluateAggregationExpression(GPStore::Expression *exp, int _begin, int _end, KVstore * _kvstore,
                                  const std::unordered_map<std::string, GPStore::Value> * params);

    void
    evaluateAggregationExpression(GPStore::Atom *atom, int _begin, int _end, KVstore * _kvstore,
                                  const std::unordered_map<std::string, GPStore::Value> * params);

    void
    evaluateAggregationFunction(GPStore::FunctionInvocation *func, int _begin, int _end, KVstore * _kvstore,
                                const std::unordered_map<std::string, GPStore::Value> * params);

    static void removeDuplicate(std::vector<GPStore::Value> & values);

};


#endif
