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

size_t
partition(item_t *a, size_t l, size_t r)
{
    size_t i = l, j = r; item_t v = a[r];
    for (;;)
      {
        while (less(&a[i], &v)) { i++; }
        while (less(&v, &a[--j])) if (j == l) break;
        if (i >= j) break;
        exch(&a[i], &a[j]);
      }
    exch(&a[i], &a[r]);
    return i;
}

void quicksort(item_t *a, size_t l, size_t r)
{
    size_t i;
    if ( r <= l) return;
    i = partition(a, l, r);
    if ( i == 0) return;
    quicksort(a, l, i-1);
    quicksort(a, i+1, r);
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

    quicksort(data, 0, N-1);
    for ( size_t i = 0; i < N; i++) {
        printf("%12d ", data[i].data);
        if( i%5 == 4) printf("\n");
    }
    printf("\n");


    /* checking whether stable */
    for ( size_t i = 0; i < N-1; i++) {
        if (data[i].data == data[i+1].data) {
            if(data[i].id > data[i+1].id)
                printf("Error {%d:%d} {%d:%d}\n",
                        data[i].id, data[i].data,
                        data[i+1].id, data[i+1].data);
        }
    }
}
