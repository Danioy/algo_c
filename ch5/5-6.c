/**
 *  divide-n-conquer
 */

#include <stdio.h>

typedef long item_t;

item_t
max( item_t *a, size_t l, size_t r)
{
    printf("max(%ld, %ld)\n", l, r);
    item_t u, v; size_t m = (l + r)/2;
    if ( l == r) return a[l];
    u = max(a, l, m);
    v = max(a, m+1, r);
    if ( u > v ) return u;
    else return v;
}

int main( void )
{
    item_t a[10] = {6, 24, 32, 42, 7, 0, 11, 13, 9, 99};

    item_t v = max(a, 0, 9);

    printf("%ld\n", v);
}
