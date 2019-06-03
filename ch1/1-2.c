#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>

#define N 10
int id[N];

int find( int node ) {
    /* In a tree, only the root = id[root]. so we use the empty
     * loop to find the root */
    for( int i = node; i != id[node]; i = id[node]);
    return i;
}

void union_s( int node1, int node2 ) {
    int i = find(node1);
    int j = find(node2);
    if (i == j) return;
    id[i] = j;
}



int main( void )
{
    char *buf[1024];
    size_t len = 1024;

    int p, q, t, v, id[N];
    for (size_t i = 0; i < N; i++) id[i] = i;

    while (getline(buf, &len, stdin) > 1 ) {
        sscanf(*buf, "%d %d", &p, &q);

        union_s(p, q);

        for ( size_t i = 0; i < N; i++ )
            printf("%d ", id[i]);
        printf("\n");
    }
}
