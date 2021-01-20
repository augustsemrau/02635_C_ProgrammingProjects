#include <stdlib.h>
#include <stdio.h>
#include "matrix_io.h"

/* call_dgesv' has to be copied into this script, as it would otherwise not compile in codejudge 
where the function isn't existing... */


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

/* The function written for part 1 */
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
        free(ipiv);
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






int main(int argc, char *argv[]) {

    if (argc != 4) {
    fprintf(stderr,"Usage: %s A b x\n", argv[0]);
    return EXIT_FAILURE;
    }

    /* First, we need to read the two given input .txt files */

    // Read the matrix from the first given .txt file
    matrix_t * A = read_matrix(argv[1]); 

    // Read the vector from the second given .txt file
    vector_t * b = read_vector(argv[2]);


    /* We check that reading the inputs were succesful and will work in 'call_dgesv', 
    else print to stderr and return failure */

    // We check that they are not NULL pointers
    if (A == NULL){
        fprintf(stderr, "FALIURE: Unable to read matrix from the first given .txt file");
        free_matrix(A);
        free_vector(b);
        return EXIT_FAILURE;
    } 
    if (b == NULL){
        fprintf(stderr, "FALIURE: Unable to read vector from the first given .txt file");
        free_matrix(A);
        free_vector(b);
        return EXIT_FAILURE;
    }

    // We check that the A is a square matrix
    if (A->n != A->m){
        fprintf(stderr, "FALIURE: The given matrix is not a square matrix");
        free_matrix(A);
        free_vector(b);
        return EXIT_FAILURE;
    }
    // We check that A and b dimensions are compatible
    if (A->n != b->n){
        fprintf(stderr, "FALIURE: The dimensions of the given matrix and vector do not match");
        free_matrix(A);
        free_vector(b);
        return EXIT_FAILURE;
    }


    /* Now we solve the given system of equations using the function 'call_dgesv' created in part 1 */
    int info = call_dgesv(A, b);

    // if the 'dgesv_' function inside 'call_dgesv' did not finish correctly, we return error
    if (info != 0){
        fprintf(stderr, "FALIURE: LAPACK function dgesv_ did not finish correctly, returning error code: %d", info);
        free_matrix(A);
        free_vector(b);
        return EXIT_FAILURE;
    }


    /* When the system is solved, we write the solution to the third given .txt file */
    int write_info = write_vector(argv[3], b);

    // We save the output status of 'write_vector' to check that it finished succesfully
    if (write_info != 0){
        fprintf(stderr, "FALIURE: Writing the solution to the third given .txt file was unsuccessfull");
        free_matrix(A);
        free_vector(b);
        return EXIT_FAILURE;
    }


    /* Lastly, we free A and b and return succesful status EXIT_SUCCESS */
    free_matrix(A);
    free_vector(b);
    
    return EXIT_SUCCESS;
}