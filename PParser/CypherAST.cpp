#include "CypherAST.h"
#include <cassert>

void CypherAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "CypherAST");
    if(single_querys_.size())
        single_querys_[0]->print(dep + 1);
    for(int i = 0; i < union_all_.size(); ++i){
        GPStore::Expression::printHead(dep + 1,union_all_[i] ? "UNION ALL" : "UNION", false);
        single_querys_[i + 1]->print(dep + 1);
    }
}

void SingleQueryAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "SingleQueryAST");
    for(auto &query_unit : query_units_){
        query_unit->print(dep + 1);
    }
}

void QueryUnitAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "QueryUnitAST");
    for(auto &r : reading_){
        r->print(dep + 1);
    }
    for(auto &u : updating_){
        u->print(dep + 1);
    }
    if(with_return_ != nullptr){
        with_return_->print(dep + 1);
    }
}

void MatchAST::print(int dep) const{
    GPStore::Expression::printHead(dep, is_optional_ ? "OptionalMatch" : "Match");
    for(auto &pat : pattern_)
        pat.print();
    if(where_ != nullptr){
        GPStore::Expression::printHead(dep + 1, "Where");
        where_->print(dep + 2);
    }
}

void UnwindAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "UnwindAST");
    exp_->print(dep + 1);
    GPStore::Expression::printHead(dep + 1, "AS ", false, false);
    printf("%s\n", var_name_.c_str());
}

void InQueryCallAST::print(int dep) const{
    assert(false);
    return;
}

void CreateAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "CreateAST");
    for(auto& pat : pattern_){
        pat.print();
    }
}

void MergeAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "MergeAST");
    rigid_pattern_.print();
    unsigned n = set_actions_.size();
    for(unsigned i = 0; i < n; ++i){
        if(is_on_match_[i]){
            GPStore::Expression::printHead(dep + 1, "ON MATCH", false, true);
        }else{
            GPStore::Expression::printHead(dep + 1, "ON CREATE", false, true);
        }
        set_actions_[i]->print(dep + 1);
    }
}

void DeleteAST::print(int dep) const{
    GPStore::Expression::printHead(dep, detach ? "Detach Delete" : "Delete");
    for(auto &e : exp_){
        e->print(dep + 1);
    }
}

void SetAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "SetAST");
    for(auto &s : set_items_){
        s->print(dep + 1);
    }
}

void RemoveAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "RemoveAST");
    for(auto &r : remove_items_){
        r->print(dep + 1);
    }
}   

void WithReturnAST::print(int dep) const{
    GPStore::Expression::printHead(dep, with_ ? "WITH" : "RETURN");
  
    // print Projection_exp
    if(proj_exp_.size()){
        GPStore::Expression::printHead(dep + 1, "ProjectionItems");
        for(int i = 0; i < proj_exp_.size(); ++i){
            proj_exp_[i]->print(dep + 2);
            if(var_name_[i] != ""){
                GPStore::Expression::printHead(dep + 2, "AS ", false, false);
                printf("%s\n",var_name_[i].c_str());
            }
        }
    }
    // where
    if(where_ != nullptr){
        GPStore::Expression::printHead(dep + 1, "Where");
        where_->print(dep + 2);
    }
    // order by
    if(order_by_.size()){
        GPStore::Expression::printHead(dep + 1, "Order By");
        for(int i = 0; i < order_by_.size() - 1; ++i){
            order_by_[i]->print(dep + 2);
            GPStore::Expression::printHead(dep + 2, ascending_[i] ? "ASC," : "DEC,", false);
        }
        order_by_.back()->print(dep + 2);
        GPStore::Expression::printHead(dep + 2, ascending_.back() ? "ASC" : "DEC", false);
    }
    // limit
    if(limit_){
        GPStore::Expression::printHead(dep + 1, "Limit");
        limit_->print(dep + 2);
    }
    // skip
    if(skip_){
        GPStore::Expression::printHead(dep + 1, "Skip");
        skip_->print(dep + 2);
    }
}

void SetItemAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "SetItemAST");
    switch (set_type_){
        case PROPERTY_EXP:
            prop_exp_->print(dep + 1);
            GPStore::Expression::printHead(dep + 1, "=",false);
            rval_->print(dep + 1);
            break;
        case NODE_LABEL:
            GPStore::Expression::printHead(dep + 1, var_name_.c_str(),false,false);
            for(auto &l : rlabels_){
                printf(":%s", l.c_str());
            }
            putchar('\n');
            break;
        default:
            GPStore::Expression::printHead(dep + 1, var_name_.c_str());
            GPStore::Expression::printHead(dep + 1, VAR_ASSIGN ? "=" : "+=");
            rval_->print(dep + 1);
            break;
    }
}

void RemoveItemAST::print(int dep) const{
    GPStore::Expression::printHead(dep, "RemoveItemAST");
    if(labels_.size() != 0){
        GPStore::Expression::printHead(dep + 1, var_name_.c_str(), false,false);
        for(auto &l : labels_){
            printf(":%s",l.c_str());
        }
        putchar('\n');
    }else{
        prop_exp_->print(dep + 1);
    }
}