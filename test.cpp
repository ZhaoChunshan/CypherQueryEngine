#include "Value.h"
#include "Expression.h"
#include "PCypherParser.h"
#include "PQueryTree.h"

//#include "PTempResult.h"
//#include "PCalculator.h"
#include <fstream>
#include <memory>
#include <algorithm>
#include <iostream>
using namespace std;
std::shared_ptr< std::unordered_map<std::string, GPStore::Value>> param(new  std::unordered_map<std::string, GPStore::Value>);

std::string QueryPath = "../Queries/";
const char *s[]= {
        "interactive-short-1.cypher",
        "interactive-short-2.cypher",
        "interactive-short-3.cypher",
        "interactive-short-4.cypher",
        "interactive-short-5.cypher",
        "interactive-short-6.cypher",
        "interactive-short-7.cypher",

        "interactive-complex-1.cypher",
        "interactive-complex-2.cypher",
        "interactive-complex-3.cypher",
        "interactive-complex-4.cypher",
        "interactive-complex-5.cypher",
        "interactive-complex-6.cypher",
        "interactive-complex-7.cypher",
        "interactive-complex-8.cypher",
        "interactive-complex-9.cypher",
        "interactive-complex-10.cypher",
        "interactive-complex-11.cypher",
        "interactive-complex-12.cypher",
        "interactive-complex-13.cypher",
        "interactive-complex-14.cypher",

        "interactive-update-1.cypher",
        "interactive-update-2.cypher",
        "interactive-update-3.cypher",
        "interactive-update-4.cypher",
        "interactive-update-5.cypher",
        "interactive-update-6.cypher",
        "interactive-update-7.cypher",
        "interactive-update-8.cypher",

        "interactive-delete-1.cypher",
        "interactive-delete-2.cypher",
        "interactive-delete-3.cypher",
        "interactive-delete-4.cypher",
        "interactive-delete-5.cypher",
        "interactive-delete-6.cypher",
        "interactive-delete-7.cypher",
        "interactive-delete-8.cypher",
        "test_list_comprehension.cypher",
        "example_2.cypher"

};

/* 测试一：对IntValue * 排序 */
int test1(){
    vector<GPStore::Value *> int_vec;
    for(int i = 100; i >=1; --i){
        int_vec.push_back(new GPStore::Value((GPStore::int_64)i));
    }
    sort(int_vec.begin(), int_vec.end(), [](GPStore::Value *a, GPStore::Value* b){return *a < *b; });
    for(int i = 1; i <= 100; ++i){
        if(int_vec[i - 1]->data_.Int != i )
            return 1;
        delete int_vec[i - 1];
    }
    return 0;
}

/* 测试二: 对 10, 8.8, "hello", null, [10, null], [10] 排序 */
int test2(){
    
    GPStore::Value i(10LL);
    GPStore::Value f(8.8);
    GPStore::Value nll(GPStore::Value::NO_VALUE);
    GPStore::Value lst(GPStore::Value::LIST), lst2(GPStore::Value::LIST);
    lst.append(i);
    lst.append(nll);
    GPStore::Value s(string("hello"));
    lst2.append(i);
    vector<GPStore::Value *> values = { &i, &f,&s, &nll, &lst, &lst2};
    sort(values.begin(), values.end(), [](GPStore::Value *a, GPStore::Value *b){return a->comp(*b) == -1;});
    // order: lst2 lst s, f, i, null
    vector<GPStore::Value *> order = { &lst2,  &lst,  &s,  &f,  &i, &nll};
    for(int i = 0; i < 6; ++i){
        if(values[i] != order[i]) return 1;
    }
    return 0;
}

/* 测试三：相等 */
int test3(){
    GPStore::Value i(-100LL);
    GPStore::Value f(-100.0);
    if(!(i == f)) return 1;
    GPStore::Value ls1(GPStore::Value::LIST), ls2(GPStore::Value::LIST);
    ls1.append(i);
    ls1.append(i);
    ls2.append(i);
    ls2.append(i);
    if(!(ls1 == ls2))return 2;
    ls2.append(ls1);
    if(ls1 == ls2) return 3;
    ls1.append(ls1);
    if(!(ls1 == ls2) )return 4;
    return 0;
}

/* 测试四：赋值 */
int test4(){
    GPStore::Value i1(5LL), i2;
    i2 = i1;
    if(!(i1 == i2)) return 1;
    GPStore::Value ls(GPStore::Value::LIST);
    ls.append(i1);
    ls.append(ls);
    if(!(ls == ls)) return 2;
    return 0;
}

/* 测试五：路径 */
int test5(){
    vector<unsigned > nodes  = {1, 3, 5};
    vector<GPStore::uint_64> edges = {2, 4};

    GPStore::Value p1(nodes, edges);

    GPStore::Value p2 = GPStore::Value(nodes,  edges);
    p1 = p2;
    if(!(p1 ==  p2))return 1;
    vector<unsigned > nodes2  = {5, 3, 1};
    vector<GPStore::uint_64> edges2 = {4, 2};

    auto p3=  GPStore::Value(nodes2, edges2);

    if((p3 ==  p2))return 2;
    return 0;
}

