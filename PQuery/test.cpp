// g++ -o test ./test.cpp -std=c++11

#include <vector>
#include <string>
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
    return 0;
}