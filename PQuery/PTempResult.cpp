#include "PTempResult.h"
#include "../Value/PCalculator.h"
#include <cassert>
#include <algorithm>

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
    spo_var_id2col_.clear();
    edge_var_id2col_.clear();
    value_var_id2col_.clear();
    var_propid2col_.clear();
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

void PTempResult::Header::setVarset(const std::vector<unsigned > & spo_var, const std::vector<unsigned > & edge_var,
               const std::vector<unsigned > & other_var,const std::vector<std::pair<unsigned,unsigned>> & prop) {
    spo_var_.vars = spo_var;
    edge_var_.vars = edge_var;
    other_var_.vars = other_var;
    prop_.vars = prop;
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
 * @param asc If Compare in ascending order
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
 * @brief compare two row on certain columns in ascending order.
 * @param x A row(record)
 * @param x_cols Columns to be compared of X
 * @param y Another row(record)
 * @param y_cols Columns to be compared of Y
 * @return 0 if equal; 1 if greater; -1 if less
 * @warning Element corresponding to x_cols[i] AND that corresponding to y_cols[i] must be comparable.
 * (i.e. Both of them are nodes, or edges, or values)
 */
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

/**
 * @brief Sort rows of a PTempResult table.
 * @param l Position of the first row of the table.
 * @param r Position of the last row of the table.
 * @param exps Order by the values of exps
 * @param asc Order by this_cols[i] ascending ?
 * @param _kvstore Pointer to KVStore
 * @param param Cypher Global Parameter
 * */
void PTempResult::sort(int l, int r, const std::vector<const GPStore::Expression *> & exps,
                       const std::vector<bool> &asc, KVstore * _kvstore,
                       const std::unordered_map<std::string, GPStore::Value> * params){
    auto this_cols = projectionView(exps, _kvstore, params);
    sort(l, r, this_cols, asc);
}



/**
 * @brief For a table that is sorted on certain columns, Find the first position of x
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

/**
 * @brief For a table that is sorted on certain columns, Find the last position of x
 * @param x
 * @param x_cols
 * @param this_cols
 * @return left bounder position if x was found, else -1
 */
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
 * @brief Evaluate an expression, store the value to the last column.
 * @param exp The expression to be evaluated
 * @param _kvstore KVStore
 * @param params Cypher Global parameters.
 * */
void PTempResult::extend(const GPStore::Expression * exp, KVstore * _kvstore,
                         const std::unordered_map<std::string, GPStore::Value> * params){

    int n = rows_.size();
    for(int i = 0; i < n; ++i) {
        rows_[i].values_.push_back(PCalculator::evaluateExpression(exp, rows_[i].spo_id_, head_.spo_var_id2col_,
                                                                   rows_[i].edge_id_, head_.edge_var_id2col_,
                                                                   rows_[i].values_, head_.value_var_id2col_,
                                                                   head_.var_propid2col_, params, _kvstore));
    }
    return;
}

/**
 * @brief Get column view of some expressions
 * @return column that store the value of exp[i]
 * */
std::vector<unsigned > PTempResult::projectionView(const std::vector<const GPStore::Expression *> & exps, KVstore * _kvstore,
                                      const std::unordered_map<std::string, GPStore::Value> * params){
    assert(!rows_.empty());
    int n = rows_[0].spo_id_.size(), m = rows_[0].edge_id_.size(), v = rows_[0].values_.size();
    std::vector<unsigned > cols;

    for(auto exp : exps){
        if(exp->isVariable()){
            unsigned var_id = exp->getVariableId();
            if(head_.spo_var_.findVar(var_id)){
                cols.push_back(head_.spo_var_id2col_.at(var_id));
            } else if(head_.edge_var_.findVar(var_id)){
                cols.push_back(n + head_.edge_var_id2col_.at(var_id));
            } else if(head_.other_var_.findVar(var_id)){
                cols.push_back(n + m + head_.value_var_id2col_.at(var_id));
            } else { assert(false);}
            continue;
        } else if(exp->isVariableProp()){
            unsigned var_id = exp->getVariableId();
            TYPE_PROPERTY_ID prop_id = exp->property_label_->prop_ids_[0];
            auto p = std::make_pair(var_id, prop_id);
            if(head_.prop_.findVar(p)){
                cols.push_back(n + m + head_.var_propid2col_.at(p));
                continue;
            }
        }
        cols.push_back(n + m + v);
        ++v;
        extend(exp, _kvstore, params);
    }

    return cols;
}


/**
 * @brief Join two tables on certain columns, and produce result to r.
 * @param x another table
 * @param r empty table to stream result to;Varset of r is initialized, whereas var2col is not.
 * @param x_cols x's column to be joined on
 * @param this_cols column to be joined
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
                r.rows_.emplace_back();
                generateRow(r.rows_.back(), this->rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col, r_edge2x_col,
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
                r.rows_.emplace_back();
                generateRow(r.rows_.back(), this->rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col, r_edge2x_col,
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
                r.rows_.emplace_back();
                generateRow(r.rows_.back(), this->rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col, r_edge2x_col,
                            r_val2this_col, r_val2x_col, r_prop2this_col, r_prop2x_col);
            }
        }
    }

    // this table is the outer table, x is inner.
    else {
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                generateRow(r.rows_.back(), this->rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col, r_edge2x_col,
                            r_val2this_col, r_val2x_col, r_prop2this_col, r_prop2x_col);
            }
        }
    }
    return;
}

/**
 * @brief Stream result to r.
 * @param r An empty table whose varsets are initialized
 */
void PTempResult::doUnion(PTempResult &r){
    auto r_spo2this_col = mapTo(r.head_.spo_var_, head_.spo_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, head_.edge_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, head_.value_var_id2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, head_.var_propid2col_);
    r.head_.initColumnInfoByVarset();
    for(int i = 0; i < (int)this->rows_.size(); ++i){
        r.rows_.emplace_back();
        generateRow(r.rows_.back(), this->rows_[i], r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
    }
    return;
}

/**
 * @brief Do left outer join
 * @param x another table
 * @param r An empty table to stream result to, whose varsets are initialized
 * @param x_cols Columns of x to join on.
 * @param this_cols Columns of this table
 */
void PTempResult::doLeftOuterJoin(PTempResult &x, PTempResult &r, const std::vector<unsigned >& x_cols,
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
            int rb = x.findRightBounder(rows_[i], this_cols, x_cols);
            for(int j = lb; j <= rb; ++j){
                r.rows_.emplace_back();
                generateRow(r.rows_.back(), rows_[i], x.rows_[j], r_spo2this_col, r_spo2x_col, r_edge2this_col,
                            r_edge2x_col, r_val2this_col, r_val2x_col, r_prop2this_col, r_prop2x_col);
            }
        }
    }
    return;
}

