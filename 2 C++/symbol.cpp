#include "symbol.h"

Symbol::Symbol()
{
	character = 0;
	numpar = 0;
}

Symbol::Symbol(const char c)
{
	character = c;
	numpar = 0;
}

Symbol::Symbol(const char c, const int n)
{
	character = c;
	if(n > 0)
	{
		numpar = n;
		parameters = new double[numpar];
		std::fill(parameters, parameters+numpar, 0.0);
	}
	else
	{
		numpar = 0;
	}
}

Symbol::Symbol(const char c, const int n, const double p[])
{
	character = c;
	if(n > 0)
	{
		numpar = n;
		parameters = new double[numpar];
		std::copy(p,p+numpar,parameters);
	}else{
		numpar = 0;
	}
	
}

Symbol::~Symbol()
{
	if(this->numpar > 0)
	{
    	delete[] parameters;
	}
}

bool Symbol::operator==(const Symbol &other) const {
	if (character == other.character)
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& output, const Symbol &s){
	output << s.character;
	if(s.numpar > 0)
	{
		output << '(';
		for(int i = 0 ; i < s.numpar-1 ; i++)
		{
			output << s.parameters[i] << ", ";
		}
		output << s.parameters[s.numpar-1] << ')';
	}
	return output;
}


