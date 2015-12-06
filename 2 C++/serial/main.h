#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <omp.h>
#include <ctime>
#include "fractals.h"
#include <queue>

char* gettime(char *buffer);

std::vector< std::vector<int> > get_connected_components(std::vector<std::vector<int> > &neighbors);
void print_connected_components(std::vector<std::vector<int> > connected_components);
void print_forest(std::vector<Tree*> &Forest, std::vector< std::vector<int> > &neighbors, std::vector<double> &metrics);

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

std::vector< std::vector<int> > get_connected_components(std::vector< std::vector<int> > &neighbors)
{
	std::vector<int> empty_vec;
	std::vector< std::vector<int> > connected_components;
	int nodes_visited = 0;
	std::vector<bool> explored(neighbors.size(),false);
	std::queue<int> next_nodes;
	int i = 0,j=0;
	while(nodes_visited < neighbors.size())
	{
		while(explored[i])
		{
			i++;
		}
		next_nodes.push(i);
		explored[i] = true;
		nodes_visited++;
		connected_components.push_back(empty_vec);
		connected_components[j].push_back(i);
		// printf("CC%d : %d ",j,i)
		while(!next_nodes.empty())
		{
			int v = next_nodes.front();
			next_nodes.pop();
			for(int k = 0 ; k < neighbors[v].size() ; k++)
			{
				int w = neighbors[v][k];
				if(!explored[w])
				{
					explored[w] = true;
					nodes_visited++;
					next_nodes.push(w);
					connected_components[j].push_back(w);
				}
			}
		}
		j++;
	}
	return connected_components;
}

void print_connected_components(std::vector< std::vector<int> > connected_components)
{
	for(int i = 0; i < connected_components.size(); i++)
	{
		printf("CC%02d(%d) : ", i,connected_components[i].size());
		for(int j = 0; j < connected_components[i].size() ; j++)
		{
			printf("%d ",connected_components[i][j]);
		}
		printf("\n");
	}
	return;
}

void print_forest(std::vector<Tree*> &Forest, std::vector< std::vector<int> > &neighbors, std::vector<double> &metrics)
{
	for(int i = 0; i < Forest.size() ; i++)
	{
		printf("%02d %02d %2lf %5lf : ",i,Forest[i]->iteration, Forest[i]->probability, metrics[i] );
		for(int j = 0 ; j < neighbors[i].size(); j++)
		{
			std::cout << neighbors[i][j] << " ";
		}
		std::cout << std::endl;
		
	}
}