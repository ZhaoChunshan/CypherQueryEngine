/*=============================================================================
# Filename: PVarset.h
# Author: Chunshan Zhao
# Mail: 1900016633@pku.edu.cn
# Last Modified: 2023-04-19
# Description:
=============================================================================*/
#ifndef PQUERY_PVARSET_H
#define PQUERY_PVARSET_H

#include <iostream>
#include <string>
#include <vector>

inline std::ostream&  operator<<(std::ostream& o, std::pair<unsigned, unsigned> p){
    std::cout << "(" << p.first << "," << p.second << ")";
    return o;
}

template <class T>
class PVarset
{
    public:
        std::vector<T> vars;

        PVarset(){};
        PVarset(const T &_var){  this->addVar(_var);}
        PVarset(const std::vector<T> &_vars)
        {
            for (int i = 0; i < (int)_vars.size(); i++)
                this->addVar(_vars[i]);
        }

        bool empty() const { return this->vars.empty(); }
        int getVarsetSize() const { return this->vars.size(); }
        bool findVar(const T &_var) const{
            if (this->vars.empty())
                return false;

            for (int i = 0; i < (int)this->vars.size(); i++)
                if (this->vars[i] == _var)    return true;

            return false;
        }
        void addVar(const T &_var){
            if (!this->findVar(_var))
                this->vars.push_back(_var);
        }

        PVarset operator + (const PVarset &_varset) const{
            PVarset<T> r(*this);

            for (int i = 0; i < (int)_varset.vars.size(); i++)
                r.addVar(_varset.vars[i]);

            return r;
        }

        PVarset& operator += (const PVarset &_varset){
             for (int i = 0; i < (int)_varset.vars.size(); i++)
                this->addVar(_varset.vars[i]);

            return *this;
        }

        PVarset operator * (const PVarset &_varset) const{
            PVarset<T> r;

            for (int i = 0; i < (int)this->vars.size(); i++)
                if (_varset.findVar(this->vars[i]))
                    r.addVar(this->vars[i]);

            return r;
        }

        PVarset operator - (const PVarset &_varset) const{
            PVarset<T> r;

            for (int i = 0; i < (int)this->vars.size(); i++)
                if (!_varset.findVar(this->vars[i]))
                    r.addVar(this->vars[i]);

            return r;
        }

        bool operator ==(const PVarset &_varset) const{
            if ((int)this->vars.size() != (int)_varset.vars.size())
                return false;

            for (int i = 0; i < (int)this->vars.size(); i++)
                if (!_varset.findVar(this->vars[i]))
                    return false;

            return true;
        }

        bool hasCommonVar(const PVarset &_varset) const{
            for (int i = 0; i < (int)this->vars.size(); i++)
                if (_varset.findVar(this->vars[i]))
                    return true;

            return false;
        }

        bool belongTo(const PVarset &_varset) const{
            for (int i = 0; i < (int)this->vars.size(); i++)
                if (!_varset.findVar(this->vars[i]))
                    return false;

            return true;
        }

        std::vector<int> mapTo(const PVarset &_varset) const{
            std::vector<int> r;

            for (int i = 0; i < (int)this->vars.size(); i++)
            {
                r.push_back(-1);
                for (int j = 0; j < (int)_varset.vars.size(); j++)
                    if (this->vars[i] == _varset.vars[j])
                        r[i] = j;
            }

            return r;

        }

        void print() const{
            printf("Varset: ");

            for (int i = 0; i < (int)this->vars.size(); i++)
            {
                std::cout << this->vars[i] << " ";
            }

            printf("\n");
        }
};


#endif