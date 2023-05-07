// g++ -o test ./test.cpp -std=c++11

#include <vector>
#include <string>
#include <unordered_map>
#include "PVarset.h"
using namespace std;

int main(){
    PVarset<string> varset;
    varset.addVar("dir");
    varset.addVar(string("abc"));
    varset.addVar(string("make"));
    varset.print();
    PVarset<pair<unsigned, unsigned>> varidset;
    varidset.addVar(make_pair(1,2));
    varidset.addVar(make_pair(1,2));
    varidset.addVar(make_pair(3,2));
    varidset.print();
    unordered_map<string, int> ma;
    ma.insert(make_pair("12", 2));
    ma.insert(make_pair("12", 2));
    ma.insert(make_pair("122", 2));
    for(auto &p : ma){
    cout << p.first << " "<<p.second<<endl;
    }
    std::vector<std::vector<bool>> adj;
    for(int i =0 ; i < 10;++i){
        adj.emplace_back();
        for(int j =0; j < 10; ++j){
            adj[i].push_back(true);
        }
    }
    for(int i = 0; i < 10;++i){
        adj[i][4] = adj[4][i] = false;
    }
    adj[4][4] = true;
    auto vec = calculateConnectedComponent(adj);
    for(auto i : vec){
        std::cout << " " << i ;
    }
    return 0;
}