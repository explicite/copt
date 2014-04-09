#pragma once
#include <stdio.h>

typedef struct
{
	unsigned int size;
	double* bounds;
	double (*val)(double*);
} Fun;
