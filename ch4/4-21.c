/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

int main( int argc, char *argv[])
{
    int N = atoi(argv[1]); double p = atof(argv[2]);
    poly_t *t, *x; int i;
    printf("Binomial coefficients\n");
    t = poly_add( poly_term( 1, 1), poly_term( 1, 0));
    for ( i = 0, x = t; i < N; i++)
    {
        x = poly_mult(t, x);
        poly_show(x);
    }
    printf("%f\n", poly_eval(x, p));
}
