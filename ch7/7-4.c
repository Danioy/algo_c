/**
 *  comb insertion sort and quick sort together
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// typedef struct item_  item_t;
typedef int item_t;
// struct item_ {
//     int id;
//     int data;
// };

#define BUF_SIZE 8192
#define M 10
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

long
partition(item_t a[], long l, long r)
{
    long i = l-1, j = r; item_t v = a[r];
    for(;;)
    {
        while (less(a[++i], v));
        while (less(v, a[--j])) if (j == l) break;
        if (i >= j) break;
        exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}

void quicksort(item_t a[], long l, long r)
{
    long i;
    if ( r - l <= M) return;
    exch(a[(l+r)/2], a[r-1]);
    cmpexch(a[l], a[r-1]);
    cmpexch(a[l], a[r]);
    cmpexch(a[r-1], a[r]);
    i = partition(a, l, r);
    quicksort(a, l, i-1);
    quicksort(a, i+1, r);
}

void sort(item_t *a, long l, long r)
{
    quicksort(a, l, r);
    insertion(a, l, r);
}

int main( void )
{
    item_t data[BUF_SIZE];
    size_t N = 0;

    FILE* fp = fopen("data", "r");
    while (N < BUF_SIZE && (fscanf(fp, "%d", &data[N]) == 1)) N++;
    fclose(fp);

    sort(data, 0, N-1);
    for ( size_t i = 0; i < N; i++) {
        printf("%12d ", data[i]);
        if( i%5 == 4) printf("\n");
    }
    printf("\n");
}
