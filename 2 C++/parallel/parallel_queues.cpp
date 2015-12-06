#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>
#include <omp.h>
#include <ctime>
#include "fractals.h"

// #define SIDE 5
// #define R 3

char* gettime(char *buffer);

std::vector< std::vector<int> > get_connected_components(int size, std::vector<std::vector<int> > &neighbors);
void print_connected_components(std::vector<std::vector<int> > connected_components);
int main(int argc, char const *argv[])
{
	char* s;
	std::srand(std::time(0)); //use current time as seed for random generator
	int r = rand() % 1000;
	for(int i = 0; i < r; i++)
	{
		rand();
	}
	if(argc < 3)
	{
		int forestSize = strtol(argv[1], &s, 10);
		for(int i = 0 ; i < forestSize ; i++)
		{
			printf("%lf\n",fRand(1,std::sqrt(10)));
		}
		return 1;
	}
	const double PI = std::atan(1.0)*4;
	
	int forestSize = strtol(argv[1], &s, 10);
	int iterations = strtol(argv[2], &s, 10);

	double SIDE = std::sqrt(forestSize);
	SIDE = fRand(std::sqrt(SIDE),std::sqrt(2)*SIDE);
	double R = 1;

	double begin, end;

	std::vector<int> empty;

	std::vector<Tree*> Forest;
	std::vector< std::vector<int> > neighbors(forestSize,empty);
	std::vector<double> metrics(forestSize,0.0);

	int num_threads;

	begin = omp_get_wtime(); //PARALLELO
	#pragma omp parallel shared(Forest,neighbors,metrics,num_threads)
	{
		#pragma omp master
		{
			// INIT VARIABLES
			std::vector<Point> positions;

			num_threads = omp_get_num_threads();
			std::cout << "Running " << forestSize << " trees for " << iterations << " iterations on " << num_threads << " processors" << std::endl;
			printf("SIDE = %lf, R = %lf\n",SIDE,R);
			
			for(int i = 0; i < forestSize; i++)
			{
				// double x = std::fabs((SIDE-1)*std::sin(i));
				// double y = std::fabs(SIDE*std::cos(i*i));
				double x = fRand(0,SIDE);
				double y = fRand(0,SIDE);
				Point p = {x,y};
				Tree *T = new MonopodialTree();
				Forest.push_back(T);
				positions.push_back(p);
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
		}

		#pragma omp barrier

		int thread_num = omp_get_thread_num();
		// ITERATE

		for(int j = 0 ; j < iterations ; j++)
		{
			#pragma omp for schedule(dynamic)
			for(int i = 0; i < Forest.size() ; i++)
			{
				Forest[i]->next();
				// std::cout << Forest[i] << std::endl;
				metrics[i] = Forest[i]->calculateMetric();
				// printf("Proc %d working on tree %02d iteration %02d : %lf\n",omp_get_thread_num(),i,j,metrics[i] ); //VERBOSE
			}

			#pragma omp barrier

			#pragma omp for schedule(dynamic)
			for(int i = 0; i < Forest.size() ; i++)
			{
				Forest[i]->updateMetric(metrics,neighbors[i]);
				// std::cout << j << " " << i << " " << metrics[i] << std::endl;
			}
			// printf("Proc %d FINISHED iteration %02d\n",omp_get_thread_num(),j ); //VERBOSE
			#pragma omp barrier
		}

	}

	end = omp_get_wtime(); //PARALLELO

	for(int i = 0; i < Forest.size() ; i++)
	{
		printf("%02d %02d %2lf %5lf : ",i,Forest[i]->iteration, Forest[i]->probability, metrics[i] );
		for(int j = 0 ; j < neighbors[i].size(); j++)
		{
			std::cout << neighbors[i][j] << " ";
		}
		std::cout << std::endl;
		
	}
	
	std::vector< std::vector<int> > connected_components = get_connected_components(forestSize,neighbors);
	// print_connected_components( connected_components);


	char buffer[80];

	FILE *f = fopen("parallel_queues.txt", "a");
	if(f != NULL)
	{
	    fprintf(f, "%s\n", gettime(buffer));
	    fprintf(f,"%d threads\n",num_threads);
	    fprintf(f,"%d trees\n",forestSize);
	    fprintf(f,"%d iterations\n",iterations);
	    for(int i = 0; i < connected_components.size(); i++)
	    {
	    	fprintf(f, "%d ", connected_components[i].size());
	    }
	    fprintf(f, "\n");
	    fprintf(f,"Time : %f seconds\n", end-begin);
	    fprintf(f,"\n=====================\n");
	}

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

std::vector< std::vector<int> > get_connected_components(int size, std::vector< std::vector<int> > &neighbors)
{
	std::vector<int> empty_vec;
	std::vector< std::vector<int> > connected_components;
	int nodes_visited = 0;
	std::vector<bool> explored(size,false);
	std::stack<int> next_nodes;
	int i = 0,j=0;
	while(nodes_visited < size)
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
			int v = next_nodes.top();
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