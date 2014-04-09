#include "gwo.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <omp.h>

// utils
double next_rand(double min, double max);
double** initialize(Fun* function, unsigned int wolfs);
void back_to_space(double** positions, double* bounds, unsigned int size, unsigned int wolfs);

// Grey Wolf Optimizer
double* optimize(Fun* function, enum Opt optimum, unsigned int wolfs, unsigned int iterations)
{
	srand(time(NULL));
	double INF = 0;

	switch(optimum)
	{
		case MIN:		
			INF = INFINITY;
			break;

		case MAX:
			INF = -INFINITY;
			break;
	} 

	double*	alpha_position 	= (double*) calloc(function->size, sizeof(double));
	double 	alpha_score		= INF;

	double*	beta_position 	= (double*) calloc(function->size, sizeof(double));
	double 	beta_score		= INF;

	double* delta_position 	= (double*) calloc(function->size, sizeof(double));
	double  delta_score		= INF;

	double** positions 		= initialize(function, wolfs);

	for(unsigned int iteration = 0; iteration < iterations; iteration++){
		for(unsigned int position = 0; position < wolfs; position++){
			//Return back the search agents that go beyond the boundaries of the search space
			back_to_space(positions, function->bounds, function->size, wolfs);

			double fitness = function->val(positions[position]);

			if(fitness < alpha_score) {
				alpha_score = fitness;
				memcpy(alpha_position, positions[position], function->size*sizeof(double));
			}

			if(fitness > alpha_score && fitness < beta_score) {
				beta_score = fitness;
				memcpy(beta_position, positions[position], function->size*sizeof(double));
			}

			if(fitness > alpha_score && fitness > beta_score && fitness < delta_score) {
				delta_score = fitness;
				memcpy(delta_position, positions[position], function->size*sizeof(double));
			}
		}

		double a = 2.0 - iteration * (2.0 / iterations);

		#pragma omp parallel for
		for(unsigned int i = 0; i < wolfs; i++){
			for(unsigned int j = 0; j < function->size; j++){
				double d_alpha 	= abs((2.0*next_rand(0.0, 1.0))*alpha_position[j] - positions[i][j]);
				double x1 		= alpha_position[j] - ((2.0*a*next_rand(0.0, 1.0)) - 1.0) * d_alpha;

				double d_beta 	= abs((2.0*next_rand(0.0, 1.0))*beta_position[j] - positions[i][j]);
				double x2 		= beta_position[j] - ((2.0*a*next_rand(0.0, 1.0)) - 1.0) * d_beta;

				double d_delta 	= abs((2.0*next_rand(0.0, 1.0))*delta_position[j] - positions[i][j]);
				double x3 		= delta_position[j] - ((2.0*a*next_rand(0.0, 1.0)) - 1.0) * d_delta;

				positions[i][j] = (x1 + x2 + x3) / 3.0;
			}
		}
	}

	return alpha_position;
}


// api
double* min(Fun* function, unsigned int wolfs, unsigned int iterations)
{
	return optimize(function, MIN, wolfs, iterations);
}

double* max(Fun* funciton, unsigned int wolfs, unsigned int iterations)
{
	return optimize(funciton, MAX, wolfs, iterations);
}


//utils impl
double next_rand(double min, double max)
{
	return (min + (rand() / (RAND_MAX / (max - min))));
}

double** initialize(Fun* function, unsigned int wolfs)
{
	double** positions = (double**) malloc(wolfs*sizeof(double));
	#pragma omp parallel for
	for(unsigned int x = 0; x < wolfs; x++)
		positions[x] = (double*) malloc(function->size*sizeof(double));

	#pragma omp parallel for
	for(unsigned int x = 0; x < wolfs; x++)
		for(unsigned int y = 0; y < function->size; y++)
			positions[x][y] = next_rand(function->bounds[y*2], function->bounds[(y*2)+1]);

	
	return positions;
}

void back_to_space(double** positions, double* bounds, unsigned int size, unsigned int wolfs)
{
	#pragma omp parallel for
	for(unsigned int x = 0; x < wolfs; x++)
		for(unsigned int y = 0; y < size; y++)
			if(positions[x][y] >= bounds[(y*2)+1] || positions[x][y] <= bounds[(y*2)])
				positions[x][y] = next_rand(bounds[y*2], bounds[(y*2)+1]);
}
