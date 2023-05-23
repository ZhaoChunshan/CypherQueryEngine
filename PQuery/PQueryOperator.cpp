#include "PQueryOperator.h"

void printTab(int n){
    for(int i = 0; i < n; ++i) std::putchar('\t');
}

void printVarset(const PVarset<unsigned > & varset, int dep ){
    printTab(dep);
    std::printf("Produce Varset:");
    for(auto & v : varset.vars){
        std::printf("%u, ", v);
    }
    std::putchar('\n');
}

void BGPOperator::print(int dep) const {
    printTab(dep);
    std::printf("BGP:\n");
    for(auto & pat : pattern_){
        printTab(dep + 1);
        pat->print();
        std::putchar('\n');
    }
    printTab(dep + 1);
    std::printf("Edge Different: ");
    int n = edge_conflict_.getVarsetSize();
    if(n != 0)
        std::printf("(%u, %u)", edge_conflict_.vars[0].first, edge_conflict_.vars[0].second);
    for(int i = 1; i < n; ++i){
        std::printf(", (%u, %u)", edge_conflict_.vars[i].first, edge_conflict_.vars[i].second);
    }
    std::putchar('\n');
    printTab(dep + 1);
    std::printf("Constrain:\n");
    for(auto & exp :filters_){
        printTab(dep + 2);
        exp->print();
        std::putchar('\n');
    }
    printVarset(minimal_varset_,dep + 1);
}

void FilterOperator::print(int dep) const {
    printTab(dep);
    printf("Filter:\n");
    printTab(dep + 1);

    for(auto &exp :filters_){
        exp->print();
        std::printf(" ,");
    }
    std::printf("\n");
    printVarset(minimal_varset_,dep + 1);
}

void ProjectionOperator::print(int dep) const {
    printTab(dep);
    std::printf("Projection:\n");
    int n = proj_exps_.size();

    for(int i = 0; i < n; ++i){
        printTab(dep + 1);
        proj_exps_[i]->print();
        std::printf("  AS %u\n", var_id_[i]);
    }
    printVarset(minimal_varset_,dep + 1);
}

void AndOperator::print(int dep) const {
    printTab(dep);
    std::printf("And:\n");
    if(!filters_.empty()){
        printTab(dep + 1);
        std::printf("Join on: ");
        for(auto & f : filters_){
            f->print();
            std::printf(", ");
        }
        std::printf("\n");
    }
    printVarset(minimal_varset_,dep + 1);
}
void OptionalOperator::print(int dep) const {
    printTab(dep);
    std::printf("Optional:\n");
    printVarset(minimal_varset_,dep + 1);
}
void UnionOperator::print(int dep) const {
    printTab(dep);
    std::printf("Union:\n");
    printVarset(minimal_varset_,dep + 1);
}
void MinusOperator::print(int dep) const {
    printTab(dep);
    std::printf("Minus:\n");
    printVarset(minimal_varset_,dep + 1);
}

void ModifierOperator::print(int dep) const {
    printTab(dep);
    std::printf("Modifier:\n");
    printTab(dep + 1);
    std::printf("Order By:\n");
    int n = order_exps_.size();

    for(int i = 0; i < n; ++i){
        printTab(dep + 2);
        order_exps_[i]->print();
        printf(ascending_[i] ? "  ASC\n" : "  DEC\n");
    }
    if(limit_ != INVALID){
        printTab(dep + 1);
        std::printf("Limit: %u\n", limit_);
    }
    if(skip_ != 0){
        printTab(dep + 1);
        std::printf("Skip: %u\n", skip_);
    }
    if(distinct_){
        printTab(dep + 1);
        std::printf("Distinct: true\n");
    }
    printVarset(minimal_varset_,dep + 1);
}
void UnwindOperator::print(int dep) const {
    printTab(dep);
    std::printf("Unwind:\n");
    printTab(dep + 1);
    unwind_->print();
    std::printf("  AS %u\n", var_id_);
    printVarset(minimal_varset_,dep + 1);
}

