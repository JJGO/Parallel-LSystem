#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>

class Symbol{
	friend std::ostream& operator<<(std::ostream& output, const Symbol& s);

	private:
		char character;
		int numpar;
		double* parameters;

	public:
		Symbol();
		Symbol(const char c);
		Symbol(const char c, const int n);
		Symbol(const char c, const int n, const double p[]);
		~Symbol();

		bool operator == (const Symbol &other) const;

};

#endif


