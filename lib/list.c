/**
 *
 */

#include <stdlib.h>
#include <string.h>
#include "list.h"


link_t *
link_init() {
    link_t *h;
    h = (link_t *)malloc(sizeof *h);
    h->next = NULL;

    return h;
}

link_t *
node_new( item_t *v) {
    link_t *t;
    t = (link_t *)malloc(sizeof *t);
    t->item = *v;

    return t;
}

link_t *
link_find( link_t *h, item_t *t ) {
    link_t *tmp;
    for ( tmp = h->next; tmp->next != NULL; tmp = tmp->next) {
        if ( tmp->item == *t) return tmp;
    }
    return NULL;
}

void
link_insert_after( link_t *first, link_t *second) {
    second->next = first->next;
    first->next = second;
}

void
link_del_next( link_t *first) {
    link_t *tmp = first->next;
    first->next = first->next->next;
    free(tmp);
}

item_t
link_get_item(link_t *des) { return des->item; }

bool
is_empty(link_t *head) {
    return head->next == NULL || head->next == head;
}

/**
 * larger_2_tail  exercise 3-24
 * to move the largest item on the linked list to the tail.
 * 1) we first need to find max node's parent, max node and tail node;
 * 2) disjoin max node from it's parent and append to tail;
 * 3) make sure the link is not broken.
 * we use 4 temporary variables but we do the job in single scan.
 * That is: t = O(N).
 *
 * @param [in] head: ptr to the head of the linked list.
 */
void
larger_2_tail(link_t *head)
{
    /* temp variables to store the largest node's parent and tail node */
    link_t *max_p, *max, *tail; item_t max_i = head->next->item;
    for (tail = head->next; tail->next != NULL; tail = tail->next) {
        if( tail->next->item > max_i) {
            max_i = tail->next->item;
            max_p = tail;
        }
    }
    max = max_p->next; max_p->next = max->next;
    tail->next = max; max->next = NULL;
}
