/**
 *
 */

#ifndef TIGER_POLY_H
#define TIGER_POLY_H

typedef struct poly poly_t;
void     poly_show( poly_t *);
poly_t  *poly_term( int, int);
poly_t  *poly_add( poly_t *, poly_t *);
poly_t  *poly_mult( poly_t *, poly_t *);
double    poly_eval( poly_t *, double );

#endif
