#include "lsystem.h"

LSystem::LSystem(std::vector<Symbol> ax)
{
	axiom = ax;
	this->reset();
}

std::vector<Symbol> LSystem::getState() const
{
	return state;
}

void LSystem::reset()
{
	state = axiom;
	iteration = 0;
}

void LSystem::next()
{
	iteration++;
	std::vector<Symbol> new_state;
	for( int i = 0; i < state.size() ; i++)
	{
		substitute(state[i],new_state);
	}
	state = new_state;
}

void LSystem::iterate(int n)
{
	for(int i = 0 ; i < n ; i++)
	{
		next();
	}
}

void LSystem::substitute(Symbol s, std::vector<Symbol> &string)
{
	Symbol F('F');
	if(s == F)
	{
		Symbol p('+');
		Symbol m('-');
		Symbol production[9] = {F, p, F, m, F, m, F, p, F};
		string.insert(string.end(),production,production+(sizeof(production)/sizeof(Symbol)));
	}else
	{
		string.push_back(s);
	}
}

std::ostream& operator<<(std::ostream& output, const LSystem &l){
	std::vector<Symbol> state = l.getState();
	for( int i = 0; i < state.size() ; i++)
	{
		output << state[i];// << std::endl;
	}
	return output;
}
