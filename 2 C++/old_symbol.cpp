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
	numpar = n > 0 ? n : 0;
	if(n > 0)
	{
		parameters = new double[numpar];
		std::fill(parameters, parameters+numpar, 0.0);
	}
}

Symbol::Symbol(const char c, const int n, const double p[])
{
	character = c;
	numpar = n > 0 ? n : 0;
	if(n > 0)
	{
		parameters = new double[numpar];
		std::copy(p,p+numpar,parameters);
	}
}

Symbol::Symbol( const Symbol &obj)
{
	character = obj.character;
	numpar = obj.numpar > 0 ? obj.numpar : 0;
	if(numpar > 0)
	{
		parameters = new double[numpar];
		std::copy(obj.parameters,obj.parameters+numpar,parameters);
	}
}

Symbol::~Symbol()
{
	if(numpar > 0)
	{
    	delete[] parameters;
	}
}

bool Symbol::operator==(const Symbol &other) const {
	if (character == other.character)
		return true;
	return false;
}

Symbol& Symbol::operator = (const Symbol &other)
{
	character = other.character;
	numpar = other.numpar > 0 ? other.numpar : 0;
	if( numpar > 0)
	{
		parameters = new double[numpar];
		std::copy(other.parameters,other.parameters+numpar,parameters);
	}
	return *this;
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


