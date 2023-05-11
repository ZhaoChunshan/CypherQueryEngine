#include "PTempResult.h"
#include <cassert>
PTempResult::Header::Header(const PTempResult::Header &that):
spo_var_(that.spo_var_), edge_var_(that.edge_var_), other_var_(that.other_var_),
prop_(that.prop_), spo_var_id2col_(that.spo_var_id2col_),edge_var_id2col_(that.edge_var_id2col_),
value_var_id2col_(that.value_var_id2col_), var_propid2col_(that.var_propid2col_)
{

}

PTempResult::Header& PTempResult::Header::operator=(const Header &that) {
    if(this == &that) return *this;
    spo_var_ = that.spo_var_;
    edge_var_ = that.edge_var_;
    other_var_ = that.other_var_;
    prop_ = that.prop_;
    spo_var_id2col_ = that.spo_var_id2col_;
    edge_var_id2col_ = that.edge_var_id2col_;
    value_var_id2col_ = that.value_var_id2col_;
    var_propid2col_ = that.var_propid2col_;
    return *this;
}

void PTempResult::Header::setColumnVarName(const std::vector<unsigned > & spo_var, const std::vector<unsigned > & edge_var,
                                           const std::vector<unsigned > & other_var){
    spo_var_.vars = spo_var;
    edge_var_.vars = edge_var;
    other_var_.vars = other_var;
    for(int i = 0; i < (int)spo_var.size(); ++i){
        spo_var_id2col_[spo_var[i]] = i;
    }
    for(int i = 0; i < (int)edge_var.size(); ++i){
        edge_var_id2col_[edge_var[i]] = i;
    }
    for(int i = 0; i < (int)other_var.size(); ++i){
        value_var_id2col_[other_var[i]] = i;
    }
}

PTempResult::Record::Record(const Record& that):
spo_id_(that.spo_id_), edge_id_(that.edge_id_), values_(that.values_)
{
}

PTempResult::Record& PTempResult::Record::operator=(const Record& that){
    if(this == &that) return *this;
    spo_id_ = that.spo_id_;
    edge_id_ = that.edge_id_;
    values_ = that.values_;
    return *this;
}

void PTempResult::Record::swap(Record& that){
    spo_id_.swap(that.spo_id_);
    edge_id_.swap(that.edge_id_);
    values_.swap(that.values_);
}

PTempResult::PTempResult(const PTempResult& that):
rows_(that.rows_), head_(that.head_)
{

}

PTempResult& PTempResult::operator=(const PTempResult& that){
    if(this == &that) return *this;
    head_ = that.head_;
    rows_ = that.rows_;
    return *this;
}

PVarset<unsigned > PTempResult::getAllVarset() const{
    return head_.spo_var_ + head_.edge_var_ + head_.other_var_;
}

void PTempResult::print() const{
    int n = head_.spo_var_.getVarsetSize(), m = head_.edge_var_.getVarsetSize();
    int v = head_.other_var_.getVarsetSize(), prop_num = head_.prop_.getVarsetSize();
    for(int i = 0; i < n; ++i){
        std::cout << "SPO(" << head_.spo_var_.vars[i] << ")\t";
    }
    for(int i = 0; i < m; ++i){
        std::cout << "Edge(" << head_.edge_var_.vars[i] << ")\t";
    }
    for(int i = 0; i < v; ++i){
        std::cout << "Value(" << head_.other_var_.vars[i] << ")\t";
    }
    for(int i = 0; i < prop_num; ++i){
        std::cout << "Prop(" << head_.prop_.vars[i].first
            <<", " << head_.prop_.vars[i].second << ")\t";
    }
    std::cout << std::endl;
    for(auto & record: rows_){
        for(int i = 0; i < n; ++i){
            std::cout << record.spo_id_[head_.spo_var_id2col_.at(head_.spo_var_.vars[i])] << "\t";
        }
        for(int i = 0; i < m; ++i){
            std::cout << record.edge_id_[head_.edge_var_id2col_.at(head_.edge_var_.vars[i])] << "\t";
        }
        for(int i = 0; i < v; ++i){
            std::cout << record.values_[head_.value_var_id2col_.at(head_.other_var_.vars[i])].toString() << "\t";
        }
        for(int i = 0; i < prop_num; ++i){
            std::cout << record.values_[head_.var_propid2col_.at(head_.prop_.vars[i])].toString() << "\t";
        }
        std::cout << std::endl;
    }
    return;
}

