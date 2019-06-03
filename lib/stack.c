
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"

static struct stack_conf {
    item_t *buff;
    size_t size;
    size_t capacity;
} *stack;

void
stack_init( size_t bufsize )
{
    stack = (struct stack_conf *)malloc(sizeof *stack);
    if (stack == NULL) {
        fprintf(stderr, "Error malloc\n");
        exit(-1);
    }

    stack->buff = (item_t *)malloc(bufsize * sizeof( item_t));
    if (stack->buff == NULL) {
        fprintf(stderr, "Error malloc\n");
        exit(-1);
    }

    stack->capacity = bufsize;
    stack->size = 0;
}

bool
is_empty()
{
    return stack->size == 0;
}

void
push( item_t v)
{
    if (stack->size > stack->capacity -1) {
        fprintf(stderr, "Error Buffer Overflow\n");
        exit(-1);
    }

    stack->buff[stack->size++] = v;
}

item_t
pop()
{
    return stack->buff[--stack->size];
}
