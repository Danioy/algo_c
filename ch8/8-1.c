/**
 * basic of mergesort
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int item_t;

#define BUF_SIZE 8192
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { item_t t = (A); (A) = (B); (B) = t; }
#define cmpexch(A, B) if (less(B, A)) exch(A, B)

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

item_t aux[BUF_SIZE];

void merge(item_t a[], size_t l, size_t m, size_t r)
{
    size_t i, j, k;
    for (i = m+1; i > l; i--) aux[i-1] = a[i-1];
    for (j = m; j < r; j++) aux[r+m-j] = a[j+1];
    for (k = l; k <=r; k++) {
        if( less(aux[j], aux[i])) {
            a[k] = aux[j--];
        } else {
            a[k] = aux[i++];
        }
    }
}

void mergesort( item_t a[], size_t l, size_t r)
{
    size_t m = (r + l)/2;
    if (r <= l) return;
    mergesort(a, l, m);
    mergesort(a, m+1, r);
    merge(a, l, m, r);
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
