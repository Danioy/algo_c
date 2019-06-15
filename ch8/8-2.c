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

/**
 * mergeab2c to merge two ordered arraies (a with N items and
 * c with M items in this case) into one ordered array c, which
 * suppose should be N + M in length.
 * @param c ptr to destination array;
 * @param a ptr to array a;
 * @param N length of array a;
 * @param b ptr to array b;
 * @param M length of array b.
 */
void mergeab2c(item_t *c, item_t *a, size_t N,
        item_t *b, size_t M)
{
    for( size_t i=0, j=0, k=0; k < N+M; k++)
    {
        if (i == N) {c[k] = b[j++]; continue;}
        if (j == M) {c[k] = a[i++]; continue;}
        c[k] = (less(a[i], b[j]) ? a[i++] : b[j++]);
    }
}

void mergeb2a(item_t *a, item_t *b, size_t l, size_t r)
{
    size_t m = (r + l) / 2;
    if ( r - l <= G ) {insertion(a, l, r); return;}
    mergeb2a(b, a, l, m);
    mergeb2a(b, a, m+1, r);
    mergeab2c(a+l, b+l, m-l+1, b+m+1, r-m);
}

void merge(item_t a[], size_t l, size_t r)
{
    item_t aux[BUF_SIZE];
    for( size_t i=l; i <= r; i++) aux[i] = a[i];
    mergeb2a(a, aux, l, r);
}

int main( void )
{
    item_t data[BUF_SIZE];
    size_t N = 0;

    FILE* fp = fopen("data", "r");
    while (N < BUF_SIZE && (fscanf(fp, "%d", &data[N]) == 1)) N++;
    fclose(fp);

    merge(data, 0, N-1);
    for ( size_t i = 0; i < N; i++) {
        printf("%12d ", data[i]);
        if( i%5 == 4) printf("\n");
    }
    printf("\n");
}
