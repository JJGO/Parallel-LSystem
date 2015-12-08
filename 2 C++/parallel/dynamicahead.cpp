#include "main.h"

std::vector<int> get_order(std::vector< std::vector<int> > &neighbors);

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
		return 1;
	}
	
	
	int forestSize = strtol(argv[1], &s, 10);
	int iterations = strtol(argv[2], &s, 10);

	double SIDE = std::sqrt(forestSize);
	SIDE = fRand(std::sqrt(SIDE),std::sqrt(2)*SIDE);
	double R = 1;

	double begin, end;

	std::vector<int> empty;

	std::vector<Tree*> Forest;
	std::vector< std::vector<int> > neighbors(forestSize,empty);
	std::vector< std::vector<double> > metrics(iterations,std::vector<double>(forestSize,0.0));

	//Parallel variables
	int num_threads;
	std::vector<int> order;

	std::vector<int> systems_processed; // DEBUG
    std::vector<int> symbols_translated; // DEBUG

	begin = omp_get_wtime();
	#pragma omp parallel shared(Forest,neighbors,metrics,forestSize,iterations,order)
	{
		
		#pragma omp master
		{
			// INIT VARIABLES
			num_threads = omp_get_num_threads();
			std::vector<Point> positions;
			std::cout << "Running " << forestSize << " trees for " << iterations << " iterations on " << num_threads << " processors" << std::endl;
			
			for(int i = 0; i < forestSize; i++)
			{
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
			order = get_order(neighbors);
			systems_processed = std::vector<int>(num_threads,0); //DEBUG
			symbols_translated = std::vector<int>(num_threads,0); //DEBUG
			
		}

		#pragma omp barrier

		int N = forestSize;
		int T = iterations;
		int thread_num = omp_get_thread_num();
		// ITERATE
		#pragma omp for schedule(dynamic)
		for(int x = 0; x < N*T; x++)
		{
			int i = order[x%N];
			int j = x/N;

			while(Forest[i]->iteration < j);
			bool ready = false;
			while(!ready)
			{
				ready = true;
				for(int k = 0; k < neighbors[i].size() ; k++)
				{
					if( Forest[ neighbors[i][k] ]->iteration < j)
					{
						ready = false;
						break;
					}
				}
			}

			if(j > 0)
			{
				Forest[i]->updateMetric(metrics[j-1],neighbors[i]);
			}
			Forest[i]->next();

			double metric = Forest[i]->calculateMetric();
			metrics[j][i] = metric;
			systems_processed[thread_num]++; //DEBUG
			symbols_translated[thread_num] += Forest[i]->getState().size(); //DEBUG
		}

	}


	end = omp_get_wtime();
	
	std::vector< std::vector<int> > connected_components = get_connected_components(neighbors);
	// for(int i = 0; i < order.size(); i++) //VERBOSE
	// 	std::cout << order[i] << " "; //VERBOSE
	// std::cout << std::endl; //VERBOSE
	// print_forest(Forest, neighbors, metrics[iterations-1]); //VERBOSE
	// print_connected_components( connected_components); //VERBOSE

	char buffer[80];

	FILE *f = fopen("Results_dynamicahead.txt", "a");
	if(f != NULL)
	{
	    fprintf(f, "%s\n", gettime(buffer));
	    fprintf(f,"%d threads\n",num_threads);
	    fprintf(f,"%d trees\n",forestSize);
	    fprintf(f,"%d iterations\n",iterations);
	    fprintf(f,"%lf %lf\n",SIDE,R);
	    for(int i = 0; i < connected_components.size(); i++)
	    {
	    	fprintf(f, "%d ", connected_components[i].size());
	    }
	    fprintf(f, "\n");
	    fprintf(f,"Proc   Systems   Symbols\n");//DEBUG
	    for(int i = 0; i < num_threads; i++)//DEBUG
	    {//DEBUG
	        fprintf(f,"  %02d  %03d  %03d\n",i,systems_processed[i],symbols_translated[i]);//DEBUG
	    }//DEBUG
	    fprintf(f,"Time : %f seconds\n", end-begin);
	    fprintf(f,"\n=====================\n");
	}

	for(int i = 0; i < Forest.size() ; i++)
	{
		delete Forest[i];
	}

	return 0;
}

std::vector<int> get_order(std::vector< std::vector<int> > &neighbors)
{
	std::vector<int> order( neighbors.size(), 0);
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
		order[nodes_visited++] = i;
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
					order[nodes_visited++] = w;
					next_nodes.push(w);
				}
			}
		}
		j++;
	}
	return order;
}

