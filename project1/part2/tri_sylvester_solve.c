#include <stdlib.h>
#include <math.h>
#include "matrix.h"


/* Initializing fwdsub function. */
int fwdsub(unsigned long n, double alpha, double ** R, double * b);






int tri_sylvester_solve(const matrix_t *R, matrix_t *C) {
    

    /* First we want to check that the inputs are valid and the dimension fit. */
    // We check if the inputs are NULL pointers.
    if (R == NULL || C == NULL || R->A == NULL || C->A == NULL) return -2;
    // Here, m and n need to be equal for each matrix, and R and C need to match.
    if (R->m != R->n || C->m != C->n || R->m != C->m) return -2;


    /* To solve the Sylvester Equation we will follow the two steps given on Codejudge.
    We will perform the two steps for each row of matrix C, ie. we loop over rows c_k. */
    for (int k = 0; k < C->m; k++){
        
        /* Before computing the two steps, we define c_k as a seperate array.
        In the spirit of this assignment, we define it using the given vector structure. */
        // Initiate vector structure c_k.
        struct vector c_k;

        // We define the vectors length.
        c_k.n = C->n;

        // For the vector, we dynamically allocate an array with the given length.
        c_k.v = (double *) malloc(c_k.n * sizeof(double));
        if (c_k.v == NULL) return -500;

        // We then append the k'th row of C to c_k.v
        for (int i = 0; i < c_k.n; i++){
            c_k.v[i] = C->A[k][i];
        }
        

        /* First step of overwriting c_k is now carried out. */
        // This step is a vector-wise operation, but we use an extra loop to make it elementwise.
        for (int i = 0; i < c_k.n; i++){

            // First we want to calculate sum(C[j][i]*R[j][k]).
            double sum = 0;
            for (int j = 0; j < k; j++){
                sum = sum + (C->A[j][i] * R->A[j][k]);
            }

            // We now subtract it from c_k[i].
            c_k.v[i] = c_k.v[i] - sum;
        }


        /* The second step is now performed by running fwdsub. */
        // We make sure to return -1 for numerical faliure inside fwdsub
        if (fwdsub(C->m, R->A[k][k], R->A, c_k.v)) return -1;


        // With the solved row c_k, we reimplement this into the matrix C.
        for (int i = 0; i < c_k.n; i++){
            C->A[k][i] = c_k.v[i];
        }

        // Lastly, we free the memory of c_k so it can be allocated again.
        free(c_k.v); 
    }

    /* The Sylvester equation is now solved, and we return 0 to finish. */
    return 0;
}

 



/* fwdsub function copied directly from part 1 of the assignment. */

int fwdsub(unsigned long n, double alpha, double ** R, double * b){

    /* We perform forward substitution on each eleḿent b[k] for k= 0 up to n-1 
    b[k] is overwritten by the solution x[k] given by the formula in Ćodejudge. */
    for (int k = 0; k < n; k++){

        // Before any substitution, we check that the division will be legal, else we return -1
        if ((alpha + R[k][k]) == 0) return -1; 

        // First we calculate the sum: sum(b[i] * R[i][k])
        double sum = 0;
        for (int i = 0; i < k; i++){
            sum = sum + b[i] * R[i][k];
        }

        // Now b[k] is overwritten
        b[k] = (b[k] - sum) / (alpha + R[k][k]);
    }

    /* The substitution is now complete, and we return 0 to finish */
    return 0;
}




