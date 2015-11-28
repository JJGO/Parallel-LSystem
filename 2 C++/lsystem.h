#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <iostream>
#include <vector>
#include "symbol.h"

class LSystem{
	friend std::ostream& operator<<(std::ostream& output, const LSystem& s);

	private:
		int iteration;
		std::vector<Symbol> state;
		
	protected:
		std::vector<Symbol> axiom;

	public:
		LSystem();
		LSystem(std::vector<Symbol> axiom);
		~LSystem(){};

		std::vector<Symbol> getState() const;
		virtual void substitute(Symbol s, std::vector<Symbol> &string);
		void reset();
		void next();
		void iterate(int n);
};


class DLSystem : public LSystem
{
	private:
		std::vector<double> parameters;
	public:
		DLSystem(std::vector<Symbol> axiom, std::vector<double> par);
		virtual double calculateMetric();
		virtual void updateMetric(std::vector<double> neighbor_metrics);
};

class LGroup
{
	private:
		std::vector<DLSystem> systems;
	public:
		LGroup(){};
		LGroup(std::vector<DLSystem> s);
		std::vector< std::vector<Symbol> > getStates() const;
		void reset();
		void next();
		void iterate(int n);
		void addSystem(DLSystem l);
};

#endif