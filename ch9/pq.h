/**
 *
 *
 */

#ifndef TIGER_PQ_H
#define TIGER_PQ_H

#include <stdbool.h>

typedef char item_t;

void pq_init( size_t );
bool pq_empty();
void pq_insert( item_t );
item_t pq_popmax();

#endif
