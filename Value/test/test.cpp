// g++ -o test test.cpp ../src/Value.cpp -I ../src -std=c++11
// ./test
#include "../src/Value.h"
#include <memory>
#include <algorithm>
#include <iostream>
using namespace std;


/* 测试一：对IntValue * 排序 */
int test1(){
    vector<Value *> int_vec;
    for(int i = 100; i >=1; --i){
        int_vec.push_back(new Value((int_64)i));
    }
    sort(int_vec.begin(), int_vec.end(), [](Value *a, Value* b){return *a < *b; });
    for(int i = 1; i <= 100; ++i){
        if(int_vec[i - 1]->data_.Int != i )
            return 1;
        delete int_vec[i - 1];
    }
    return 0;
}

/* 测试二: 对 10, 8.8, "hello", null, [10, null], [10] 排序 */
int test2(){
    
    Value i(10LL);
    Value f(8.8);
    Value nll(Value::NO_VALUE);
    Value lst(Value::LIST), lst2(Value::LIST);
    lst.append(i);
    lst.append(nll);
    Value s(string("hello"));
    lst2.append(i);
    vector<Value *> values = { &i, &f,&s, &nll, &lst, &lst2};
    sort(values.begin(), values.end(), [](Value *a, Value *b){return *a < *b;});
    // order: lst2 lst s, f, i, null
    vector<Value *> order = { &lst2,  &lst,  &s,  &f,  &i, &nll};
    for(int i = 0; i < 6; ++i){
        if(values[i] != order[i]) return 1;
    }
    return 0;
}

/* 测试三：相等 */
int test3(){
    Value i(-100LL);
    Value f(-100.0);
    if(!(i == f)) return 1;
    Value ls1(Value::LIST), ls2(Value::LIST);
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
    Value i1(5LL), i2;
    i2 = i1;
    if(!(i1 == i2)) return 1;
    Value ls(Value::LIST);
    ls.append(i1);
    ls.append(ls);
    if(!(ls == ls)) return 2;
    return 0;
}

/* 测试五：路径 */
int test5(){
    vector<uint_64> nodes  = {1, 3, 5};
    vector<uint_64> edges = {2, 4};
    vector<Value::EdgeType> tys = {Value::LEFT_EDGE, Value::RIGHT_EDGE};
    Value p1(nodes, edges, tys);

    Value p2 = Value(nodes,  edges, tys);
    p1 = p2;
    if(!(p1 ==  p2))return 1;
    vector<uint_64> nodes2  = {5, 3, 1};
    vector<uint_64> edges2 = {4, 2};
    vector<Value::EdgeType> tys2 = { Value::RIGHT_EDGE, Value::LEFT_EDGE};

    auto p3=  Value(edges2, nodes2, tys2);
    p2 = p3;
    if((p1 ==  p2))return 2;
    return 0;
}

int main(){
    int (*a[])()  = {test1, test2, test3, test4, test5};
    for(int i = 0; i < 5; ++i){
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