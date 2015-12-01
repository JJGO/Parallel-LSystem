#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>
#include <ctime>
#include "fractals.h"

#define SIDE 5
#define R 3

char* gettime(char *buffer);

int main(int argc, char const *argv[])
{
	char* s;
	if(argc < 3)
	{
		return 1;
	}
	int forestSize = strtol(argv[1], &s, 10);
	int iterations = strtol(argv[2], &s, 10);
	std::cout << "Running " << forestSize << " trees for " << iterations << " iterations" << std::endl;
	std::srand(std::time(0)); //use current time as seed for random generator

	std::vector<Tree*> Forest;
	std::vector<std::vector<int>> neighbors;
	std::vector<double> metrics;

	clock_t begin, end;
    double time_spent;

    begin = clock();


	
	// INIT VARIABLES
	std::vector<Point> positions;
	std::vector<int> empty;
	for(int i = 0; i < forestSize; i++)
	{
		double x = (SIDE-1)*std::sin(i);//fRand(0,SIDE);
		double y = SIDE*std::cos(i*i);//fRand(0,SIDE);
		Point p = {x,y};
		Tree *T = new MonopodialTree();
		Forest.push_back(T);
		positions.push_back(p);
		metrics.push_back(0);
		neighbors.push_back(empty);
		for(int j = 0 ; j < i ; j++)
		{
			Point q = positions[j];
			if(pointDistance(p,q) < R)
			{
				neighbors[j].push_back(i);
				neighbors[i].push_back(j);
			}
		}
	}

	// ITERATE

	for(int j = 0 ; j < iterations ; j++)
	{
		for(int i = 0; i < Forest.size() ; i++)
		{
			Forest[i]->next();
			// std::cout << Forest[i] << std::endl;
			metrics[i] = Forest[i]->calculateMetric();
		}


		for(int i = 0; i < Forest.size() ; i++)
		{
			Forest[i]->updateMetric(metrics,neighbors[i]);
			// std::cout << j << " " << i << " " << metrics[i] << std::endl;
		}
	}



	for(int i = 0; i < Forest.size() ; i++)
	{
		printf("%02d %02d %2lf %5lf : ",i,Forest[i]->iteration, Forest[i]->probability, metrics[i] );
		for(int j = 0 ; j < neighbors[i].size(); j++)
		{
			std::cout << neighbors[i][j] << " ";
		}
		std::cout << std::endl;
		
	}

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTIME : %lf seconds\n", time_spent);

	for(int i = 0; i < Forest.size() ; i++)
	{
		delete Forest[i];
	}

	return 0;
}


char* gettime(char* buffer)
{
    time_t rawtime;
    struct tm * timeinfo;
    
    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%Y-%m-%d %I:%M:%S",timeinfo);
    std::string str(buffer);

    return buffer;
}