/**
 *
 */

#ifndef TIGER_QUEUE_H
#define TIGER_QUEUE_H
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"

typedef struct q_node link_t;
struct q_node {
   Item item;
   link_t *next;
};

static link_t *head, *tail;

link_t *
link_new( item_t item, link_t *next) {
   link_t *x = malloc(sizeof *x);
   x->item = item; x->next = next;
   return x;
}

inline void
fifoq_init() { head = NULL;}

inline bool
fifoq_empty() { return head == NULL; }

void
fifoq_put( item_t item) {
   if (head == NULL) {
      head = (tail = link_new(item, head)); return;
   }
   tail->next = link_new(item, tail->next);
   tail = tail->next;
}

item_t
fifoq_get() {
   item_t item = head->item;
   link_t *t = head->next;
   free(head); head = t;
   return item;
}



#endif
