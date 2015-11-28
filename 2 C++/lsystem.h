#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <iostream>
#include <vector>
#include "symbol.h"

class LSystem{
	friend std::ostream& operator<<(std::ostream& output, const LSystem& s);

	private:
		std::vector<Symbol> axiom;
		std::vector<Symbol> state;
		int iteration;

	public:
		LSystem(std::vector<Symbol> axiom);
		~LSystem(){};

		std::vector<Symbol> getState() const;
		virtual void substitute(Symbol s, std::vector<Symbol> &string);
		void reset();
		void next();
		void iterate(int n);
};

#endif