/**
 * @brief Select rows that evaluate filter to TRUE.
 */
void PTempResult::doFilter(PTempResult &r, const GPStore::Expression * filter, KVstore * _kvstore,
                           const std::unordered_map<std::string, GPStore::Value> * params){
    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);
    r.head_.initColumnInfoByVarset();
    for(auto &row : this->rows_){
        GPStore::Value val = PCalculator::evaluateExpression(filter, row.spo_id_, head_.spo_var_id2col_, row.edge_id_,
                                                             head_.edge_var_id2col_, row.values_, head_.value_var_id2col_,
                                                             head_.var_propid2col_, params, _kvstore);
        if(val.type_ == GPStore::Value::BOOLEAN && val.data_.Boolean){
            r.rows_.emplace_back();
            generateRow(r.rows_.back(), row, r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
        }
    }
}

/**
 * @brief Projection proj_exps[i] AS alias[i]. Besides, projection keep_vars[i] AS keep_vars[i]. Property Cache will remain.
 * @param proj_exps Expressions that are projected
 * @param alias Renamed column
 * @param keep_vars vars that dont drop
 * @param _kvstore KVstore
 * @param params Cypher Global Parameters
 */
void PTempResult::doProjection(const std::vector<const GPStore::Expression *> & proj_exps, const std::vector<unsigned > & alias,
                  const std::vector<unsigned > & keep_vars,
                  KVstore * _kvstore, const std::unordered_map<std::string, GPStore::Value> * params){
    auto allVarset = getAllVarset();
    int proj_num = proj_exps.size();
    int keep_num = keep_vars.size();
    if(allVarset.empty()){
        head_.other_var_ = alias;
        head_.initColumnInfoByVarset();
        rows_.emplace_back();
        for(auto & proj : proj_exps){
            rows_.back().values_.emplace_back(PCalculator::evaluateConstExpression(proj, params));
        }
        return;
    }
    else if(rows_.empty()){
        PVarset<unsigned> spo_, edge_, value_;
        PVarset<unsigned> keep = keep_vars;
        for(int i = 0; i < proj_num; ++i){
            if(proj_exps[i]->isVariable()){
                unsigned var_id = proj_exps[i]->getVariableId();
                if(head_.spo_var_.findVar(var_id)){
                    spo_.addVar(alias[i]);
                } else if(head_.edge_var_.findVar(var_id)){
                    edge_.addVar(alias[i]);
                } else if(head_.other_var_.findVar(var_id)){
                    value_.addVar(alias[i]);
                } else { assert(false);}
            } else
                value_.addVar(alias[i]);
        }
        head_.spo_var_ = spo_ + (head_.spo_var_ * keep);
        head_.edge_var_ = edge_ + (head_.edge_var_ * keep);
        head_.other_var_ = value_ + (head_.other_var_ * keep);
        head_.initColumnInfoByVarset();
    }
    /// both col and row of this table is not empty.
    /// Remember: We do lazy projection
    PVarset<unsigned > marked_col;  // already used col
    // ||-----keep vars------||-----proj vars-----||
    std::vector<int > spo_cols;
    std::vector<int > edge_cols;
    std::vector<int > val_cols;
    int n = rows_[0].spo_id_.size(), m = rows_[0].edge_id_.size();
    for(auto & var : keep_vars){
        spo_cols.push_back(-1);
        edge_cols.push_back(-1);
        val_cols.push_back(-1);

        if(head_.spo_var_.findVar(var)){
            unsigned spo_col = head_.spo_var_id2col_.at(var);
            if(marked_col.findVar(spo_col)){
                spo_cols.back() = rows_[0].spo_id_.size();
                copyColumn(spo_col, 0);
            } else {
                marked_col.addVar(spo_col);
                spo_cols.back() = spo_col;
            }

        } else if(head_.edge_var_.findVar(var)){
            unsigned edge_col = head_.edge_var_id2col_.at(var);
            if(marked_col.findVar(edge_col + n)){
                edge_cols.back() = rows_[0].edge_id_.size();
                copyColumn(edge_col, 1);
            } else {
                marked_col.addVar(n + edge_col);
                edge_cols.back() = edge_col;
            }
        } else if(head_.other_var_.findVar(var)){
            unsigned val_col = head_.value_var_id2col_.at(var);
            if(marked_col.findVar(n + m + val_col)){
                val_cols.back() = rows_[0].values_.size();
                copyColumn(val_col, 2);
            } else {
                marked_col.addVar(n + m + val_col);
                val_cols.back() = val_col;
            }
        } else { assert(false);}

    }

    for(int i = 0; i < proj_num; ++i){
        const GPStore::Expression* proj = proj_exps[i];
        spo_cols.push_back(-1);
        edge_cols.push_back(-1);
        val_cols.push_back(-1);
        if(proj->isVariable()){
            unsigned var = proj->getVariableId();
            if(head_.spo_var_.findVar(var)){
                unsigned spo_col = head_.spo_var_id2col_.at(var);
                if(marked_col.findVar(spo_col)){
                    spo_cols.back() = rows_[0].spo_id_.size();
                    copyColumn(spo_col, 0);
                } else {
                    marked_col.addVar(spo_col);
                    spo_cols.back() = spo_col;
                }

            } else if(head_.edge_var_.findVar(var)){
                unsigned edge_col = head_.edge_var_id2col_.at(var);
                if(marked_col.findVar(edge_col + n)){
                    edge_cols.back() = rows_[0].edge_id_.size();
                    copyColumn(edge_col, 1);
                } else {
                    marked_col.addVar(n + edge_col);
                    edge_cols.back() = edge_col;
                }
            } else if(head_.other_var_.findVar(var)){
                unsigned val_col = head_.value_var_id2col_.at(var);
                if(marked_col.findVar(n + m + val_col)){
                    val_cols.back() = rows_[0].values_.size();
                    copyColumn(val_col, 2);
                } else {
                    marked_col.addVar(n + m + val_col);
                    val_cols.back() = val_col;
                }
            } else { assert(false);}
            /// Deal with Property
            PVarset<std::pair<unsigned ,TYPE_PROPERTY_ID>> var_prop;
            for(auto & p : head_.prop_.vars){
                if(p.first == var){
                    auto new_pair = std::make_pair(alias[i], p.second);
                    unsigned old_col = head_.var_propid2col_.at(p);
                    p.first = new_pair.first;
                    head_.var_propid2col_.erase(p);
                    head_.var_propid2col_.insert(std::make_pair(new_pair, old_col));
                }
            }
            continue;
        }

        val_cols.back() = rows_[0].values_.size();
        extend(proj, _kvstore, params);
    }
    // spo, edge, val, prop
    std::map<unsigned,unsigned> spo2col;
    std::map<unsigned,unsigned> edge2col;
    std::map<unsigned,unsigned> val2col;

    PVarset<std::pair<unsigned, TYPE_PROPERTY_ID>> props;
    head_.spo_var_.vars.clear();
    head_.edge_var_.vars.clear();
    head_.other_var_.vars.clear();
    for(int i = 0; i < keep_num + proj_num; ++i){
        if(spo_cols[i] != -1){
            if(i < keep_num){
                head_.spo_var_.addVar(keep_vars[i]);
                spo2col.insert(std::make_pair(keep_vars[i], spo_cols[i]));
            } else {
                head_.spo_var_.addVar(alias[i - keep_num]);
                spo2col.insert(std::make_pair(alias[i - keep_num], spo_cols[i]));
            }
        } else if(edge_cols[i] != -1){
            if(i < keep_num){
                head_.edge_var_.addVar(keep_vars[i]);
                edge2col.insert(std::make_pair(keep_vars[i], edge_cols[i]));
            } else {
                head_.edge_var_.addVar(alias[i - keep_num]);
                edge2col.insert(std::make_pair(alias[i - keep_num], edge_cols[i]));
            }

        } else if(val_cols[i] != -1){
            if(i < keep_num){
                head_.other_var_.addVar(keep_vars[i]);
                val2col.insert(std::make_pair(keep_vars[i], val_cols[i]));
            } else {
                head_.other_var_.addVar(alias[i - keep_num]);
                val2col.insert(std::make_pair(alias[i - keep_num], val_cols[i]));
            }
        } else {
            assert(false);
        }
    }

    head_.spo_var_id2col_.swap(spo2col);
    head_.edge_var_id2col_.swap(edge2col);
    head_.value_var_id2col_.swap(val2col);

    for(auto & p : head_.prop_.vars){
        if(head_.spo_var_.findVar(p.first) || head_.edge_var_.findVar(p.first) || head_.other_var_.findVar(p.first)){
            props.addVar(p);
        } else {
            head_.var_propid2col_.erase(p);
        }
    }
    head_.prop_ = props;
}


