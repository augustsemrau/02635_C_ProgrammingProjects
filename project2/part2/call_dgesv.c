#include "matrix_io.h"

/* C prototype for LAPACK routine DGESV */
void dgesv_(const int *n,    /* columns/rows in A          */
            const int *nrhs, /* number of right-hand sides */
            double *A,       /* array A                    */
            const int *lda,  /* leading dimension of A     */
            int *ipiv,       /* pivoting array             */
            double *B,       /* array B                    */
            const int *ldb,  /* leading dimension of B     */
            int *info        /* status code                */
            );

/* call_dgesv : wrapper for LAPACK's DGESV routine

Purpose:
Solves system of equations A*x=b using LAPACK's DGESV routine
Upon exit, the input vector b is overwriten by the solution x.

Return value:
The function returns the output `info` from DGESV with the
following exceptions: the return value is

   -9 if the input A is NULL and/or the input B is NULL
   -10 if A is not a square matrix
   -11 if the dimensions of A and b are incompatible
   -12 in case of memory allocation errors.
*/




int call_dgesv(matrix_t * A, vector_t * b) {
    

    /* First we check the inputs*/

    // We check that they are not NULL pointers
    if (A == NULL || b == NULL) return -9;
    // We check that the A is a square matrix
    if (A->n != A->m) return -10;
    // We check that A and b dimensions are compatible
    if (A->n != b->n) return -11;


    /* Now we will define all inputs not already defined for dgesv_ */

    // 'nrhs' is the number of columns in b, ie. 1
    int nrhs = 1;
    // 'info' will be the output of call_dgesv, which is the exit status of dgesv_
    int info;
    // 'ipiv' is an output array for storing pivoting information
    int * ipiv = (int *) malloc(A->n * sizeof(int));
    if (ipiv == NULL) return -12;


	/* As LAPACK uses column-wise arrays, we transpose the A array */
	
	// Allocate an array of length n*n as it is easier than allocating a 2-d array
	double * A_t = (double *) malloc(A->n*A->n * sizeof(double));
    if (A_t == NULL){
        free(ipiv);  // Free allocated ipiv to avoid memory leakage
        return -12;
    }

    // Copy (transposed) content from A matrix to A_t
    for (int i = 0; i < A->n; i++) 
        for (int j = 0; j < A->n; j++)
            A_t[i*A->n + j] = A->A[j][i];  


    /* Now we call the LAPACK function DGESV */
    dgesv_((const int *) (&A->n), 	// Number of collums/rows in A
            &nrhs,					// Number of collumns in b, 1
            A_t,					// Transposed A as 1-d array
            (const int *) (&A->n),	// Dimension of A
            ipiv,					// Output array for pivoting information
            b->v,					// b vector
            (const int *) (&b->n),	// Length of b
            &info);					// Status code for output
    

	/* Free allocated arrays */
	free(ipiv);
	free(A_t);


    /* Lastly, we return the output 'info' from dgesv_ */
    return info;
}
