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

	std::cout << "Running " << forestSize << " trees for " << iterations << " iterations" << std::endl;
	std::srand(std::time(0)); //use current time as seed for random generator

	std::vector<int> empty;

	std::vector<Tree*> Forest;
	std::vector< std::vector<int> > neighbors(forestSize,empty);
	std::vector<double> metrics(forestSize,0.0);

	clock_t begin, end;
    double time_spent;

    begin = clock();

    printf("SIDE = %lf, R = %lf\n",SIDE,R);
	
	// INIT VARIABLES
	std::vector<Point> positions;
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

	// ITERATE

	for(int j = 0 ; j < iterations ; j++)
	{
		for(int i = 0; i < Forest.size() ; i++)
		{
			Forest[i]->next();
			metrics[i] = Forest[i]->calculateMetric();
		}


		for(int i = 0; i < Forest.size() ; i++)
		{
			Forest[i]->updateMetric(metrics,neighbors[i]);
		}
	}
	end = clock();

	print_forest(Forest, neighbors, metrics);
	
	std::vector< std::vector<int> > connected_components = get_connected_components(neighbors);
	print_connected_components( connected_components);

	char buffer[80];

	FILE *f = fopen("../parallel/Results_serial.txt", "a");
	if(f != NULL)
	{
	    fprintf(f, "%s\n", gettime(buffer));
	    fprintf(f,"%d threads\n",1);
	    fprintf(f,"%d trees\n",forestSize);
	    fprintf(f,"%d iterations\n",iterations);
	    for(int i = 0; i < connected_components.size(); i++)
	    {
	    	fprintf(f, "%d ", connected_components[i].size());
	    }
	    fprintf(f, "\n");
	    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	    fprintf(f,"Time : %f seconds\n", time_spent);
	    fprintf(f,"\n=====================\n");
	}

	for(int i = 0; i < Forest.size() ; i++)
	{
		delete Forest[i];
	}

	return 0;
}
