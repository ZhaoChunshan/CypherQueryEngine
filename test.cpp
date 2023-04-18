// g++ -o test test.cpp Value.cpp Expression.cpp ../PQuery/Varset.cpp -I ./ -I ../PQuery -std=c++11
// ./test
#include "Value.h"
#include "Expression.h"
#include "PCypherParser.h"
#include <fstream>
#include <memory>
#include <algorithm>
#include <iostream>
using namespace std;

std::string QueryPath = "../Queries/";

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
    sort(values.begin(), values.end(), [](GPStore::Value *a, GPStore::Value *b){return *a < *b;});
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
    vector<GPStore::uint_64> nodes  = {1, 3, 5};
    vector<GPStore::uint_64> edges = {2, 4};
    vector<GPStore::Value::EdgeType> tys = {GPStore::Value::LEFT_EDGE, GPStore::Value::RIGHT_EDGE};
    GPStore::Value p1(nodes, edges, tys);

    GPStore::Value p2 = GPStore::Value(nodes,  edges, tys);
    p1 = p2;
    if(!(p1 ==  p2))return 1;
    vector<GPStore::uint_64> nodes2  = {5, 3, 1};
    vector<GPStore::uint_64> edges2 = {4, 2};
    vector<GPStore::Value::EdgeType> tys2 = { GPStore::Value::RIGHT_EDGE, GPStore::Value::LEFT_EDGE};

    auto p3=  GPStore::Value(edges2, nodes2, tys2);
    p2 = p3;
    if((p1 ==  p2))return 2;
    return 0;
}

/* 测试六：表达式 */
int test6(){
    GPStore::Expression exp;
    exp.oprt_ = GPStore::Expression::AND;
    GPStore::Expression *exp1 = new GPStore::Expression();
    GPStore::Expression *exp2 = new GPStore::Expression();
    exp1->atom_ = new GPStore::Variable(string("Var1"));
    exp2->atom_ = new GPStore::Variable(string("Var2"));
    exp.children_.push_back(exp1);
    exp.children_.push_back(exp2);
    // exp.print(0);
    return 0;
}

/* 测试七: 抽象语法树 */
int test7(){
    PCypherParser parser;
    std::ifstream fin(QueryPath + "/interactive-complex-10.cypher");
    CypherAST *ast = nullptr;
    try{
        ast = parser.CypherParse(fin);
        ast->print(0);
    } catch (const runtime_error& e){
        cout << e.what() << endl;
    }
    
    return 0;
}

int main(){
    int (*a[])()  = {test1, test2, test3, test4, test5, test6, test7};
    for(int i = 0; i < 7; ++i){
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