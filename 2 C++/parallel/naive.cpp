#include "main.h"

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
	std::vector<double> metrics(forestSize,0.0);

	int num_threads;

	std::vector<int> systems_processed; // DEBUG
    std::vector<int> symbols_translated; // DEBUG

///// PARALLEL BLOCK
	begin = omp_get_wtime();
	#pragma omp parallel shared(Forest,neighbors,metrics,num_threads)
	{
		#pragma omp master
		{
			// INIT VARIABLES
			std::vector<Point> positions;

			num_threads = omp_get_num_threads();
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

			systems_processed = std::vector<int>(num_threads,0); //DEBUG
			symbols_translated = std::vector<int>(num_threads,0); //DEBUG
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
				double metric = Forest[i]->calculateMetric();
				metrics[i] = metric;
				systems_processed[thread_num]++; //DEBUG
				symbols_translated[thread_num] += Forest[i]->getState().size(); //DEBUG
			}

			#pragma omp for schedule(dynamic)
			for(int i = 0; i < Forest.size() ; i++)
			{
				Forest[i]->updateMetric(metrics,neighbors[i]);
			}
		}
	}
///// PARALLEL BLOCK
	end = omp_get_wtime();

	std::vector< std::vector<int> > connected_components = get_connected_components(neighbors);
	// print_forest(Forest, neighbors, metrics); // VERBOSE
	// print_connected_components( connected_components); // VERBOSE


	char buffer[80];

	FILE *f = fopen("Results_naive.txt", "a");
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
