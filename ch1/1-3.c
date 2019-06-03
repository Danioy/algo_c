/**
 * Weighted quick union.
 *
 */

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>

#define N 10000
int id[N];
int sz[N];

int find(int node) {
    int i;
    for (i = node; i != id[i]; i++);
    return i;
}

void union_s( int node1, int node2 ) {
    int i = find(node1);
    int j = find(node2);
    if (i == j) return;
    if ( sz[i] < sz[j] ) {
        id[i] = j; sz[j] += sz[i];
    } else {
        id[j] = i; sz[i] += sz[j];
    }
}

int main( void )
{
    char *buf[1024];
    size_t len = 1024;

    int p, q;
    for (size_t i = 0; i < N; i++) { id[i] = i; sz[i] = 1; }

    while (getline(buf, &len, stdin) > 1 ) {
        sscanf(*buf, "%d %d", &p, &q);

        union_s(p, q);

        for ( size_t i = 0; i < 10; i++ )
            printf("%d ", id[i]);
        printf("\n");
    }
}
