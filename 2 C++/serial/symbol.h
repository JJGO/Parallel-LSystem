#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <vector>
#include <cstdlib>

class Symbol{
	friend std::ostream& operator<<(std::ostream& output, const Symbol& s);

	private:
		char character;
		std::vector<double> parameters;

	public:
		Symbol();
		Symbol(const char c);
		Symbol(const char c, const int n);
		Symbol(const char c, std::vector<double> v);
		Symbol(const char c, const double p[], int n);
		~Symbol(){};

		std::vector<double> getParameters() const;

		bool operator == (const Symbol &other) const;

};

double fRand(double fMin, double fMax);

#endif


