/**
 *
 */

#ifndef TIGER_STACK_H
#define TIGER_STACK_H

#include <stdbool.h>
#include "item.h"

#define MAX_BUF 4096

void
stack_init( size_t );

item_t
pop();

bool
empty();

void
push( item_t );

item_t
top();

void
free();

#endif
