#include "gwo.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

// utils
double next_rand(double min, double max);
double** initialize(Fun* function, int wolfs);

// Grey Wolf Optimizer
double* optimize(Fun* function, enum Opt optimum, int wolfs, int iterations)
{
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

	for(uint iteration = 0; iteration < iterations; iteration++){
		for(uint position = 0; position < wolfs; position++){
			double fitness = function->val(positions[position]);

			if(fitness > alpha_score) {
				alpha_score = fitness;
				alpha_position = positions[position];
			}

			if(fitness > alpha_score && fitness < beta_score) {
				beta_score = fitness;
				beta_position = positions[position];
			}

			if(fitness > alpha_score && fitness > beta_score && fitness < delta_score) {
				delta_score = fitness;
				delta_position = positions[position];
			}
		}

		double a = 2.0 - iteration * (2.0 / iterations);

		for(uint i = 0; i < wolfs; i++){
			for(uint j = 0; j < function->size; j++){
				double d_alpha = abs(2.0 * next_rand(0.0, 1.0) * alpha_position[j] - positions[i][j]);
				double x1 = alpha_position[j] - 2.0 * a * next_rand(0.0,1.0)-1.0 * d_alpha;

				double d_beta = abs(2.0 * next_rand(0.0, 1.0) * beta_position[j] - positions[i][j]);
				double x2 = beta_position[j] - 2.0 * a * next_rand(0.0,1.0)-1.0 * d_beta;

				double d_delta = abs(2.0 * next_rand(0.0, 1.0) * delta_position[j] - positions[i][j]);
				double x3 = delta_position[j] - 2.0 * a * next_rand(0.0,1.0)-1.0 * d_delta;

				positions[i][j] = (x1 + x2 + x3) / 3.0;
			}
		}
	}

	

	return alpha_position;
}


// api
double* min(Fun* function, int wolfs, int iterations)
{
	return optimize(function, MIN, wolfs, iterations);
}

double* max(Fun* funciton, int wolfs, int iterations)
{
	return optimize(funciton, MAX, wolfs, iterations);
}


//utils impl
double next_rand(double min, double max)
{
	return (min + (rand() / (RAND_MAX / (max - min))));
}

double** initialize(Fun* function, int wolfs)
{
	double** positions = (double**) malloc(wolfs*sizeof(double));
	for(uint x = 0; x < wolfs; x++)
		positions[x] = (double*) malloc(function->size*sizeof(double));

	for(uint x = 0; x < wolfs; x++)
		for(uint y = 0; y < function->size; y++)
			positions[x][y] = next_rand(function->bounds[y*2], function->bounds[(y*2)+1]);	

	return positions;
}