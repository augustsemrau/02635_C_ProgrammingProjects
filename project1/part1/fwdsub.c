#include <stdlib.h>
#include <math.h>

int fwdsub(
unsigned long n, 
double alpha, 
double ** R, /* two-dimensional array, row-major */
double * b /* one-dimensional array */
){

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