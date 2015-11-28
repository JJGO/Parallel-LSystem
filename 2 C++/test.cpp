#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lsystem.h"

int main(int argc, char const *argv[])
{
	Symbol a('A');
	std::cout << a << std::endl;
	Symbol b('B',2);
	std::cout << b << std::endl;
	double p[3] = {1.2, 2.4, 4.8};
	Symbol c('C',3,p);
	std::cout << c << std::endl;
	Symbol a2('A',3,p);
	std::cout << (a == c) << std::endl;
	std::cout << (a == a) << std::endl;
	std::cout << (a == a2) << std::endl;

	Symbol* d = new Symbol('D',3,p);


	////
	Symbol F('F');
	std::cout << *d << std::endl;
	delete d;
	std::vector<Symbol> axiom;
	// axiom.push_back(b);
	// axiom.push_back(c);
	// printf("Hello\n");
	// std::cout << axiom[1];
	// printf("Hello\n");
	// axiom.push_back(c);
	// for(int i = 0 ; i < axiom.size() ; i++)
	// 	std::cout << axiom[i];
	// std::cout << std::endl;
	LSystem L(axiom);
	std::cout << L << std::endl;
	L.iterate(2);
	std::cout << L << std::endl;
	printf("FIN\n");
	return 0;
}