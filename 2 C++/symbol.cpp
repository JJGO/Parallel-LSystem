#include "symbol.h"

Symbol::Symbol()
{
	character = 0;
}
Symbol::Symbol(const char c)
{
	character = c;
}
Symbol::Symbol(const char c, const int n)
{
	character = c;
	for(int i = 0; i < n ; i++)
	{
		parameters.push_back(0.0);
	}
}
Symbol::Symbol(const char c, std::vector<double> p)
{
	character = c;
	parameters = p;
}
Symbol::Symbol(const char c, const double p[], int n)
{
	character = c;
	for(int i = 0; i < n ; i++)
	{
		parameters.push_back(p[i]);
	}
}

std::vector<double> Symbol::getParameters() const
{
	return parameters;
}

bool Symbol::operator==(const Symbol &other) const {
	if (character == other.character)
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& output, const Symbol &s){
	output << s.character;
	int n = s.parameters.size();
	if(n > 0)
	{
		output << '(';
		for(int i = 0 ; i < n-1 ; i++)
		{
			output << s.parameters[i] << ", ";
		}
		output << s.parameters[n-1] << ')';
	}
	return output;
}


