#ifndef FWDSUB_H
#define FWDSUB_H

#include <stdlib.h>
#include <math.h>

// Initiate function 'fwdsub'
int fwdsub(
unsigned long n, 
double alpha, 
double **R, /* two-dimensional array, row-major */
double *b /* one-dimensional array */
);

#endif