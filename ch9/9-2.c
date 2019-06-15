/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char item_t;

#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { item_t t = (A); (A) = (B); (B) = t; }
#define cmpexch(A, B) if (less(B, A)) exch(A, B)

static item_t *pq;
static size_t cnt;

static void
fixup( item_t a[], size_t k)
{
    while ( k >= 1 && less(a[k/2], a[k])) {
        exch(a[k], a[k/2]); k = k/2;
    }
}

static void
fixdown(item_t a[], size_t k, size_t N)
{
    size_t j;
    while ( 2*k <= N) {
        j = 2*k;
        if (j < N && less(a[j], a[j+1])) j++;
        if ( !less( a[k], a[j])) break;
        exch( a[k], a[j]); k=j;
    }
}

void pq_init(size_t max_buf)
{ pq = malloc(max_buf * sizeof( item_t )); cnt = 0;}

bool pq_empty() {return cnt == 0;}

void pq_insert( item_t v) { pq[cnt++] = v; fixup(pq, cnt-1);}

item_t pq_popmax()
{
    exch(pq[0], pq[cnt-1]);
    fixdown(pq, 0, cnt-2);
    return pq[--cnt];
}

int main( void )
{
    char *p = "PRIO*R**I*T*Y***QUE***U*E";
    pq_init(100);
    char ch, cch;
    while ((sscanf(p, "%c", &ch)) == 1) {
        switch(ch) {
        case '*': cch = pq_popmax(); printf("%c\n", cch); break;
        default: pq_insert(ch);
        }
        p++;
    }

    printf("%s\n", pq);

    free(pq);

}