/**
 * @brief Remove duplicated rows on certain cols.
 * @param r Empty table to stream result to, whose PVarsets are initialized.
 * @param dis_cols Columns to perform DISTINCT
 * @param already_order Columns that are already ordered.
 */
void PTempResult::doDistinct(PTempResult &r, const std::vector<unsigned > & dis_cols, const std::vector<unsigned > already_order){
    // TODO: Grouping By the already sorted columns, and perform DISTINCT in each group.
    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);
    r.head_.initColumnInfoByVarset();

    int n = rows_.size();
    sort(0, n - 1, dis_cols);
    int i = 0, j = 0;
    while(i < n){
        j = i + 1;
        while(j < n && compareRow(rows_[i],dis_cols, rows_[j], dis_cols) != 0)
            ++j;
        r.rows_.emplace_back();
        generateRow(r.rows_.back(), rows_[i], r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
        i = j;
    }
}

/**
 * @brief For Cypher Unwind clause.
 */
void PTempResult::doUnwind(PTempResult &r, const GPStore::Expression * exp,  unsigned var_id, KVstore * _kvstore,
              const std::unordered_map<std::string, GPStore::Value> * params){

    if(getAllVarset().empty()){
        r.head_.other_var_.vars.clear();
        r.head_.other_var_.addVar(var_id);
        r.head_.value_var_id2col_[var_id] = 0;
        GPStore::Value val = PCalculator::evaluateConstExpression(exp, params);
        if(val.type_ == GPStore::Value::LIST){
            for(int i = 0; i < val.data_.List->size(); ++i){
                r.rows_.emplace_back();
                r.rows_.back().values_.emplace_back(*val.data_.List->at(i));
            }
        } else {
            r.rows_.emplace_back();
            r.rows_.back().values_.emplace_back(val);
        }
        return;
    }

    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);
    r.head_.initColumnInfoByVarset();

    int n = rows_.size();
    for(int i = 0; i < n; ++i){
        GPStore::Value val = PCalculator::evaluateExpression(exp, rows_[i].spo_id_, head_.spo_var_id2col_,rows_[i].edge_id_,
                                                             head_.edge_var_id2col_, rows_[i].values_, head_.value_var_id2col_,
                                                             head_.var_propid2col_, params, _kvstore);
        if(val.type_ != GPStore::Value::LIST){
            r.rows_.emplace_back();
            generateRow(r.rows_.back(), rows_[i], r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
            r.rows_.back().values_[r.head_.value_var_id2col_.at(var_id)] = val;
        } else {
            int ls_size = val.data_.List->size();
            for(int j = 0; j < ls_size; ++j){
                r.rows_.emplace_back();
                generateRow(r.rows_.back(), rows_[i], r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
                r.rows_.back().values_[r.head_.value_var_id2col_.at(var_id)] =*(val.data_.List->at(j));
            }
        }

    }

}

void PTempResult::doAggregation(PTempResult &r, const std::vector<unsigned > & groups, const std::vector<const GPStore::Expression *> & aggr_val,
                   std::vector<unsigned > aggr_id,  KVstore * _kvstore,
                   const std::unordered_map<std::string, GPStore::Value> * params){
    if(rows_.empty()) {
        // TODO: 边界情况
    }
    int n = rows_.size();
    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);
    r.head_.initColumnInfoByVarset();
    /**
     * Invoke: EvaluateAggregationValue; store the value to atom::FunctionInvo::value.
     * Then, call regular EvaluateExpression, will read the value in atom::FunctionInvo::value.
     * */
     int num_group = groups.size();
     std::vector<std::unique_ptr<GPStore::Expression>> copy_exp;
     for(auto & aggr : aggr_val) copy_exp.emplace_back(new GPStore::Expression(*aggr));
     for(int i = 0; i < num_group; ++i){
         int lb = groups[i], lr = (i == num_group - 1 ? n : groups[i + 1]);
         r.rows_.emplace_back();
         generateRow(r.rows_.back(), rows_[lb], r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
         std::vector<GPStore::Value> values;
         for(int j = 0; j < copy_exp.size(); ++j){
             evaluateAggregationExpression(copy_exp[i].get(), lb , lr, _kvstore, params);
             r.rows_.back().values_[r.head_.value_var_id2col_.at(aggr_id[j])] =PCalculator::evaluateExpression(copy_exp[i].get(), rows_[lb].spo_id_, head_.spo_var_id2col_,
                                                                 rows_[lb].edge_id_, head_.edge_var_id2col_, rows_[lb].values_,
                                                                 head_.value_var_id2col_, head_.var_propid2col_, params,
                                                                 _kvstore);
         }


     }

}


void PTempResult::doLimit(PTempResult &r, unsigned limit, unsigned skip){
    auto r_spo2this_col = mapTo(r.head_.spo_var_, this->head_.spo_var_id2col_);
    auto r_edge2this_col = mapTo(r.head_.edge_var_, this->head_.edge_var_id2col_);
    auto r_val2this_col = mapTo(r.head_.other_var_, this->head_.value_var_id2col_);
    auto r_prop2this_col = mapTo(r.head_.prop_, this->head_.var_propid2col_);
    r.head_.initColumnInfoByVarset();
    unsigned n = rows_.size();
    unsigned start_pos = skip, end_pos = limit == INVALID ? n : (skip + limit >  n ? n : skip + limit);
    for(unsigned i = start_pos; i < end_pos; ++i){
        r.rows_.emplace_back();
        generateRow(r.rows_.back(), this->rows_[i], r_spo2this_col, r_edge2this_col, r_val2this_col, r_prop2this_col);
    }
}

/**
 * @brief Group the rows by grouping keys
 * @param grouping_keys Grouping keys (variable name).
 * @return The position of first row in each group.
 */
std::vector<unsigned > PTempResult::doGroupBy(const std::vector<unsigned > & grouping_keys){
    unsigned n = (unsigned)rows_.size();
    if(n == 0) return { };
    if(n == 1) return {0U};
    std::vector<unsigned > grouping_cols;
    for(auto & var : grouping_keys){
        if(head_.spo_var_.findVar(var)){
            grouping_cols.push_back(head_.spo_var_id2col_.at(var));
        } else if(head_.edge_var_.findVar(var)){
            grouping_cols.push_back(head_.edge_var_id2col_.at(var));
        } else {
            grouping_cols.push_back(head_.value_var_id2col_.at(var));
        }
    }
    std::vector<unsigned > groups;
    sort(0, n - 1, grouping_cols);
    unsigned i = 0, j = 0;
    while(i < n){
        groups.push_back(i);
        j = i + 1;
        while(j < n && compareRow(rows_[i], grouping_cols, rows_[j], grouping_cols) == 0)
            ++j;
        i = j;
    }
    return groups;
}

/// helper functions

/**
 * @brief Get a map From index of varset To column id of another table.
 * @param from The varset
 * @param id2col The var id to col id map
 * */
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

/**
 * @brief Get a map From index of varset To column id of another table.
 * @param from The varset
 * @param id2col The var id to col id map
 * */
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

/**
 * @brief Generate a new row r from record x and record y
 * @param r New row that will be filled
 * @param x A record
 * @param y Another record
 * @param r_spo2x_col A map from SPO column of r to that of x
 * @param r_spo2y_col A map from SPO column of r to that of y
 * @param r_edge2x_col A map from Edge column of r to that of x
 * @param r_edge2y_col A map from Edge column of r to that of y
 * @param r_val2x_col A map from Value column of r to that of x
 * @param r_val2y_col A map from Value column of r to that of y
 * @param r_prop2x_col A map from Prop column of r to column of Value Table of x
 * @param r_prop2y_col A map from Prop column of r to column of Value Table of x
 * */
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

/**
 * @brief Copy a particular column.
 * @param col_id Id of the column.
 * @param part_num 0: SPO 1 : EDGE 2 : VALUE
 * */
void PTempResult::copyColumn(unsigned col_id, unsigned part_num){
    if(part_num == 0){
        for(auto & r : rows_){
            r.spo_id_.push_back(r.spo_id_[col_id]);
        }
    } else if(part_num == 1){
        for(auto & r : rows_){
            r.edge_id_.push_back(r.edge_id_[col_id]);
        }
    } else if(part_num == 2){
        for(auto & r : rows_){
            r.values_.emplace_back(r.values_[col_id]);
        }
    }
}

/**
 * @brief Evaluate an aggregation value, store it in FunctionInvocation::val
 * */
void PTempResult::evaluateAggregationExpression(GPStore::Expression *exp, int _begin, int _end, KVstore * _kvstore,
                                                const std::unordered_map<std::string, GPStore::Value> * params){
    if(exp->isAtom()){
        evaluateAggregationExpression(exp->atom_, _begin, _end, _kvstore, params);
    }
    else {
        for(auto child : exp->children_){
            if(child != nullptr)
                evaluateAggregationExpression(child, _begin, _end, _kvstore, params);
        }
    }
}

/**
 * @brief Evaluate an aggregation value, store it in FunctionInvocation::val
 * */
void PTempResult::evaluateAggregationExpression(GPStore::Atom *atom, int _begin, int _end, KVstore * _kvstore,
                                                const std::unordered_map<std::string, GPStore::Value> * params){
    auto atom_ty = atom->atom_type_;
    if(atom_ty == GPStore::Atom::LITERAL){
        GPStore::Literal *lit = dynamic_cast<GPStore::Literal*>(atom);
        if(lit->literal_type_ == GPStore::Literal::LIST_LITERAL){
            for(auto exp : lit->list_literal_){
                evaluateAggregationExpression(exp, _begin, _end, _kvstore, params);
            }
        } else if(lit->literal_type_ == GPStore::Literal::MAP_LITERAL){
            for(auto &p : lit->map_literal_){
                evaluateAggregationExpression(p.second,_begin, _end, _kvstore, params);
            }
        }
    }
    else if(atom_ty == GPStore::Atom::PARAMETER){

    }
    else if(atom_ty == GPStore::Atom::CASE_EXPRESSION){
        GPStore::CaseExpression *case_exp = dynamic_cast<GPStore::CaseExpression*>(atom);
        if(case_exp->test_exp_ != nullptr){
            evaluateAggregationExpression(case_exp->test_exp_, _begin, _end, _kvstore, params);
        }
        for(auto when : case_exp->when_exps_){
            evaluateAggregationExpression(when, _begin, _end, _kvstore, params);
        }
        for(auto then : case_exp->when_exps_){
            evaluateAggregationExpression(then, _begin, _end, _kvstore, params);
        }
        if(case_exp->else_exp_ != nullptr){
            evaluateAggregationExpression(case_exp->else_exp_, _begin, _end, _kvstore, params);
        }
    }
    else if(atom_ty == GPStore::Atom::COUNT){
        GPStore::Count *cnt = dynamic_cast<GPStore::Count*>(atom);
        // Please do aggregation here.
    }
    else if(atom_ty == GPStore::Atom::LIST_COMPREHENSION){
        GPStore::ListComprehension *lc = dynamic_cast<GPStore::ListComprehension*>(atom);
        if(lc->exp_ != nullptr){
            evaluateAggregationExpression(lc->exp_, _begin, _end, _kvstore, params);
        }
        if(lc->filter_ != nullptr){
            evaluateAggregationExpression(lc->filter_, _begin, _end, _kvstore, params);
        }
        if(lc->trans_ != nullptr){
            evaluateAggregationExpression(lc->trans_, _begin , _end, _kvstore, params);
        }
    }
    else if(atom_ty == GPStore::Atom::PATTERN_COMPREHENSION){

    }
    else if(atom_ty == GPStore::Atom::QUANTIFIER){

    }
    else if(atom_ty == GPStore::Atom::PATTERN_PREDICATE){

    }
    else if(atom_ty == GPStore::Atom::FUNCTION_INVOCATION){
        GPStore::FunctionInvocation *func = dynamic_cast<GPStore::FunctionInvocation*>(atom);
        if(func->isAggregationFunction()){
            evaluateAggregationFunction(func,  _begin, _end, _kvstore, params);
        } else {
            for(auto arg : func->args){
                evaluateAggregationExpression(arg, _begin, _end, _kvstore, params);
            }
        }
    }
    else if(atom_ty == GPStore::Atom::EXISTENTIAL_SUBQUERY){

    }
    else if(atom_ty == GPStore::Atom::VARIABLE){

    }
    else if(atom_ty == GPStore::Atom::PARENTHESIZED_EXPRESSION){
        GPStore::ParenthesizedExpression * par_exp = dynamic_cast<GPStore::ParenthesizedExpression*>(atom);
        if(par_exp->exp_ != nullptr)
            evaluateAggregationExpression(par_exp->exp_, _begin, _end, _kvstore, params);
    }
}

/**
 * @brief Evaluate an aggregation function, store value in FunctionInvocation::val
 * */
void
PTempResult::evaluateAggregationFunction(GPStore::FunctionInvocation *func, int _begin, int _end, KVstore * _kvstore,
                                         const std::unordered_map<std::string, GPStore::Value> * params){
    assert(func->isAggregationFunction());
    func->val_.Destruct();
    std::string str = func->func_name_[0];
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::vector<GPStore::Value> values;
    for(int i = _begin; i < _end; ++i){
        values.emplace_back(PCalculator::evaluateExpression(func->args[0], rows_[i].spo_id_, head_.spo_var_id2col_,
                                                            rows_[i].edge_id_, head_.edge_var_id2col_, rows_[i].values_,
                                                            head_.value_var_id2col_, head_.var_propid2col_, params, _kvstore ));

    }
    if(values.empty()){
        func->val_ = GPStore::Value::NO_VALUE;
        return;
    }
    if(func->distinct){
        removeDuplicate(values);
    }
    if(str == "avg"){
        bool bad = false, have_num = false;
        GPStore::Value val(GPStore::Value::FLOAT);
        val.data_.Float = 0;
        int cnt = 0;
        for(auto & v : values){
            if(v.isNumber()){
                have_num = true;
            }
            if(v.type_ != GPStore::Value::NO_VALUE && !v.isNumber()) {
                bad = true;
                break;
            }

        }
        if(bad){
            func->val_ = GPStore::Value::ERROR_VALUE;
            return;
        }
        if(!have_num){
            func->val_ = GPStore::Value::NO_VALUE;
            return;
        }
        for(auto & v : values){
            if(v.type_ == GPStore::Value::NO_VALUE)continue;
            ++cnt;
            if(v.type_ == GPStore::Value::FLOAT){
                val.data_.Float += v.data_.Float;
            } else {
                val.data_.Float += v.data_.Int;
            }
        }
        val.data_.Float /= (double)cnt;
        func->val_ =  val;
    }
    else if(str == "collect"){
        func->val_.type_ = GPStore::Value::LIST;
        func->val_.data_.List = new std::vector<GPStore::Value*>;
        for(auto &v :values){
            if(v.type_ != GPStore::Value::NO_VALUE)
                func->val_.data_.List->push_back(new GPStore::Value(v));
        }
        return;
    }
    else if(str == "count"){
        func->val_.type_ = GPStore::Value::INTEGER;

        int cnt = 0;
        for(auto & v : values)
            cnt += (int)(v.type_!=GPStore::Value::NO_VALUE);
        func->val_.data_.Int = cnt;
    }
    else if(str == "max"){
        int i = 0;
        for(; i < values.size(); ++i){
            if(values[i].type_ != GPStore::Value::NO_VALUE){
                break;
            }
        }
        if(i >= values.size()){
            func->val_= GPStore::Value::NO_VALUE;
            return;
        }
        for(int j = i + 1; j < values.size(); ++j){
            if(values[j].type_ != GPStore::Value::NO_VALUE && values[i].comp(values[j]) == -1)
                i = j;
        }
        func->val_ = values[i];
    }
    else if(str == "min"){
        int i = 0;
        for(; i < values.size(); ++i){
            if(values[i].type_ != GPStore::Value::NO_VALUE){
                break;
            }
        }
        if(i >= values.size()){
            func->val_= GPStore::Value::NO_VALUE;
            return;
        }
        for(int j = i + 1; j < values.size(); ++j){
            if(values[j].type_ != GPStore::Value::NO_VALUE && values[i].comp(values[j]) == 1)
                i = j;
        }
        func->val_ = values[i];
    }
    else if(str == "percentilecont"){
        throw std::runtime_error("[ERROR] Aggregation function percentileCont not implemented.");
    }
    else if(str == "percentiledisc"){
        throw std::runtime_error("[ERROR] Aggregation function percentileDisc not implemented.");
    }
    else if(str == "stdev"){
        throw std::runtime_error("[ERROR] Aggregation function stdev not implemented.");
    }
    else if(str == "stdevp"){
        throw std::runtime_error("[ERROR] Aggregation function stdevp not implemented.");
    }
    else if(str == "sum"){
        bool bad = false, have_float = false, have_num = false;
        GPStore::Value val(GPStore::Value::INTEGER);
        val.data_.Int = 0;

        for(auto & v : values){
            if(v.type_ == GPStore::Value::FLOAT)have_float = true;
            if(v.isNumber()) have_num = true;
            if(v.type_ != GPStore::Value::NO_VALUE && !v.isNumber()) {
                bad = true;
                break;
            }
        }
        if(bad){
            func->val_ = GPStore::Value::ERROR_VALUE;
            return;
        }
        if(!have_num) {
            func->val_ = GPStore::Value::NO_VALUE;
            return;
        }
        if(have_float){
            val.type_ = GPStore::Value::FLOAT;
            val.data_.Float = 0;
        }
        for(auto & v : values){
            if(v.type_ == GPStore::Value::NO_VALUE) continue;
            if(v.type_ == GPStore::Value::FLOAT){
                val.data_.Float += v.data_.Float;
            } else {
                if(val.type_ == GPStore::Value::INTEGER){
                    val.data_.Int += v.data_.Int;
                } else {
                    val.data_.Float += v.data_.Int;
                }
            }
        }
        func->val_ = val;
    }

}

void PTempResult::removeDuplicate(std::vector<GPStore::Value> & values){
    std::vector<GPStore::Value> new_values;
    std::vector<const GPStore::Value *> vec;
    for(auto & v : values){
        vec.push_back(&v);
    }
    std::sort(vec.begin(), vec.end(), [](const GPStore::Value *a, const GPStore::Value* b){return *a < *b; });
    int i = 0, n = values.size(), j = 0;
    while(i < n){
        new_values.emplace_back(*vec[i]);
        j = i + 1;
        while(j < n && vec[j]->comp(*vec[i]) == 0)
            j ++;
        i = j;
    }
    values.swap(new_values);
}