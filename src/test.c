#include "gwo.h"
#include "fun.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double mc_cornic(double*);
double ackleys(double*);
double beales(double*);
double easom(double*);

int main()
{
	unsigned int wolfs 		= 1000;
	unsigned int iterations = 2000;
	Fun fun;

	fun.size = 2;

	double* bounds 	= (double*) malloc(4*sizeof(double));
	double* min_pos = (double*) malloc(2*sizeof(double));

	//Mc Cornic
	bounds[0] = -1.5;
	bounds[1] = 4;
	bounds[2] = -3;
	bounds[3] = 4;

	fun.bounds 	= bounds;
	fun.val 	= &mc_cornic;

	min_pos[0] = -0.54719;
	min_pos[1] = -1.54719;

	double min_mc_cornic = mc_cornic(min_pos);
	double cmin_mc_cornic = mc_cornic(min(&fun, wolfs, iterations));
	printf("Mc Cornic min: %f, computed: %f\n", min_mc_cornic, cmin_mc_cornic);

	//Ackley's
	bounds[0] = -5;
	bounds[1] = 5;
	bounds[2] = -5;
	bounds[3] = 5;

	fun.bounds 	= bounds;
	fun.val 	= &ackleys;

	min_pos[0] = 0;
	min_pos[1] = 0;

	double min_ackleys = ackleys(min_pos);
	double cmin_ackleys = ackleys(min(&fun, wolfs, iterations));
	printf("Ackleys min: %f, computed: %f\n", min_ackleys, cmin_ackleys);

	//Beales
	bounds[0] = -4.5;
	bounds[1] = 4.5;
	bounds[2] = -4.5;
	bounds[3] = 4.5;

	fun.bounds 	= bounds;
	fun.val 	= &beales;

	min_pos[0] = 3;
	min_pos[1] = 0.5;

	double min_beales = beales(min_pos);
	double cmin_beales = beales(min(&fun, wolfs, iterations));
	printf("Beales min: %f, computed: %f\n", min_beales, cmin_beales);

	//Easom
	bounds[0] = -100;
	bounds[1] = 100;
	bounds[2] = -100;
	bounds[3] = 100;

	fun.bounds 	= bounds;
	fun.val 	= &easom;

	min_pos[0] = M_PI;
	min_pos[1] = M_PI;

	double min_easom = easom(min_pos);
	double cmin_easom = easom(min(&fun, wolfs, iterations));
	printf("Easom min: %f, computed: %f\n", min_easom, cmin_easom);

	return 0;
}

double mc_cornic(double* xs) 
{
	double x = xs[0];
	double y = xs[1];
	return (sin(x + y) + ((x - y) * (x - y)) - (1.5 * x) + (2.5 * y) + 1.0);
}

double ackleys(double* xs) 
{
	double x = xs[0];
	double y = xs[1];
	return(-20 * exp(-0.2 * sqrt(0.5 * ((x * x) + (y * y)))) - exp(0.5 * (cos(2.0 * M_PI * x) + cos(2.0 * M_PI * y))) + 20.0 + M_E);
}

double beales(double* xs)
{
	double x = xs[0];
	double y = xs[1];
	return(((1.5 - x + (x * y)) * (1.5 - x + (x * y))) + ((2.25 - x + (x * y * y)) * (2.25 - x + (x * y * y))) + ((2.625 - x + (x * y * y * y)) * (2.625 - x + (x * y * y * y))));
}

double easom(double* xs)
{
	double x = xs[0];
	double y = xs[1];
	return(-cos(x) * cos(y) * exp(-(((x - M_PI) * (x - M_PI)) + ((y - M_PI) * (y - M_PI)))));
}