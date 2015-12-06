#include "fractals.h"
#include <cmath>

double fRand(double lower_bound, double upper_bound)
{
    double f = (double)rand() / (double)RAND_MAX;
    return lower_bound + f * (upper_bound - lower_bound);
}

KochCurve::KochCurve()
{
	Symbol F('F');
	axiom.push_back(F);
	reset();
}

void KochCurve::substitute(Symbol s, std::vector<Symbol> &string)
{
	Symbol F('F');
	if(s == F)
	{
		Symbol plus('+');
		Symbol minus('-');
		Symbol production[9] = {F, plus, F, minus, F, minus, F, plus, F};
		string.insert(string.end(),production,production+(sizeof(production)/sizeof(Symbol)));
	}else
	{
		string.push_back(s);
	}
}


ArrowHeadCurve::ArrowHeadCurve()
{
	Symbol A('A');
	axiom.push_back(A);
	reset();
}

void ArrowHeadCurve::substitute(Symbol s, std::vector<Symbol> &string)
{
	
	if(s == Symbol('A') || s == Symbol('B') )
	{
		Symbol A('A');
		Symbol B('B');
		Symbol plus('+');
		Symbol minus('-');
		std::vector<Symbol> production;
		if(s == A)
		{
			Symbol production[5] = {B,minus,A,minus,B};
			string.insert(string.end(),production,production+(sizeof(production)/sizeof(Symbol)));
		}else if(s == B)
		{
			Symbol production[5] = {A,plus,B,plus,A};
			string.insert(string.end(),production,production+(sizeof(production)/sizeof(Symbol)));
		}
	}else
	{
		string.push_back(s);
	}
}

RowOfTrees::RowOfTrees()
{
	double par[1] = {500.0};
	Symbol F('F',par,1);
	axiom.push_back(F);
	reset();
	c = 1;
	p = 0.3;
	q = c-p;
	h = std::pow(p*q,0.5);

}

void RowOfTrees::substitute(Symbol s, std::vector<Symbol> &string)
{
	
	if(s == Symbol('F') )
	{
		double x = s.getParameters()[0];
		double par[1];
		par[0] = 87;
		Symbol plus('+',par,1);
		Symbol minus('-',par,1);

		par[0] = x * p;
		Symbol P('F',par,1);
		par[0] = x * q;
		Symbol Q('F',par,1);
		par[0] = x * h;
		Symbol H('F',par,1);

		Symbol production[8] = {P,plus,H,minus,minus,H,plus,Q};
		string.insert(string.end(),production,production+(sizeof(production)/sizeof(Symbol)));
	}else
	{
		string.push_back(s);
	}
}

double Tree::calculateMetric()
{
	double nodes = 0;
	for(int i = 0 ; i < state.size() ; i++)
	{
		if( state[i] == Symbol(']') )
		{
			nodes++;
		}
	}
	metric = nodes;
	return nodes;
}

void Tree::updateMetric(std::vector<double> &global_metrics, std::vector<int> &neighbors)
{
	double average = 0;
	for(int i = 0 ; i < neighbors.size() ; i++)
	{
		average += global_metrics[neighbors[i]];
	}
	average /= neighbors.size();
	probability *= (1+(average - metric)/(metric));
	probability = std::max(0.3,std::min(0.9,probability));

}

MonopodialTree::MonopodialTree()
{
 	parameters = std::vector<double>(7);
	parameters[0] = 0.9; 	// r1
	parameters[1] = 0.6; 	// r2
	parameters[2] = 45; 	// a0
	parameters[3] = 45; 	// a2
	parameters[4] = 137.5; 	// d
	parameters[5] = 0.707; 	// wr
	probability = .9;		// probability
	double symbol_par[2] = {1,10};
	Symbol A('A',symbol_par,2);
	axiom.push_back(A);
	reset();
}


void MonopodialTree::substitute(Symbol s, std::vector<Symbol> &string)
{

	if( (s == Symbol('A') || s == Symbol('B') || s == Symbol('C') ) && fRand(0,1) <= probability )
		// if( (s == Symbol('A') || s == Symbol('B') || s == Symbol('C') ) && 0.85 <= probability )
	{
		double l = s.getParameters()[0];
		double w = s.getParameters()[1];
		Symbol production[8];
		double symbol_par[2];
		symbol_par[0] = w;
		production[0] = Symbol('!',symbol_par,1);

		symbol_par[0] = l;
		production[1] = Symbol('F',symbol_par,1);

		production[2] = Symbol('[');

		double symbol_par1[2] = { l * parameters[1] , w * parameters[5] };
		double symbol_par2[2] = { l * parameters[0] , w * parameters[5] };

		if( s == Symbol('A'))
		{
			symbol_par[0] = parameters[2];
			production[3] = Symbol('&',symbol_par,1);
			production[4] = Symbol('B',symbol_par1,2);
			production[5] = Symbol(']');
			symbol_par[0] = parameters[4];
			production[6] = Symbol('>',symbol_par,1);
			production[7] = Symbol('A',symbol_par2,2);
		}
		else if( s == Symbol('B') )
		{
			symbol_par[0] = parameters[3];
			production[3] = Symbol('-',symbol_par,1);
			production[4] = Symbol('$');
			production[5] = Symbol('C',symbol_par1,2);
			production[6] = Symbol(']');
			production[7] = Symbol('C',symbol_par2,2);
		}
		else
		{
			symbol_par[0] = parameters[3];
			production[3] = Symbol('+',symbol_par,1);
			production[4] = Symbol('$');
			production[5] = Symbol('B',symbol_par1,2);
			production[6] = Symbol(']');
			production[7] = Symbol('B',symbol_par2,2);
		}
		string.insert(string.end(),production,production+(sizeof(production)/sizeof(Symbol)));
	}
	else
	{
		string.push_back(s);
	}
}