/**
 * @brief compare two row on certain columns
 * @param x A row(record)
 * @param x_cols Columns to be compared of X
 * @param y Another row(record)
 * @param y_cols Columns to be compared of Y
 * @return 0 if equal; 1 if greater; -1 if less
 * @warning Element corresponding to x_cols[i] AND that corresponding to y_cols[i] must be comparable.
 * (i.e. Both of them are nodes, or edges, or values)
 */
int PTempResult::compareRow(const Record& x, const std::vector<unsigned > & x_cols,
                      const Record& y, const std::vector<unsigned > & y_cols, const std::vector<bool> & asc){
    // [0..n-1][n..n+m-1][n+m..n+m+v-1]
    int x_n = x.spo_id_.size(), x_m = x.edge_id_.size();
    int y_n = y.spo_id_.size(), y_m = y.edge_id_.size();
    int col_len = x_cols.size();
    for(int i = 0; i < col_len; ++i){
        if(x_cols[i] < x_n){
            assert(y_cols[i] < y_n);
            if(x.spo_id_[x_cols[i]] == y.spo_id_[y_cols[i]])
                continue;
            int comp_s = x.spo_id_[x_cols[i]] < y.spo_id_[y_cols[i]] ? -1 : 1;
            return asc[i] ? comp_s : -comp_s;
        } else if(x_cols[i] < x_n + x_m){
            assert(y_cols[i] >= y_n && y_cols[i] < y_n + y_m);
            if(x.edge_id_[x_cols[i] - x_n] == y.edge_id_[y_cols[i] - y_n])
                continue;
            int comp_e = x.edge_id_[x_cols[i] - x_n] < y.edge_id_[y_cols[i] - y_n] ? -1 : 1;
            return asc[i] ? comp_e : -comp_e;
        } else {
            assert(y_cols[i] >= y_n + y_m);
            int comp_v = x.values_[x_cols[i] - x_n - x_m].comp(y.values_[y_cols[i]- y_n - y_m]);
            if(comp_v != 0) {
                return asc[i] ? comp_v : -comp_v;
            }
        }
    }
    return 0;
}

/**
 * @brief Sort rows of a PTempResult table.
 * @param l Position of the first row of the table.
 * @param r Position of the last row of the table.
 * @param this_cols Columns will be considered
 * */
void PTempResult::sort(int l, int r, const std::vector<unsigned> & this_cols){
    std::vector<bool> asc(this_cols.size(), true);
    sort(l, r, this_cols, asc);
}

/**
 * @brief Sort rows of a PTempResult table.
 * @param l Position of the first row of the table.
 * @param r Position of the last row of the table.
 * @param this_cols Columns will be considered
 * @param asc Order by this_cols[i] ascending ?
 * */
void PTempResult::sort(int l, int r, const std::vector<unsigned> & this_cols, const std::vector<bool> &asc){
    if(r <= l)
        return;
    int i = l, j = r;
    while(i < j){
        while(i < j &&
            compareRow(rows_[i], this_cols, rows_[j], this_cols, asc) <= 0)
            --j;
        if(i != j) rows_[i].swap(rows_[j]);
        while(i < j &&
            compareRow(rows_[i], this_cols, rows_[j], this_cols, asc) <= 0)
            ++i;
        if(i != j) rows_[i].swap(rows_[j]);
    }
    sort(l, i - 1, this_cols, asc);
    sort(i + 1, r, this_cols, asc);
    return;
}

void PTempResult::sort(int l, int r, const std::vector<const GPStore::Expression *> & exps,
          const std::vector<bool> &asc, const void * pStore ){
    return;
}

std::vector<unsigned > PTempResult::extend(const std::vector<const GPStore::Expression *> & exps, const void * pstore){
    return {};
}

int PTempResult::findLeftBounder(const Record& x, const Header& x_head, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& y_cols) const{
    return -1;
}

int PTempResult::findRightBounder(const Record& x, const Header& x_head, const std::vector<unsigned >& x_cols, const std::vector<unsigned >& y_cols) const{
    return -1;
}

void PTempResult::doJoin(PTempResult &x, PTempResult &r){
    return;
}

void PTempResult::doUnion(PTempResult &r){
    return;
}

void PTempResult::doOptional(PTempResult &x, PTempResult &r){
    return;
}

void PTempResult::doFilter(const GPStore::Expression * filter, PTempResult &r, const void * pstore){
    return;
}

void PTempResult::doProjection(const std::vector<GPStore::Expression> & proj_exp, const std::vector<unsigned > & alias, const void * pstore){
    return;
}