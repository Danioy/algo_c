/**
 *
 */

#ifndef TIGER_LIST_H
#define TIGER_LIST_H

#include <stdbool.h>

typedef int item_t;
typedef struct node link_t;

struct node {
   item_t item;
   struct node *next;
};

link_t *
link_init();

link_t *
node_new( item_t *);

void
node_free( link_t *);

link_t *
link_find( link_t *h, item_t *t);

void
link_insert_after( link_t *, link_t *);

void
link_del_next( link_t *h);

link_t *
link_next( link_t *);

item_t
link_get_item(link_t *);

bool
is_empty(link_t *);

#endif   /* TIGER_LIST_H */
