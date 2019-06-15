/**
 * basic of mergesort
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define G 10

typedef int item_t;

#define BUF_SIZE 8192
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { item_t t = (A); (A) = (B); (B) = t; }
#define cmpexch(A, B) if (less(B, A)) exch(A, B)
#define min(a, b) ({            \
    __typeof__ (a) _a = (a);    \
    __typeof__ (b) _b = (b);    \
    _a < _b ? _a : _b;          \
})

void insertion( item_t *a, size_t l, size_t r)
{
    size_t i;
    for ( i = r; i> l; i--) cmpexch(a[i-1], a[i]);
    for (i = l+2; i<=r; i++) {
        int j = i; item_t v = a[i];
        while ( less( v, a[j-1]))
        { a[j] = a[j-1]; j--; }
        a[j] = v;
    }
}

void merge(item_t a[], size_t l, size_t m, size_t r)
{
    item_t aux[BUF_SIZE];
    size_t i, j, k;
    for ( i = m+1; i> l; i--) aux[i-1] = a[i-1];
    for ( j = m; j < r; j++) aux[r+m-j] = a[j+1];
    for ( k = l; k <= r; k++)
        if(less(aux[j], aux[i]))
            a[k] = aux[j--];
        else a[k] = aux[i++];
}

void mergesort(item_t a[], size_t l, size_t r)
{
    for ( size_t m = 1; m <= r-l; m = m + m)
        for ( size_t i = l; i <= r-m; i += m + m)
            merge(a, i, i+m-1, min(i+m+m-1, r));
}

int main( void )
{
    item_t data[BUF_SIZE];
    size_t N = 0;

    FILE* fp = fopen("data", "r");
    while (N < BUF_SIZE && (fscanf(fp, "%d", &data[N]) == 1)) N++;
    fclose(fp);

    mergesort(data, 0, N-1);
    for ( size_t i = 0; i < N; i++) {
        printf("%12d ", data[i]);
        if( i%5 == 4) printf("\n");
    }
    printf("\n");
}