/* 测试六：表达式 */
int test6(){
    GPStore::Expression *exp_var = new GPStore::Expression();
    GPStore::Variable *var = new GPStore::Variable(string("AVAR"));
    exp_var->atom_ = var;
    GPStore::Expression exp_var_copy(*exp_var);
    delete exp_var;
    // exp_var_copy.print(0);
    GPStore::Expression exp;
    exp.oprt_ = GPStore::Expression::AND;
    GPStore::Expression *exp1 = new GPStore::Expression();
    GPStore::Expression *exp2 = new GPStore::Expression();
    exp1->atom_ = new GPStore::Variable(string("Var1"));
    exp2->atom_ = new GPStore::Variable(string("Var2"));
    exp.children_.push_back(exp1);
    exp.children_.push_back(exp2);
    //exp.print(0);
    return 0;
}

/* 测试七: 抽象语法树 */
int test7(){
    PCypherParser parser;

    // std::cout << std::endl;
    for(int i = 0; i < 37; ++i){
        std::unique_ptr<CypherAST> ast;
        std::ifstream fin(QueryPath + s[i]);
        // std::cout << "===========Parse AST For " << s[i] << "===========" << std::endl;

        try{
            ast.reset(parser.CypherParse(fin, param ,nullptr));
            // ast->print(0);
        } catch (const runtime_error& e){
            cout << e.what() << endl;
            return 1;
        }
    }
    return 0;
}


/* 测试八：逻辑执行树 */
int test8(){
    cout << endl;

    PCypherParser parser;
    for(int i = 0; i < 39; ++i){
        std::ifstream fin(QueryPath + string(s[i]));
        std::cout << "===========Generate QueryTree For " << s[i] << "===========" << std::endl;
        std::unique_ptr<CypherAST> ast;
        std::unique_ptr<PTreeNode> plan;
        try{
            ast.reset( parser.CypherParse(fin, param, nullptr));
            plan.reset(PQueryTree::GenerateQueryTree(ast.get()));
            std::cout << "===========Variable Encoding " << s[i] << "===========" << std::endl;
            int n = ast->id2var_name_->size();
            for(int i = 0; i < n; ++i){
                std::printf("%5d\t%s\n",i,ast->id2var_name_->at(i).c_str());
            }
            plan->print();
        } catch (const runtime_error& e){
            cout << e.what() << endl;
            return 1;
        }
        fin.close();
    }
    return 0;
}

///* 测试九：PTempResult Sort */
//int test9(){
//    vector<unsigned > n1 = {22, 1, 8, 40, 33};
//    vector<unsigned > n2 = {3, 5, 1, 2, 4};
//    vector<unsigned long long> e = {100, 88, 99, 111, 222};
//    vector<GPStore::Value> v = { GPStore::Value(1.0), GPStore::Value("Hello"),
//                                    GPStore::Value("Alice"), GPStore::Value(GPStore::Value::INTEGER),
//                                    GPStore::Value(GPStore::Value::NO_VALUE) };
//    v[3].data_.Int = -1;
//
//    vector<unsigned > node_var = {1, 2};
//    vector<unsigned > edge_var = {3};
//    vector<unsigned > value_var = {5};
//    PTempResult res;
//    res.head_.setColumnVarName(node_var, edge_var, value_var);
//    for(int i = 0; i < 5; ++i){
//        res.rows_.emplace_back();
//        res.rows_.back().spo_id_.push_back(n1[i]);
//        res.rows_.back().spo_id_.push_back(n2[i]);
//        res.rows_.back().edge_id_.push_back(e[i]);
//        res.rows_.back().values_.emplace_back(v[i]);
//    }
//    cout << "\n ========Print PTempResult========\n";
//    res.print();
//    cout << "\n ========Sort PTempResult========\n";
//    vector<unsigned >cols ={ 0, 1, 2};
//    res.sort(0, 4, cols);
//    cout << "\n ========Print PTempResult========\n";
//    res.print();
//    return 0;
//}
//
///* 测试十：计算器 */
//int test10(){
//    PCypherParser parser;
//    std::string q1("RETURN \"abc\" starts with \"a\" ");
//    std::string q2(" RETURN [1, null, \"happy\", {age:10}][2..4][1][\"age\"]");
//    std::unique_ptr<CypherAST> ast(parser.CypherParse(q1));
//    auto & with_ret = ast->single_querys_[0]->query_units_[0]->with_return_;
//    auto v1 = PCalculator::evaluateConstExpression(with_ret->proj_exp_[0].get());
//    ast.reset(parser.CypherParse(q2));
//    auto v2 = PCalculator::evaluateConstExpression(
//            ast->single_querys_[0]->query_units_[0]->with_return_->proj_exp_[0].get()
//            );
//    if(v1.type_ == GPStore::Value::BOOLEAN && v1.data_.Boolean){
//        if(v2.type_ == GPStore::Value::INTEGER && v2.data_.Int == 10){
//            return 0;
//        }
//        return 2;
//    }
//    return 1;
//}
//
//int test11(){
//    PCypherParser parser;
//    std::ifstream fin(QueryPath + string("example_2.cypher"));
//        std::unique_ptr<CypherAST> ast;
//        try{
//            ast.reset( parser.CypherParse(fin));
//            PQueryTree qt;
//            qt.GenerateQueryTree(ast.get());
//        } catch (const runtime_error& e){
//            cout << e.what() << endl;
//        }
//        fin.close();
//    return 0;
//}

int main(){

    int (*a[])()  = {test1, test2, test3, test4, test5, test6, test7, test8};//, test8, test9,    test10, test11
    for(int i = 0; i < 8; ++i){
        cout << "Run test " << i + 1 <<"...\t\t\t";
        int code;
        if((code = a[i]())) {
            cout << "Fail. Code: " << code;

        }
        else{
            cout<<"Pass.";
        }
        cout <<endl;
    }
    return 0;
}
