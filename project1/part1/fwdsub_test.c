/* Include header file */
#include "fwdsub.h"

/* Include prototypes */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Main function for testing forward substitution  as written in fwdsub.c */
int main(int argc, char const *argv[]){

    // Define function inputs
    unsigned long n = 4;
    double alpha = 2;


    /* Dynamically allocated size n x n two-dimensional array of double pointers, R */
    
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


    /* Dynamically allocate length n one-dimensional vector of double pointers, b */
    double * b = (double *) malloc(n * sizeof(double));
    if (b == NULL) return -2;

    /* I choose values for these tests that I have crosschecked with maple */

    // First for R
    
    R[0][0] = 1;
    R[0][1] = 2;
    R[0][2] = 3;
    R[0][3] = 4;

    R[1][0] = 0;
    R[1][1] = 5;
    R[1][2] = 6;
    R[1][3] = 7;

    R[2][0] = 0;
    R[2][1] = 0;
    R[2][2] = 8;
    R[2][3] = 9;

    R[3][0] = 0;
    R[3][1] = 0;
    R[3][2] = 0;
    R[3][3] = 10;

    // And for b
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;
    b[3] = 4;
    //printf("R_t[%d][%d] = %lf\n", i, j, R_t[i][j]);


    // Print b before substitution
    printf("The vector b before forward substitution:\n");
    for (int ind = 0; ind < n; ind++)
        printf("%lf\n", b[ind]);

    /* Call fwdsub function */
    fwdsub(n, alpha, R, b);

    // Print b after substitution
    printf("\nThe vector b after forward substitution:\n");
    for (int ind = 0; ind < n; ind++)
        printf("%lf\n", b[ind]);


    return 0;
}


