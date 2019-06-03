#include <stdlib.h>
#include <stdio.h>

typedef struct node link_t;

struct node { int item; link_t *next; };

link_t *
find( link_t *h, int item ) {
    link_t *p;
    for(p = h; p->item == item; p = p->next);
    return p;
}

/* exercise 3.24 */
int count(link_t *l) {
    int cnt = 0;

    for (link_t *p= l; p->next != l; p = p->next) cnt++;

    return cnt;
}

/* exercise 3.25 */
int distance( link_t *x, link_t *t ) {
    int cnt = 0;
    for (link_t *p = x; p->next != t; p = p->next) cnt++;

    return cnt;
}

/* exercise 3.26 */
void conjoin( link_t *x, link_t *t) {
    link_t *i;

    i = t->next; t->next = x->next;
    x->next = i;
}

/* exercise 3.27 */
void move( link_t *src, link_t *des) {
    link_t *tmp;
    tmp = src->next; src->next = tmp->next;
    tmp->next = des->next; des->next = tmp;
}



int main( int argc, char *argv[])
{
    int i, N = atoi(argv[1]), M = atoi(argv[2]);

    link_t *t = malloc(sizeof *t), *x = t;
    t->item = 1; t->next = x;

    for ( i = 2; i < N; i++) {
        x = ( x->next = malloc(sizeof *x));
        x->item = i; x->next = t;
    }
    while ( x != x->next) {
        for (i = 1; i < M; i++) x = x->next;
        x->next = x->next->next;
        N--;
    }
    printf("%d\n", x->item);
}
