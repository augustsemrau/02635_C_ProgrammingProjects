#include <stdlib.h>
#include <math.h>

int fwdsub(
unsigned long n, 
double alpha, 
double ** R, /* two-dimensional array, row-major */
double * b /* one-dimensional array */
){

    /* First we create a transposed R matrix which is lower triangular */
    // Step 1: ynamically allocate two-dimensional array using malloc
    double ** R_t = (double **) malloc(n * sizeof(double *));
    // Check for succesful intitial allocation
    if (R_t == NULL) return -2;
    
    // Step 2: Allocate all collumns filled with zero's using calloc
    for (int i = 0; i < n; i++){
        R_t[i] = (double *) calloc(n, sizeof(double));
        // Again check for succesful allocation
        if (R_t[i] == NULL) return -2;
    }

    // Copy transposed content from R to R_t (transposed)
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++)
            R_t[i][j] = R[j][i];   
        


    /* To perform forward substitution, we loop through k from 0 up to n-1 */
    for (int k = 0; k < n; k++){

        // Before any substitution, we check that the division will be legal
        if ((alpha + R_t[k][k]) == 0) return -1; 


        // For the first substitution, we use the simpler formula
        if (k == 0){
           b[k] = b[k] / (alpha + R_t[k][k]);
        } 


        // For the rest of the substitutions, we use the lower formula writte in the assignment
        else {

            // Calculate sum(x_i*R_ik)
            double sum = 0;
            for (int i = 0; i < k; i++){
                sum = sum + b[i] * R_t[k][i];
            }

            // Now b[k] is overwritten
            b[k] = (b[k] - sum) / (alpha + R_t[k][k]);


            // SLET EVT
            // We check for other numerical faliure outputs
            if (b[k] == INFINITY || b[k] == -INFINITY) return -1;
        }

    }

    return 0;
}