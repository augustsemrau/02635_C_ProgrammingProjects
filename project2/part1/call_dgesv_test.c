/* Include header file */
#include "matrix_io.h"

/* Include prototypes */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

matrix_t * malloc_matrix(unsigned long m, unsigned long n);
void free_matrix(matrix_t * pm);
vector_t * malloc_vector(unsigned long n);
void free_vector(vector_t * pv);


matrix_t * malloc_matrix(unsigned long m, unsigned long n) {
	size_t i;
	matrix_t * pm=NULL;
	pm = malloc(sizeof(*pm));
	if ( pm == NULL ) {
		MEM_ERR;
		return NULL;
	}
	pm->m = m;
	pm->n = n;
	pm->A = malloc(m*sizeof(*pm->A));
	if ( pm->A == NULL ) {
		MEM_ERR;
		free(pm);
		return NULL;
	}
	pm->A[0] = calloc(m*n,sizeof(*pm->A[0]));
	if ( pm->A[0] == NULL ) {
		MEM_ERR;
		free(pm->A);
		free(pm);
		return NULL;
	}
	for (i=1; i<m; i++) pm->A[i] = pm->A[0] + i*n;
	return pm;
}
void free_matrix(matrix_t * pm) {
	if ( pm == NULL ) return;
	free(pm->A[0]);
	free(pm->A);
	free(pm);
	return;
}



vector_t * malloc_vector(unsigned long n) {
	vector_t * pv = malloc(sizeof(*pv));
	if ( pv == NULL ) {
		MEM_ERR;
		return NULL;
	}
	pv->n = n;
	pv->v = calloc(n,sizeof(*pv->v));
	if ( pv->v == NULL ) {
		MEM_ERR;
		free(pv);
		return NULL;
	}
	return pv;
}
void free_vector(vector_t * pv) {
	if ( pv == NULL ) return;
	free(pv->v);
	free(pv);
}


/* Main function for testing call_dgesv_ as written in call_dgesv.c */
int main(int argc, char const *argv[]){




    /* First we allocate a matrix A using the matrix_t struct */
    /*
    // First we allocate a vector
    double ** R = (double **) malloc(n * sizeof(double *));
    // Check for succesful intitial allocation
    if (R == NULL) return -2;
    
    // Second we allocate every collumn
    for (int i = 0; i < n; i++){
        R[i] = (double *) malloc(n * sizeof(double));
        // Again check for succesful allocation
        if (R[i] == NULL) return -2;
    }
    */
    /* Dynamically allocate length n one-dimensional vector of double pointers, b */
    /*
    double * b = (double *) malloc(n * sizeof(double));
    if (b == NULL) return -2;
    */



    matrix_t * A = malloc_matrix(4, 4);
   	vector_t * b = malloc_vector(4);

    /* I choose values for these tests that I have crosschecked with maple */

    // First for R
    
    A->A[0][0] = 1;
    A->A[0][1] = 2;
    A->A[0][2] = 3;
    A->A[0][3] = 4;

    A->A[1][0] = 0;
    A->A[1][1] = 5;
    A->A[1][2] = 6;
    A->A[1][3] = 7;

    A->A[2][0] = 0;
    A->A[2][1] = 0;
    A->A[2][2] = 8;
    A->A[2][3] = 9;
    
    A->A[3][0] = 0;
    A->A[3][1] = 0;
    A->A[3][2] = 0;
    A->A[3][3] = 10;
    
    // And for b
    b->v[0] = 1;
    b->v[1] = 2;
    b->v[2] = 3;
    b->v[3] = 4;

    // Print b before substitution
    printf("The vector b before forward substitution:\n");
    for (int ind = 0; ind < b->n; ind++){
        printf("%lf\n", b->v[ind]);
    }

    /* Call call_dgesv function */
    int x = call_dgesv(A, b);
    printf("Exit status: %d", x);

    // Print b after substitution
    printf("\nThe vector b after forward substitution:\n");
    for (int ind = 0; ind < b->n; ind++){
        printf("%lf\n", b->v[ind]);
        }

	free_matrix(A);
	free_vector(b);

    double data[4] = {5.0, -2.0, 2.0, 0.0};
    data[1] *= 2.0;
    --data[1];
    printf("data[1] = %lf", data[1]);

    return 0;
}


