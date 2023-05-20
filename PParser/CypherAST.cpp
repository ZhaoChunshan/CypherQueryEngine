#include "CypherAST.h"
#include <cassert>
#include <iostream>
#include <cstdio>
// helper function for print.
void printHead(int dep, const char *name, bool colon = true, bool endline = true){
    for(int i = 0; i < dep; ++i) std::printf("\t");
    std::printf(name);
    colon ? std::putchar(':') : 0;
    endline ? std::putchar('\n') : 0;
}

void CypherAST::print(int dep) const{
    printHead(dep, "CypherAST");
    if(single_querys_.size())
        single_querys_[0]->print(dep + 1);
    for(int i = 0; i < union_all_.size(); ++i){
        printHead(dep + 1,union_all_[i] ? "UNION ALL" : "UNION", false);
        single_querys_[i + 1]->print(dep + 1);
    }
}

void SingleQueryAST::print(int dep) const{
    printHead(dep, "SingleQueryAST");
    for(auto &query_unit : query_units_){
        query_unit->print(dep + 1);
    }
}

void QueryUnitAST::print(int dep) const{
    printHead(dep, "QueryUnitAST");
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
    printHead(dep, is_optional_ ? "OptionalMatchAST" : "MatchAST");
    for(auto &pat : pattern_){
        printHead(dep + 1, "", false , false);
        pat->print();
        std::printf("\n");
    }
    if(where_ != nullptr){
        printHead(dep, "Where");
        printHead(dep + 1, "", false , false);
        where_->print();
        std::printf("\n");
    }
}

void UnwindAST::print(int dep) const{
    printHead(dep, "UnwindAST");
    printHead(dep + 1, "", false, false);
    exp_->print();
    std::putchar('\n');
    printHead(dep + 1, "AS ", false, false);
    std::printf("%s\n", var_name_.c_str());
}

void InQueryCallAST::print(int dep) const{
    printHead(dep, "CallAST");
    printHead(dep + 1, "Procedure Name: ", false, false);
    int n = procedure_name_.size();
    std::printf("%s", procedure_name_[0].c_str());
    for(int i = 1; i < n; ++i){
        std::printf(".%s", procedure_name_[i].c_str());
    }
    std::putchar('\n');
    for(int i = 0; i < (int)args_.size(); ++i){
        printHead(dep + 1, (std::string("Argument") + std::to_string(i)).c_str() );
        printHead(dep + 2, "", false, false);
        args_[i]->print();
        std::putchar('\n');
    }
    printHead(dep + 1, "Yield");
    printHead(dep + 2, "", false, false);
    for(int i = 0; i < (int)yield_items_.size(); ++i){
        if(i != 0){
            std::printf(", ");
        }
        std::printf("%s AS %s", yield_items_[i].c_str(), alias_[i].empty() ? yield_items_[i].c_str() : alias_[i].c_str());
    }
    std::putchar('\n');

    if(where_ != nullptr){
        printHead(dep + 1, "Where");
        printHead(dep + 2, "", false ,false);
        where_->print();
        std::putchar('\n');
    }
    return;
}

void CreateAST::print(int dep) const{
    printHead(dep, "CreateAST");
    for(auto& pat : pattern_){
        printHead(dep + 1, "", false , false);
        pat->print();
        std::printf("\n");
    }
}

void MergeAST::print(int dep) const{
    printHead(dep, "MergeAST");
    printHead(dep + 1, "", false ,false);
    rigid_pattern_->print();
    std::putchar('\n');
    unsigned n = set_actions_.size();
    for(unsigned i = 0; i < n; ++i){
        if(is_on_match_[i]){
            printHead(dep, "ON MATCH", false, true);
        }else{
            printHead(dep, "ON CREATE", false, true);
        }
        set_actions_[i]->print(dep + 1);
    }
}

void DeleteAST::print(int dep) const{
    printHead(dep, detach ? "Detach Delete" : "Delete");
    for(auto &e : exp_){
        printHead(dep + 1, "", false, false);
        e->print();
        std::putchar('\n');
    }
}

void SetAST::print(int dep) const{
    printHead(dep, "SetAST");
    for(auto &s : set_items_){
        s->print(dep + 1);
    }
}

void RemoveAST::print(int dep) const{
    printHead(dep, "RemoveAST");
    for(auto &r : remove_items_){
        r->print(dep + 1);
    }
}   

void WithReturnAST::print(int dep) const{
    printHead(dep, with_ ? "WITH" : "RETURN");

    // print Projection_exp

    printHead(dep + 1, "ProjectionItems");
    if(asterisk_){
        printHead(dep + 2, "asterisk: true\n", false ,false);
    }
    for(int i = 0; i < proj_exp_.size(); ++i){
        printHead(dep + 2, "", false, false);
        proj_exp_[i]->print();
        if(alias_[i] != ""){
            std::printf("  AS  %s\n ", alias_[i].c_str());
        } else {
            std::printf("\n");
        }
    }

    // where
    if(where_ != nullptr){
        printHead(dep + 1, "Where");
        printHead(dep + 2, "", false, false);
        where_->print();
        std::printf("\n");
    }
    // order by
    if(order_by_.size()){
        printHead(dep + 1, "Order By");
        for(int i = 0; i < (int)order_by_.size(); ++i){
            printHead(dep + 2, "", false, false);
            order_by_[i]->print();
            std::printf(ascending_[i] ? "  ASC\n" : "  DEC\n");
        }
    }
    // limit
    if(limit_){
        printHead(dep + 1, "Limit");
        printHead(dep + 2, "", false, false);
        limit_->print();
        std::putchar('\n');
    }
    // skip
    if(skip_){
        printHead(dep + 1, "Skip");
        printHead(dep + 2, "", false, false);
        skip_->print();
        std::putchar('\n');
    }
}

void SetItemAST::print(int dep) const{
    printHead(dep, "SetItem: ", false , false);
    switch (set_type_){
        case SINGLE_PROPERTY:
            prop_exp_->print();
            std::printf(" = ");
            exp_->print();
            break;
        case NODE_LABELS:
            std::printf("%s", var_name_.c_str());
            for(auto &l : labels_){
                std::printf(":%s", l.c_str());
            }
            break;
        default:
            std::printf("%s", var_name_.c_str());;
            std::printf( ASSIGN_PROPERTIES ? " = " : " += ");
            exp_->print();
            break;
    }
    std::putchar('\n');

}

void RemoveItemAST::print(int dep) const{
    printHead(dep, "RemoveItem: ", false , false);

    if(labels_.size() != 0){
        std::printf("%s", var_name_.c_str());
        for(auto &l : labels_){
            std::printf(":%s",l.c_str());
        }
    }else{
        prop_exp_->print();
    }

    std::putchar('\n');
}