#include "fractals.h"
#include <cmath>

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

