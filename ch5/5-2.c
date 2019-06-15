#include <stdio.h>

long puzzle( long N, size_t *count )
{
    (*count)++;
    if ( N == 1 ) return 1;
    if ( N % 2 == 0 ) return puzzle(N/2, count);
    else return puzzle( 3*N + 1, count);
}

int main( void )
{
    size_t count, max = 0, max_i=0;
    for(size_t i = 1; i < 1000000 ; i++)
    {
        count = 0;
        if (puzzle(i, &count) > 0) {
            if (count > max) {max = count; max_i = i;}
        };
    }
    printf("%ld: %ld\n", max_i, max);
}
