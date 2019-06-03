#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>

#define N 10000
int id[N];

void union_s(int node1, int node2) {
    int t = id[node1], v;

    if ( id[node1] != id[node2]) {
        v = id[node2];
        for (size_t i = 0; i < N; i++)
            if( id[i] == v ) id[i] = t;
    }
}

int find(int node) {
    return id[node];
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
            if (id[i] == t) printf("%ld - ", i);
        printf("\n");
    }
}
