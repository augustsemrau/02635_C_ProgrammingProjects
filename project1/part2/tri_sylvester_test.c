/* Include header file */
#include "matrix.h"

/* Include prototypes */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Main function for testing forward substitution  as written in fwdsub.c */
int main(int argc, char const *argv[]){

    // Define function inputs which is two structures matrices R and C
    struct matrix R;
    struct matrix C;

    // Define R dimensions
    R.m = 4;  // Rows
    R.n = 4;  // Collumns

    // Define C dimensions
    C.m = 4;
    C.n = 4;

    /* Dynamically allocated size R.m x R.n array of double pointers for R */
    // First we allocate a vector equal to number of rows m
    R.A = (double **) malloc(R.m * sizeof(double *));
    // Check for succesful intitial allocation
    if (R.A == NULL) return -3;
    // Second we allocate every collumn equal to number of collumns n
    for (int i = 0; i < R.m; i++){
        R.A[i] = (double *) malloc(R.n * sizeof(double));
        // Again check for succesful allocation
        if (R.A[i] == NULL) return -3;
    }


    /* Dynamically allocated size C.m x C.n array of double pointers for C */
    // First we allocate a vector 
    C.A = (double **) malloc(C.m * sizeof(double *));
    // Check for succesful intitial allocation
    if (C.A == NULL) return -3;
    // Second we allocate every collumn
    for (int i = 0; i < C.m; i++){
        C.A[i] = (double *) malloc(C.n * sizeof(double));
        // Again check for succesful allocation
        if (C.A[i] == NULL) return -3;
    }



    /* I choose values for these tests that I have crosschecked with maple */

    // First for R
    R.A[0][0] = 1;
    R.A[0][1] = 2;
    R.A[0][2] = 3;
    R.A[0][3] = 4;

    R.A[1][0] = 0;
    R.A[1][1] = 5;
    R.A[1][2] = 6;
    R.A[1][3] = 7;

    R.A[2][0] = 0;
    R.A[2][1] = 0;
    R.A[2][2] = 8;
    R.A[2][3] = 9;

    R.A[3][0] = 0;
    R.A[3][1] = 0;
    R.A[3][2] = 0;
    R.A[3][3] = 10;


    // And for C
    C.A[0][0] = 1;
    C.A[0][1] = 2;
    C.A[0][2] = 3;
    C.A[0][3] = 4;

    C.A[1][0] = 5;
    C.A[1][1] = 6;
    C.A[1][2] = 7;
    C.A[1][3] = 8;

    C.A[2][0] = 9;
    C.A[2][1] = 10;
    C.A[2][2] = 11;
    C.A[2][3] = 12;

    C.A[3][0] = 12;
    C.A[3][1] = 14;
    C.A[3][2] = 15;
    C.A[3][3] = 16;
    
    
    //printf("R_t[%d][%d] = %lf\n", i, j, R_t[i][j]);


    // Print C before substitution
    printf("The matrix C before sylvester solve:\n");
    for (int i = 0; i < C.m; i++)
        for (int j = 0; j < C.n; j++)
            printf("C_t[%d][%d] = %lf\n", i, j, C.A[i][j]);



    /* TESTING STUFF
    for (int i = 0; i < C.m; i++)
        printf("%lf", C.A[0][i]);


    // First we dynamically allocate a vector
    double * c_k = (double *) malloc(C.n * sizeof(double));
    if (c_k == NULL) return -500;

    // We then append the k'th row of C to c_k
    for (int i = 0; i < C.n; i++){
        c_k[i] = C.A[0][i];
    }

    for (int i = 0; i < C.m; i++)
        printf("%lf", c_k[i]);

    */

    
    // Call tri_sylvester_solve function
    tri_sylvester_solve(&R, &C);

    // Print C after sylvester solve
    printf("The matrix C after sylvester solve:\n");
    for (int i = 0; i < C.m; i++)
        for (int j = 0; j < C.n; j++)
            printf("C_t[%d][%d] = %lf\n", i, j, C.A[i][j]);
    

    return 0;
}



