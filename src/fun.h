#pragma once
#include <stdio.h>

typedef struct
{
	size_t size;
	double* bounds;
	double (*val)(double*);
} Fun;
