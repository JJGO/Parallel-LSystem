#include "main.h"

std::queue<int> get_queue(std::vector< std::vector<int> > &neighbors);

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

	//Parallel variables
	int num_threads;
	std::vector< std::queue<int> > iteration_queues;

	omp_lock_t* queue_lock = new omp_lock_t[iterations];
	for(int j = 0; j < iterations; j++)
	{
		omp_init_lock(&queue_lock[j]);
	}


	begin = omp_get_wtime();
	#pragma omp parallel shared(Forest,neighbors,metrics,num_threads,iteration_queues,queue_lock)
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
			iteration_queues = std::vector< std::queue<int> >(iterations,get_queue(neighbors));
		}

		#pragma omp barrier

		int thread_num = omp_get_thread_num();
		// ITERATE
		int i;
		for(int j = 0; j < iterations; j++)
		{
			while( !iteration_queues[j].empty() )
			{
				omp_set_lock(&queue_lock[j]);
					i = iteration_queues[j].front();
					iteration_queues[j].pop();
				omp_unset_lock(&queue_lock[j]);
				int it = Forest[i]->getIteration();
				bool ready = true;
				for(int k = 0; k < neighbors[i].size() ; k++)
				{
					if( Forest[ neighbors[i][k] ]->iteration < it)
					{
						ready = false;
						break;
					}
				}
				if(ready)
				{
					// printf("P%d deriving system %d on iteration %d\n",thread_num,i,j);
					if(j > 0)
					{
						Forest[i]->updateMetric(metrics,neighbors[i]);
					}
					Forest[i]->next();
					double metric = Forest[i]->calculateMetric();
					#pragma omp critical(metrics)
					{
						metrics[i] = metric;
					}
					if(j < iterations-1)
					{
						omp_set_lock(&queue_lock[j+1]);
							iteration_queues[j+1].push(i);
						omp_unset_lock(&queue_lock[j+1]);
					}
				}
				else
				{
					omp_set_lock(&queue_lock[j]);
						iteration_queues[j].push(i);
					omp_unset_lock(&queue_lock[j]);
				}
			}
		}

	}

	end = omp_get_wtime();
	
	print_forest(Forest, neighbors, metrics);

	std::vector< std::vector<int> > connected_components = get_connected_components(neighbors);
	print_connected_components( connected_components);

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

std::queue<int> get_queue(std::vector< std::vector<int> > &neighbors)
{
	std::queue<int> order;
	std::queue<int> next_nodes;
	int nodes_visited = 0;
	std::vector<bool> explored(neighbors.size(),false);
	int i = 0,j=0;
	while(nodes_visited < neighbors.size() )
	{
		while(explored[i])
		{
			i++;
		}
		next_nodes.push(i);
		explored[i] = true;
		nodes_visited++;
		order.push(i);
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
					order.push(w);
				}
			}
		}
		j++;
	}
	return order;
}

