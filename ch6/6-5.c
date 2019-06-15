#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct item_  item_t;
struct item_ {
    int id;
    int data;
};

#define BUF_SIZE 1024

int
cmp_item( item_t *a, item_t *b)
{
    if (a->data == b->data) return 0;
    if (a->data >  b->data) return 1;
    return -1;
}

int key( item_t *a) { return a->data; }
int id( item_t *a ) { return a->id;   }
bool less(item_t *a, item_t *b) { return cmp_item(a,b) == -1;}
void exch(item_t *a, item_t *b) {
    item_t t = *a;
    *a = *b;
    *b = t;
}
void cmpexch( item_t *a, item_t *b) {
    if (less(b, a)) exch(a, b);
}

/* liner sorting, O(N*N) */
void sort( item_t *a, size_t l, size_t r)
{
    size_t i, j;
    for ( i = l + 1; i <= r; i++)
        for ( j = i; j > l; j--)
            cmpexch(&a[j-1], &a[j]);
}

void selection( item_t *a, size_t l, size_t r)
{
    size_t i, j, min;
    for ( i = l; i < r; i++) {
        min = i;
        for ( j = i+1; j <=r; j++)
            if( less( &a[j], &a[min])) min = j;
        exch( &a[i], &a[min]);
    }
}

void insertion( item_t *a, size_t l, size_t r)
{
    size_t i;
    for ( i = r; i> l; i--) cmpexch(&a[i-1], &a[i]);
    for (i = l+2; i<=r; i++) {
        int j = i; item_t v = a[i];
        while ( less( &v, &a[j-1]))
        { a[j] = a[j-1]; j--; }
        a[j] = v;
    }
}

void bubble( item_t *a, size_t l, size_t r)
{
    size_t i,j;
    for ( i = l; i < r; i++)
        for ( j = r; j > i; j--)
            cmpexch(&a[j-1], &a[j]);
}

void shellsort( item_t *a, size_t l, size_t r)
{
    size_t i, j, h;
    for ( h = l; h <= (r-l)/9; h = 3*h + 1);
    for (; h > 0; h /= 3)
        for ( i = l + h; i <= r; i++) {
            size_t j = i; item_t v = a[i];
            while ( j >= l + h && less(&v, &a[j-h]))
            {a[j] = a[j-h]; j-=h;}
            a[j] = v;
        }
}

int main( void )
{
    item_t data[BUF_SIZE];
    size_t N = 0;

    FILE* fp = fopen("data", "r");
    while (N < BUF_SIZE && (fscanf(fp, "%d", &(data[N].data)) == 1))
    {data[N].id = N; N++;}
    fclose(fp);
    data[N++].data = data[0].data;
    data[N-1].id = N-1;

    shellsort(data, 0, N-1);
    for ( size_t i = 0; i < N; i++) {
        printf("%12d ", data[i].data);
        if( i%5 == 4) printf("\n");
    }
    printf("\n");


    /* checking whether stable */
    for ( size_t i = 0; i < N-1; i++) {
        if (data[i].data == data[i+1].data) {
            if(data[i].id > data[i+1].id)
                printf("Error {%d:%d} {%d:%d}",
                        data[i].id, data[i].data,
                        data[i+1].id, data[i+1].data);
        }
    }
}
