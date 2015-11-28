#include "lsystem.h"

LSystem::LSystem()
{
	reset();
}

LSystem::LSystem(std::vector<Symbol> ax)
{
	axiom = ax;
	reset();
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
	string.push_back(s);
}

std::ostream& operator<<(std::ostream& output, const LSystem &l){
	std::vector<Symbol> state = l.getState();
	for( int i = 0; i < state.size() ; i++)
	{
		output << state[i];// << std::endl;
	}
	return output;
}

DLSystem::DLSystem(std::vector<Symbol> axiom, std::vector<double> par)
:LSystem(axiom)
{
	parameters = par;
}

double DLSystem::calculateMetric()
{
	return 0.0;
}

void DLSystem::updateMetric(std::vector<double> neighbor_metrics)
{
	return;
}

LGroup::LGroup(std::vector<DLSystem> s)
{
	systems = s;
}

std::vector< std::vector<Symbol> > LGroup::getStates() const
{
	std::vector< std::vector<Symbol> > states;

	for(int i = 0 ; i < systems.size() ; i++)
	{
		states.push_back(systems[i].getState());
	}

}

void LGroup::reset()
{
	for(int i = 0 ; i < systems.size() ; i++)
	{
		systems[i].reset();
	}
}

void LGroup::next()
{
	std::vector<double> global_metrics;
	for(int i = 0 ; i < systems.size() ; i++)
	{
		systems[i].next();
		global_metrics.push_back( systems[i].calculateMetric() );
	}

	for(int i = 0 ; i < systems.size() ; i++)
	{
		systems[i].updateMetric(global_metrics);
	}

}

void LGroup::iterate(int n)
{
	for(int i = 0 ; i < n ; i++)
	{
		next();
	}
}

void LGroup::addSystem(DLSystem l)
{
	systems.push_back(l);
}

