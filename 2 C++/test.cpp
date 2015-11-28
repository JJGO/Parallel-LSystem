#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "fractals.h"

int main(int argc, char const *argv[])
{
	Symbol a('A');
	std::cout << a << std::endl;
	Symbol b('B',2);
	std::cout << b << std::endl;
	double p[3] = {1.2, 2.4, 4.8};
	Symbol c('C', p, 3);
	std::vector<double> v(p,p+2);
	Symbol d('D',v);
	std::cout << c << std::endl;
	Symbol e;
	e = c;
	std::cout << e << std::endl;
	////
	std::vector<Symbol> axiom;
	axiom.push_back(c);
	axiom.push_back(a);
	axiom.push_back(b);
	axiom.push_back(e);
	// for(int i ; i < axiom.size() ; i++)
	// {
	// 	std::cout << axiom[i];
	// }
	std::cout << std::endl;
	LSystem L(axiom);
	std::cout << L << std::endl;
	L.iterate(2);
	std::cout << L << std::endl;

	RowOfTrees F;
	std::cout << F << std::endl;
	F.iterate(2);
	std::cout << F << std::endl;

	return 0;
}