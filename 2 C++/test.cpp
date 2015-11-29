#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "fractals.h"

int main(int argc, char const *argv[])
{
	std::srand(std::time(0)); //use current time as seed for random generator
	clock_t begin, end;
	double time_spent;

	begin = clock();

	int forestSize = 5;

	// std::vector<Tree*> Forest;
	std::vector<Tree*> Forest;
	std::vector<Point> positions;
	std::vector< std::vector<int> > neighbors;
	std::vector<double> metrics;


	for(int i = 0; i < forestSize; i++)
	{
		double x = fRand(0,20);
		double y = fRand(0,20);
		Point p = {x,y};
		// MonopodialTree T;
		Tree *T = new MonopodialTree();
		Forest.push_back(T);
		positions.push_back(p);
		metrics.push_back(0);
	}

	for(int j = 0 ; j < 15 ; j++)
	{
		for(int i = 0; i < Forest.size() ; i++)
		{
			Forest[i]->next();
			// std::cout << Forest[i] << std::endl;
			metrics[i] = Forest[i]->calculateMetric();
		}

		for(int i = 0; i < Forest.size() ; i++)
		{
			Forest[i]->updateMetric(metrics);
			std::cout << j << " " << i << " " << metrics[i] << std::endl;
		}
	}
	
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << "\nTIME :" << time_spent << "seconds" << std::endl;

	for(int i = 0; i < Forest.size() ; i++)
	{
		delete Forest[i];
	}

	return 0;
}