void CallOperator::print(int dep) const {
    printTab(dep);
    std::printf("Call:\n");
    int n = args_.size();
    for(int i = 0; i < n; ++i){
        printTab(dep + 1);
        std::printf("Argument%d: ", i);
        args_[i]->print();
        std::putchar('\n');
    }
    printTab(dep + 1);
    std::printf("Yield:\n");
    int m = yield_var_id_.size();
    for(int i = 0;i < m; ++i){
        printTab(dep + 2);
        std::printf("%s AS %d\n", yield_items_[i].c_str(), yield_var_id_[i]);
    }
    printVarset(minimal_varset_,dep + 1);
}

void CreateOperator::print(int dep) const {
    printTab(dep);
    std::printf("Create:\n");
    for(auto & pat : pattern_){
        printTab(dep + 1);
        pat->print();
        std::putchar('\n');
    }
    printVarset(minimal_varset_,dep + 1);
}

void DeleteOperator::print(int dep) const {
    printTab(dep);
    std::printf("Delete:\n");
    if(detach){
        printTab(dep + 1);
        std::printf("Detach: true\n");
    }
    for(auto & exp : exp_){
        exp->print();
        std::printf(", ");
    }
    std::putchar('\n');
    printVarset(minimal_varset_,dep + 1);
}

void SetOperator::print(int dep) const {
    printTab(dep);
    std::printf("Set:\n");
    printTab(dep + 1);
    int n = labels_.size();
    for(int i = 0; i < n; ++i){
        std::printf("%s", var_names_[i].c_str());
        for(auto & l :labels_[i]){
            std::printf(":%s", l.c_str());
        }
        std::printf(", ");
    }
    int m = exps_.size();
    for(int i = n + i; i < n + m; ++i){
        if(add_property_[i]) continue;
        std::printf("%s = ", var_names_[i].c_str());
        exps_[i]->print();
        std::printf(", ");
    }
    for(int i = n + i; i < n + m; ++i){
        if(!add_property_[i]) continue;
        std::printf("%s += ", var_names_[i].c_str());
        exps_[i]->print();
        std::printf(", ");
    }
    int t = prop_exps_.size();
    for(int i = 0; i <t;++i){
        prop_exps_[i]->print();
        std::printf(" = ");
        prop_vals_[i]->print();
        std::printf(", ");
    }
    std::putchar('\n');
    printVarset(minimal_varset_,dep + 1);
}

void RemoveOperator::print(int dep) const {
    printTab(dep);
    std::printf("Remove:\n");
    printTab(dep + 1);
    int n = labels_.size();
    for(int i = 0; i < n ; ++i){
        std::printf("%s", var_names_[i].c_str());
        for(auto & l : labels_[i]){
            std::printf(":%s", l.c_str());
        }
        std::printf(", ");
    }
    int m = prop_exps_.size();
    for(int i = 0; i < m; ++i){
        prop_exps_[i]->print();
        std::printf(", ");
    }
    std::printf("\n");
    printVarset(minimal_varset_,dep + 1);
}

void GroupByOperator::print(int dep) const {
    printTab(dep);
    std::printf("Group By:\n");
    printTab(dep + 1);
    int n = grouping_keys_.size();
    for(int i = 0; i < n; ++i){
        if(i == 0){
            std::printf("%u", grouping_keys_[i]);
        }
        else{
            std::printf(", %u", grouping_keys_[i]);
        }
    }
    std::printf("\n");
    printVarset(minimal_varset_,dep + 1);
}

void AggregationOperator::print(int dep) const {
    printTab(dep);
    std::printf("Aggregation:\n");
    int n = aggr_var_id_.size();
    for(int i = 0; i < n; ++i){
        printTab(dep + 1);
        aggr_value_[i]->print();
        std::printf("  AS  %u\n", aggr_var_id_[i]);
    }
    printVarset(minimal_varset_,dep + 1);
}

void ShortestPathOperator::print(int dep) const {
    printTab(dep);
    std::printf("ShortestPath:\n");
    printTab(dep + 1);
    std::printf("isAllShortest: ");
    std::printf(is_all_shortest_? "true\n": "false\n");
    printTab(dep + 1);
    std::printf("(%u)", src_);
    edge_pattern_->print();
    std::printf("(%u)", tgt_);
    std::printf("\n");
    printVarset(minimal_varset_,dep + 1);
}

