#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <iostream>
#include <vector>
#include <cmath>
#include "symbol.h"

struct Point {
    double x;
    double y;
};

double pointDistance(Point p, Point q);

class LSystem{
	friend std::ostream& operator<<(std::ostream& output, const LSystem& s);

	// private:
		
	protected:
		std::vector<Symbol> axiom;
		std::vector<Symbol> state;

	public:
		int iteration;
		LSystem();
		LSystem(std::vector<Symbol> axiom);
		~LSystem(){};

		std::vector<Symbol> getState() const{return state;}
		int getIteration() const {return iteration;}
		virtual void substitute(Symbol s, std::vector<Symbol> &string);
		void reset();
		void next();
		void iterate(int n);
};


class DLSystem : public LSystem
{
	protected:
		std::vector<double> parameters;
	public:
		DLSystem(){};
		DLSystem(std::vector<Symbol> axiom, std::vector<double> par);
		// virtual void substitute(Symbol s, std::vector<Symbol> &string);
		virtual double calculateMetric();
		virtual void updateMetric(std::vector<double> global_metrics);
};

class LGroup
{
	protected:
		std::vector<DLSystem> systems;
	public:
		LGroup(){};
		LGroup(std::vector<DLSystem> s);
		std::vector< std::vector<Symbol> > getStates() const;
		void reset();
		virtual void next();
		void iterate(int n);
		void addSystem(DLSystem l);
};

#endif