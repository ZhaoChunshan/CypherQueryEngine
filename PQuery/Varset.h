/*=============================================================================
# Filename: Varset.h
# Author: Jiaqi, Chen
# Mail: chenjiaqi93@163.com
# Last Modified: 2017-03-10
# Description:
=============================================================================*/

#include <string>
#include <vector>

class Varset
{
	public:
		std::vector<std::string> vars;

		Varset(){};
		Varset(const std::string &_var);
		Varset(const std::vector<std::string> &_vars);

		bool empty() const;
		int getVarsetSize() const;
		bool findVar(const std::string &_var) const;
		void addVar(const std::string &_var);

		Varset operator + (const Varset &_varset) const;
		Varset& operator += (const Varset &_varset);
		Varset operator * (const Varset &_varset) const;
		Varset operator - (const Varset &_varset) const;

		bool operator ==(const Varset &_varset) const;
		bool hasCommonVar(const Varset &_varset) const;
		bool belongTo(const Varset &_varset) const;

		std::vector<int> mapTo(const Varset &_varset) const;

		void print() const;
};


