#include <stdlib.h>
#include <stdio.h>
#include "poly.h"

struct poly { int N; int *a;};

poly_t *
poly_term( int coeff, int exp)
{
    int i; poly_t *t = malloc(sizeof *t);
    t->N = exp+1; t->a[exp] = coeff;
    for ( i = 0; i < exp; i++) t->a[i] = 0;
    return t;
}

poly_t *
poly_add( poly_t *p, poly_t *q )
{
    int i; poly_t *t = malloc(sizeof *t);
    if( p->N < q->N ) { t = p; p = q; q = t; }
    for( i = 0; i < q->N; i++) t->a[i] = p->a[i] + q->a[i];
    return t;
}

poly_t *
poly_mult( poly_t *p, poly_t *q )
{
    int i, j;
    poly_t *t = poly_term(0, (p->N-1)+(q->N-1));
    for ( i = 0; i < p->N; i++)
        for ( j = 0; j < q-> N; j++)
            t->a[i+j] += p->a[i] * q->a[j];
    return t;
}

double
poly_eval( poly_t *p, double x)
{
    int i; double t = 0.0;
    for ( i = p->N -1; i >= 0; i--)
        t = t*x + p->a[i];
    return t;
}

void
poly_show( poly_t *p)
{
    int i;
    for (i = 0; i < p->N; i++) printf(" %dx^%d +", p->a[i], i);
}
