#include "PTempResult.h"
#include "../Value/PCalculator.h"
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

void PTempResult::Header::initColumnInfoByVarset(){
    for(int i = 0; i < spo_var_.getVarsetSize();++i)
        spo_var_id2col_[spo_var_.vars[i]] = i;
    for(int i = 0; i < edge_var_.getVarsetSize(); ++i)
        edge_var_id2col_[edge_var_.vars[i]] = i;
    for(int i = 0; i < other_var_.getVarsetSize();++i)
        value_var_id2col_[other_var_.vars[i]] = i;
    for(int j = 0; j < prop_.getVarsetSize(); ++j)
        var_propid2col_[prop_.vars[j]] = j + other_var_.getVarsetSize();
    return;
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

int PTempResult::compareRow(const Record& x, const std::vector<unsigned > & x_cols,
                      const Record& y, const std::vector<unsigned > & y_cols){
    std::vector<bool> asc(x_cols.size(), true);
    return compareRow(x, x_cols, y, y_cols, asc);
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
}

void PTempResult::sort(int l, int r, const std::vector<const GPStore::Expression *> & exps,
          const std::vector<bool> &asc, const void * pStore, const std::unordered_map<std::string, GPStore::Value> & param ){
    auto this_cols = expsToCols(exps, pStore, param);
    sort(l, r, this_cols, asc);
}

std::vector<unsigned > PTempResult::extend(const std::vector<const GPStore::Expression *> & exps, const void * pstore,
                                           const std::unordered_map<std::string, GPStore::Value> & param){
    std::vector<unsigned > cols;
    unsigned n = head_.spo_var_.getVarsetSize(), m = head_.edge_var_.getVarsetSize();
    unsigned v = head_.other_var_.getVarsetSize() + head_.prop_.getVarsetSize();
    unsigned  tot = m + n + v;
    for(auto &r : rows_){
        for(auto exp : exps){
            r.values_.push_back(PCalculator::evaluateExpression(exp, r.spo_id_, head_.spo_var_id2col_, r.edge_id_,
                                                                head_.edge_var_id2col_, r.values_, head_.value_var_id2col_,
                                                                head_.var_propid2col_, param, pstore));
            cols.push_back(tot++);

        }
    }
    return cols;
}

/**
 * @brief Map exp to columns of this PTempResult. If exp is a var, or var.prop, then the target column may
 * already in the table; otherwise exp should be evaluated, and store in values.
 * */
std::vector<unsigned > PTempResult::expsToCols(const std::vector<const GPStore::Expression *> & exps, const void * pstore,
                                  const std::unordered_map<std::string, GPStore::Value> & param){
    std::vector<unsigned > this_cols;
    unsigned n = head_.spo_var_.getVarsetSize(), m = head_.edge_var_.getVarsetSize();
    unsigned v = head_.other_var_.getVarsetSize() + head_.prop_.getVarsetSize();
    std::vector<const GPStore::Expression *> expand_exps;
    for(auto exp : exps){
        if(exp->isVariable()){
            unsigned var_id = exp->getVariableId();
            if(head_.spo_var_.findVar(var_id)){
                this_cols.push_back(head_.spo_var_id2col_.at(var_id));
            } else if(head_.edge_var_.findVar(var_id)){
                this_cols.push_back(n + head_.edge_var_id2col_.at(var_id));
            } else if(head_.other_var_.findVar(var_id)){
                this_cols.push_back(n + m + head_.value_var_id2col_.at(var_id));
            } else { assert(false);}
        } else if(exp->isVariableProp()){
            unsigned var_id = exp->getVariableId();
            TYPE_PROPERTY_ID prop_id = exp->property_label_->prop_ids_[0];
            auto p = std::make_pair(var_id, prop_id);
            if(head_.prop_.findVar(p)){
                this_cols.push_back(n + m + head_.var_propid2col_.at(p));
            }
        } else {
            this_cols.push_back(n + m + v + expand_exps.size());
            expand_exps.push_back(exp);
        }
    }

    extend(expand_exps, pstore, param);
    return this_cols;
}


/**
 * @brief For a table that is sorted on certain columns, Find first position of the columns of x
 * @param x
 * @param x_cols
 * @param this_cols
 * @return left bounder position if x was found, else -1
 */
int PTempResult::findLeftBounder(const Record& x, const std::vector<unsigned >& x_cols,
                                 const std::vector<unsigned >& this_cols) const{
    int l = 0, r = (int)this->rows_.size() - 1;
    if(r < 0) return -1;
    while(l < r){
        int m  = (l + r) / 2;
        if(compareRow(rows_[m], this_cols, x, x_cols) >= 0)
            r = m;
        else
            l = m + 1;
    }
    if(compareRow(rows_[l], this_cols, x, x_cols) == 0)
            return l;
    return -1;
}

int PTempResult::findRightBounder(const Record& x, const std::vector<unsigned >& x_cols,
                                  const std::vector<unsigned >& this_cols) const{
    int l = 0, r = (int)this->rows_.size() - 1;
    if(r < 0) return -1;
    while(l < r){
        int m  = (l + r) / 2 + 1;
        if(compareRow(rows_[m], this_cols, x, x_cols) <= 0)
            l = m;
        else
            r = m - 1;
    }
    if(compareRow(rows_[l], this_cols, x, x_cols) == 0)
        return l;
    return -1;
}

/**
 * @brief Join two tables on certain columns, and produce result to r.
 * @param x another table
 * @param r empty table to stream result to; Varsets in the header of r is initialized whereas position information is not.
 */
void PTempResult::doJoin(PTempResult &x, PTempResult &r, const std::vector<unsigned >& x_cols,
                         const std::vector<unsigned >& this_cols){
    int m = this->rows_.size(), n = x.rows_.size();

    auto r_spo2x_col = mapTo(r.head_.spo_var_, x.head_.spo_var_id2col_);
    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2x_col = mapTo(r.head_.edge_var_, x.head_.edge_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2x_col = mapTo(r.head_.other_var_, x.head_.value_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2x_col = mapTo(r.head_.prop_, x.head_.var_propid2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);

    r.head_.initColumnInfoByVarset();

    // this table is outer table, x is inner table.
    if(m > n){

        x.sort(0, n - 1, x_cols);
        for(int i = 0; i < m; ++i){
            int lb = x.findLeftBounder(rows_[i], this_cols, x_cols);
            if(lb == -1) continue;
            int rb = x.findRightBounder(rows_[i], this_cols, x_cols);
            for(int j = lb; j <= rb; ++j) {
                generateRow(r, this->rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col, r_edge2x_col,
                            r_val2this_col, r_val2x_col, r_prop2this_col, r_prop2x_col);
            }
        }
    }

    // this table is the inner table, x is outer.
    else {
        this->sort(0, m - 1, this_cols);
        for(int j = 0; j < n; ++j){
            int lb = this->findLeftBounder(x.rows_[j], x_cols, this_cols);
            if(lb == -1) continue;
            int rb = this->findRightBounder(x.rows_[j], x_cols, this_cols);
            for(int i = lb; i <= rb; ++i){
                generateRow(r, this->rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col, r_edge2x_col,
                            r_val2this_col, r_val2x_col, r_prop2this_col, r_prop2x_col);
            }
        }
    }

    return;
}


/**
 * @brief do cartesian product of two tables and produce result to r.
 * @param x another table
 * @param r empty table to stream result to; Varsets in the header of r is initialized whereas position information is not.
 */
void PTempResult::doCartesianProduct(PTempResult &x, PTempResult &r){
    int m = this->rows_.size(), n = x.rows_.size();

    // Assumption: r is empty && its varset[i] just at column[i]
    auto r_spo2x_col = mapTo(r.head_.spo_var_, x.head_.spo_var_id2col_);
    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2x_col = mapTo(r.head_.edge_var_, x.head_.edge_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2x_col = mapTo(r.head_.other_var_, x.head_.value_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2x_col = mapTo(r.head_.prop_, x.head_.var_propid2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);

    r.head_.initColumnInfoByVarset();

    // this table is inner table, x is outer table.
    if(m > n){

        for(int j = 0; j < n; ++j){
            for(int i = 0; i < m; ++i) {
                generateRow(r, this->rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col, r_edge2x_col,
                            r_val2this_col, r_val2x_col, r_prop2this_col, r_prop2x_col);
            }
        }
    }

    // this table is the outer table, x is inner.
    else {
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                generateRow(r, this->rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col, r_edge2x_col,
                            r_val2this_col, r_val2x_col, r_prop2this_col, r_prop2x_col);
            }
        }
    }
    return;
}

void PTempResult::doUnion(PTempResult &r){
    auto r_spo2this_col = mapTo(r.head_.spo_var_, head_.spo_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, head_.edge_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, head_.value_var_id2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, head_.var_propid2col_);
    for(int i = 0; i < (int)this->rows_.size(); ++i){
        r.rows_.emplace_back();
        generateRow(r.rows_.back(), this->rows_[i], r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
    }
    return;
}

void PTempResult::doOptional(PTempResult &x, PTempResult &r, const std::vector<unsigned >& x_cols,
                             const std::vector<unsigned >& this_cols){
    int m = this->rows_.size(), n = x.rows_.size();

    auto r_spo2x_col = mapTo(r.head_.spo_var_, x.head_.spo_var_id2col_);
    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2x_col = mapTo(r.head_.edge_var_, x.head_.edge_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2x_col = mapTo(r.head_.other_var_, x.head_.value_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2x_col = mapTo(r.head_.prop_, x.head_.var_propid2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);

    r.head_.initColumnInfoByVarset();
    x.sort(0, n - 1, x_cols);
    for(int i = 0; i < m; ++i){
        int lb = x.findLeftBounder(rows_[i], this_cols, x_cols);
        if(lb == -1){
            r.rows_.emplace_back();
            generateRow(r.rows_.back(), rows_[i], r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
        } else {
            int rb = this->findRightBounder(rows_[i], this_cols, x_cols);
            for(int j = lb; j <= rb; ++j){
                r.rows_.emplace_back();
                generateRow(r.rows_.back(), rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col,
                            r_edge2x_col, r_val2this_col, r_val2x_col, r_prop2this_col, r_prop2x_col);
            }
        }
    }
    return;
}

void PTempResult::doFilter(const GPStore::Expression * filter, PTempResult &r, const void * pstore,
                           const std::unordered_map<std::string, GPStore::Value> & param){
    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);

    for(auto &row : this->rows_){
        GPStore::Value val = PCalculator::evaluateExpression(filter, row.spo_id_, head_.spo_var_id2col_, row.edge_id_,
                                                             head_.edge_var_id2col_, row.values_, head_.value_var_id2col_,
                                                             head_.var_propid2col_, param, pstore);
        if(val.type_ == GPStore::Value::BOOLEAN && val.data_.Boolean){
            r.rows_.emplace_back();
            generateRow(r.rows_.back(), row, r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
        }
    }
}

void PTempResult::doProjection(const std::vector<GPStore::Expression> & proj_exp, const std::vector<unsigned > & alias, const void * pstore){

    return;
}


/// helper functions

std::vector<int> PTempResult::mapTo(const PVarset<unsigned > &from, const std::map<unsigned ,unsigned > & id2col){
    std::vector<int> mm;
    for(unsigned var : from.vars){
        auto it = id2col.find(var);
        if(it != id2col.end())
            mm.push_back((int)it->second);
        else
            mm.push_back(-1);
    }
    return mm;
}

std::vector<int> PTempResult::mapTo(const PVarset<std::pair<unsigned ,unsigned >> &from,
                 const std::map<std::pair<unsigned ,unsigned > ,unsigned > & id2col){
    std::vector<int> mm;
    for(auto& var : from.vars){
        auto it = id2col.find(var);
        if(it != id2col.end())
            mm.push_back((int)it->second);
        else
            mm.push_back(-1);
    }
    return mm;
}

void PTempResult::generateRow(PTempResult &r, Record & x, Record & y,
                                          const std::vector<int> & r_spo2x_col, const std::vector<int> & r_spo2y_col,
                                          const std::vector<int> & r_edge2x_col, const std::vector<int> & r_edge2y_col,
                                          const std::vector<int> & r_val2x_col, const std::vector<int> & r_val2y_col,
                                          const std::vector<int> & r_prop2x_col,const std::vector<int> &  r_prop2y_col)
{
    r.rows_.emplace_back();
    for(int var_idx = 0; var_idx < r.head_.spo_var_.getVarsetSize(); ++var_idx){
        if(r_spo2x_col[var_idx] != -1){
            r.rows_.back().spo_id_.push_back(x.spo_id_[r_spo2x_col[var_idx]]);
        } else {
            r.rows_.back().spo_id_.push_back(y.spo_id_[r_spo2y_col[var_idx]]);
        }
    }
    for(int var_idx = 0; var_idx < r.head_.edge_var_.getVarsetSize(); ++var_idx){
        if(r_edge2x_col[var_idx] != -1){
            r.rows_.back().edge_id_.push_back(x.edge_id_[r_edge2x_col[var_idx]]);
        } else {
            r.rows_.back().edge_id_.push_back(y.edge_id_[r_edge2y_col[var_idx]]);
        }
    }

    for(int var_idx = 0; var_idx < r.head_.other_var_.getVarsetSize(); ++var_idx){
        if(r_val2x_col[var_idx] != -1){
            r.rows_.back().values_.emplace_back(x.values_[r_val2x_col[var_idx]]);
        } else {
            r.rows_.back().values_.emplace_back(y.values_[r_val2y_col[var_idx]]);
        }
    }

    for(int var_idx = 0; var_idx < r.head_.prop_.getVarsetSize(); ++var_idx){
        if(r_prop2x_col[var_idx] != -1){
            r.rows_.back().values_.emplace_back(x.values_[r_prop2x_col[var_idx]]);
        } else {
            r.rows_.back().values_.emplace_back(y.values_[r_prop2y_col[var_idx]]);
        }
    }
    return;
}

void PTempResult::generateRow(Record &r, Record & x, Record & y,
                        const std::vector<int> & r_spo2x_col, const std::vector<int> & r_spo2y_col,
                        const std::vector<int> & r_edge2x_col, const std::vector<int> & r_edge2y_col,
                        const std::vector<int> & r_val2x_col, const std::vector<int> & r_val2y_col,
                        const std::vector<int> & r_prop2x_col,const std::vector<int> &  r_prop2y_col){
    for(int var_idx = 0; var_idx < (int)r_spo2x_col.size(); ++var_idx){
        if(r_spo2x_col[var_idx] != -1){
            r.spo_id_.push_back(x.spo_id_[r_spo2x_col[var_idx]]);
        } else if(r_spo2y_col[var_idx] != -1){
            r.spo_id_.push_back(y.spo_id_[r_spo2y_col[var_idx]]);
        } else {
            r.spo_id_.push_back(INVALID_ENTITY_LITERAL_ID);
        }
    }
    for(int var_idx = 0; var_idx < (int)r_edge2x_col.size(); ++var_idx){
        if(r_edge2x_col[var_idx] != -1){
            r.edge_id_.push_back(x.edge_id_[r_edge2x_col[var_idx]]);
        } else if(r_edge2y_col[var_idx] != -1){
            r.edge_id_.push_back(y.edge_id_[r_edge2y_col[var_idx]]);
        } else {
            r.edge_id_.push_back(INVALID_EDGE_ID);
        }
    }

    for(int var_idx = 0; var_idx < (int)r_val2x_col.size(); ++var_idx){
        if(r_val2x_col[var_idx] != -1){
            r.values_.emplace_back(x.values_[r_val2x_col[var_idx]]);
        } else if(r_val2y_col[var_idx] != -1) {
            r.values_.emplace_back(y.values_[r_val2y_col[var_idx]]);
        } else {
            r.values_.emplace_back(GPStore::Value::NO_VALUE);
        }
    }

    for(int var_idx = 0; var_idx < (int)r_prop2x_col.size(); ++var_idx){
        if(r_prop2x_col[var_idx] != -1){
            r.values_.emplace_back(x.values_[r_prop2x_col[var_idx]]);
        } else if(r_prop2y_col[var_idx] != -1){
            r.values_.emplace_back(y.values_[r_prop2y_col[var_idx]]);
        } else {
            r.values_.emplace_back(GPStore::Value::NO_VALUE);
        }
    }
}

void PTempResult::generateRow(Record &r, Record & x,
                        const std::vector<int> & r_spo2x_col,
                        const std::vector<int> & r_edge2x_col,
                        const std::vector<int> & r_val2x_col,
                        const std::vector<int> & r_prop2x_col){
    for(int var_idx = 0; var_idx < (int)r_spo2x_col.size(); ++var_idx){
        if(r_spo2x_col[var_idx] != -1){
            r.spo_id_.push_back(x.spo_id_[r_spo2x_col[var_idx]]);
        } else {
            r.spo_id_.push_back(INVALID_ENTITY_LITERAL_ID);
        }
    }
    for(int var_idx = 0; var_idx < (int)r_edge2x_col.size(); ++var_idx){
        if(r_edge2x_col[var_idx] != -1){
            r.edge_id_.push_back(x.edge_id_[r_edge2x_col[var_idx]]);
        } else {
            r.edge_id_.push_back(INVALID_EDGE_ID);
        }
    }

    for(int var_idx = 0; var_idx < (int)r_val2x_col.size(); ++var_idx){
        if(r_val2x_col[var_idx] != -1){
            r.values_.emplace_back(x.values_[r_val2x_col[var_idx]]);
        } else {
            r.values_.emplace_back(GPStore::Value::NO_VALUE);
        }
    }

    for(int var_idx = 0; var_idx < (int)r_prop2x_col.size(); ++var_idx){
        if(r_prop2x_col[var_idx] != -1){
            r.values_.emplace_back(x.values_[r_prop2x_col[var_idx]]);
        } else {
            r.values_.emplace_back(GPStore::Value::NO_VALUE);
        }
    }
}
