#include "tree.h"
#include "stack.h"
#include "stdlib.h"


struct node_s {
    item_t item;
    struct node_s *l;
    struct node_s *r;
};

tree_t *
tree_new( item_t item, tree_t *l, tree_t *r)
{
    tree_t *t = malloc(sizeof *t);
    x->item = item;
    x->l = l;
    x->r = r;
    return x;
}

void
preorder_travl( tree_t *h, void (*visit)( link ))
{
    if (h == NULL ) return;
    (*visit)(h);
    preorder_travl(h->l, visit);
    preorder_travl(h->r, visit);
}

void
print_node( tree_t *h)
{
    printf("%c \n", h->item);
}
