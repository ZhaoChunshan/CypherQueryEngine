#ifndef PPARSER_CYPHERAST_H
#define PPARSER_CYPHERAST_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "Pattern.h"


// CypherAST
class CypherAST;
class SingleQueryAST;
class QueryUnitAST;

// clauses
class ReadingAST;
class UpdatingAST;

// reading clauses
class MatchAST;
class UnwindAST;
class InQueryCallAST;

// Updating clauses
class CreateAST;
class MergeAST;
class DeleteAST;
class SetAST;
class RemoveAST;

// Return, With Clause
class WithReturnAST;

// Aux Class
class SetItemAST;
class RemoveItemAST;



class CypherAST{
public:
    std::vector<std::unique_ptr<SingleQueryAST>> single_querys_;
    std::vector<bool> union_all_;
    std::vector<std::string> id2var_name_;
    std::unordered_map<std::string, unsigned> prop2id_;
    std::map<unsigned, std::string> prop_id2string_;
    CypherAST() = default;
    ~CypherAST() = default;
    void print(int dep) const;
};

class SingleQueryAST{
public:
    std::vector<std::unique_ptr<QueryUnitAST>> query_units_;
    SingleQueryAST() = default;
    ~SingleQueryAST() = default;
    void print(int dep) const;
};

/* 多部分串接查询的一个单元，依次是Reading, Updating, With/Return/无 */
class QueryUnitAST{
public:
    std::vector<std::unique_ptr<ReadingAST>> reading_;
    std::vector<std::unique_ptr<UpdatingAST>> updating_;
    std::unique_ptr<WithReturnAST> with_return_;
    QueryUnitAST() = default;
    ~QueryUnitAST() = default;
    void print(int dep) const;
};

class ReadingAST{
public:
    enum ReadingForm{MATCH, UNWIND, INQUERY_CALL};
    ReadingForm reading_form_;
    ReadingAST() = default;
    virtual ~ReadingAST(){ }
    virtual void print(int dep) const = 0;
};

class UpdatingAST{
public:
    enum UpdatingForm{CREATE, MERGE, DELETE, SET, REMOVE};
    UpdatingForm updating_form_;
    UpdatingAST() = default;
    virtual ~UpdatingAST() { };
    virtual void print(int dep) const = 0;
};

/**
 * ALL Reading Clauses
*/

class MatchAST: public ReadingAST{
public:
    bool is_optional_;
    std::vector<GPStore::RigidPattern> pattern_;
    std::unique_ptr<GPStore::Expression> where_;
    
    MatchAST(){ reading_form_ = MATCH; }
    ~MatchAST() = default;
    void print(int dep) const override;
};

class UnwindAST: public ReadingAST{
public:
    std::unique_ptr<GPStore::Expression> exp_;
    std::string var_name_;
    unsigned var_id_;
    UnwindAST(){ reading_form_ = UNWIND; };
    ~UnwindAST() = default;
    void print(int dep) const override;
};

class InQueryCallAST: public ReadingAST{
public:
    bool asterisk_;
    // 名字空间依次用'.'分割，如db.labels
    std::vector<std::string> procedure_name_; 
    // 显式的过程调用需要括号内指定参数
    std::vector<std::unique_ptr<GPStore::Expression>> args_;
    // 返回的列
    std::vector<std::string> yield_items;
    // 与yield_items一一对应，为空则无别名
    std::vector<std::string> alias; 

    std::vector<std::string> yield_var_;   // 原名或别名
    std::vector<unsigned> yield_var_id_;    // 原名或别名的id
    std::unique_ptr<GPStore::Expression> where_;
    
    InQueryCallAST(){reading_form_ = INQUERY_CALL;}
    ~InQueryCallAST()= default;
    
    void print(int dep) const override;
};

/**
 * ALL Updating Clauses
*/

class CreateAST: public UpdatingAST{
public:
    std::vector<GPStore::RigidPattern> pattern_;
    CreateAST() {updating_form_ = CREATE;}
    ~CreateAST()= default;
    void print(int dep) const override;
};

class MergeAST: public UpdatingAST{
public:
    GPStore::RigidPattern rigid_pattern_;
    std::vector<bool> is_on_match_;
    std::vector<std::unique_ptr<SetAST>> set_actions_;
    MergeAST(){updating_form_ = MERGE;}
    ~MergeAST()= default;
    void print(int dep) const override;
};

class DeleteAST: public UpdatingAST{
public:
    bool detach;
    std::vector<std::unique_ptr<GPStore::Expression>> exp_;
    DeleteAST(){updating_form_ = DELETE;}
    ~DeleteAST()= default;
    void print(int dep) const override;
};

class SetAST: public UpdatingAST{
public:
    std::vector<std::unique_ptr<SetItemAST>> set_items_;
    SetAST(){updating_form_ = SET;}
    ~SetAST()= default;
    void print(int dep) const override;
};


class RemoveAST: public UpdatingAST{
public:
    std::vector<std::unique_ptr<RemoveItemAST> > remove_items_;
    RemoveAST(){updating_form_ = REMOVE;};
    ~RemoveAST()= default;
    void print(int dep) const override;
};


class WithReturnAST{
public:
    bool with_;    // true: with false: return
    bool distinct_;
    bool asterisk_;
    bool aggregation_;  // does projection contain aggr function ?
    std::vector<std::unique_ptr<GPStore::Expression>> proj_exp_;
    std::vector<std::string> proj_exp_text_;    // 存放表达式文本，匿名的RETURN的表达式，以此为列名
    std::vector<std::string> alias_;            // 重命名，为""则无名
    std::vector<std::string> column_name_;      // 最终名字
    std::vector<unsigned> column_var_id_;       // id化的column_name
    // 如果是星星*，则涵盖了符号表中已有，而column_var_id_未投影的；如果不是星星，则是指
    // Orderby中用到的，而column_var_id_没投影的。
    std::vector<unsigned> implict_proj_var_id_; 

    std::unique_ptr<GPStore::Expression> skip_; 
    std::unique_ptr<GPStore::Expression> limit_;
    std::vector<std::unique_ptr<GPStore::Expression>> order_by_;    // 排序的变量名
    std::vector<bool> ascending_;    // 是否升序
    std::unique_ptr<GPStore::Expression> where_;
    WithReturnAST()= default;
    ~WithReturnAST()= default;
    void print(int dep) const;
};

/**
 * Auxiliary class for updating clauses
*/

class SetItemAST{
public:
    /**
     * oC_SetItem
       :  ( oC_PropertyExpression SP? '=' SP? oC_Expression )
           | ( oC_Variable SP? '=' SP? oC_Expression )
           | ( oC_Variable SP? '+=' SP? oC_Expression )
           | ( oC_Variable SP? oC_NodeLabels )
           ;
    */
    enum SetType{PROPERTY_EXP, NODE_LABEL, VAR_ASSIGN, VAR_ADD};
    SetType set_type_;
    std::unique_ptr<GPStore::Expression> prop_exp_;
    std::string var_name_;
    std::unique_ptr<GPStore::Expression> rval_;
    std::vector<std::string> rlabels_;
    SetItemAST() = default;
    ~SetItemAST() = default;
    void print(int dep) const;
};

class RemoveItemAST{
public:
    // 如果是删除标签，只用到variable_name,label_names
    // 如果是删除属性，只用到ProperyExpression
    std::string var_name_;
    std::vector<std::string> labels_;
    std::unique_ptr<GPStore::Expression> prop_exp_;
    RemoveItemAST()= default;
    ~RemoveItemAST()= default;
    void print(int dep) const;
};

#endif