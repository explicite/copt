#include "gwo.h"
#include "fun.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double mc_cornic(double*);

int main()
{
	Fun fun;

	fun.size = 2;

	double* bounds = (double*) malloc(4*sizeof(double));
	bounds[0] = -1.5;
	bounds[1] = 4;
	bounds[2] = -3.0;
	bounds[3] = 4.0;
	fun.bounds = bounds;

	fun.val = &mc_cornic;

	double* min_pos = (double*) malloc(2*sizeof(double));
	min_pos[0] = -0.54719;
	min_pos[1] = -1.54719;

	double min_val = mc_cornic(min_pos);

	double computed_min_val = mc_cornic(min(&fun, 10000, 1000));

	printf("%f, %f\n", min_val, computed_min_val);
	return 0;
}

double mc_cornic(double* xs) {
	double x = xs[0];
	double y = xs[1];
	return (sin(x + y) + ((x - y) * (x - y)) - (1.5 * x) + (2.5 * y) + 1.0);
}