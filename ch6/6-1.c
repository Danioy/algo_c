#include <stdio.h>
#include <stdlib.h>

typedef int item_t;
#define BUF_SIZE 1024


#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { item_t t = (A); (A) = (B); (B) = t; }
#define cmpexch(A, B) if (less(B, A)) exch(A, B)

void sort( item_t *a, size_t l, size_t r)
{
    size_t i, j;
    for ( i = l + 1; i <= r; i++)
        for ( j = i; j > l; j--)
            cmpexch(a[j-1], a[j]);
}

int main( void )
{
    int data[BUF_SIZE];
    size_t N = 0;

    FILE* fp = fopen("data", "r");
    while (N < BUF_SIZE && fscanf(fp, "%d", &data[N]) == 1) N++;
    fclose(fp);

    sort(data, 0, N-1);
    for ( size_t i = 0; i < N; i++) {
        printf("%12d ", data[i]);
        if( i%5 == 4) printf("\n");
    }
    printf("\n");
}
