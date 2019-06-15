#include <stdio.h>


/**
 * N is the index of disk to move;
 * d represents the direction:
 *  if the three tags position as a trangle, then:
 *  1) + means move the indexed disk count-clockwise;
 *  2) - means move the indexed disk clockwise.
 */
void hanoi( int N, int d)
{
    if ( N == 0 ) return;
    hanoi(N-1, -d);
    shift(N, d);
    hanoi(N-1, -d);
}
