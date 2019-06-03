#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tree_entry tree_t;

struct tree_entry {
    char ch;
    struct tree_entry *l, *r;
};

/**
 * A very simple stack implement, without any protection.
 * @method:
 *  bool stack_empty(); return true if stack is empty;
 *  void stackinit();   refresh the stack, however, we not really clean
 *                      the data had been stored in the stack buffer;
 *  tree_t *pop();      return the last tree node  pushed in the stack;
 *  void push(tree_t *) push a ptr to a tree node into stack;
 *
 */
static tree_t *stack[1024];
size_t sp;

/**
 * A dummy tree node to fill into ptrs of terminal nodes.
 * it works as a sign for the end of a branch.
 */
tree_t *z;

bool stack_empty() {
    return sp == 0;
}

void stackinit() { sp = 0; }

tree_t *pop() { return stack[--sp]; }

void push( tree_t *v) { stack[sp++] = v; }


/**
 * visit(): a helper function to define what you can do when you reach
 * one tree node. It could be any action you want to process the node
 * data. Here we only print out the ch inside the node.
 *
 */
void visit( tree_t *t) {
    printf("%c ->", t->ch);
}

void inorder_traverse() {
    tree_t *t, *r;
    r = pop();
    push(r);
    t = pop();
    while ( !stack_empty() ) {
        if (t->l != z) { push(t->l); t = t->l;}
        else { visit(t); t = pop();}
        visit(t);
        if (t->r != z) { push( t->r ); t = t->r;}
        else { visit(t); t = pop();}
    }
    printf("\n");
    push(r);
}

void preorder_traverse() {
    /*
     * there was only root node in stack when travel began.
     * we use variable *root to remember root and push it back
     * when the traversing done.
     */
    tree_t *t, *root;
    root = pop();
    push(root);
    while ( !stack_empty() ) {
        t = pop(); visit(t);
        if (t->l != z) push( t-> l);
        if (t->r != z) push( t->r );
    }
    printf("\n");
    push(root);
}

int main( void )
{
    tree_t *x;
    char c;
    z = (tree_t *)malloc(sizeof *z);
    z->ch = -1; z->l = z; z->r = z;

    for ( stackinit(); scanf("%1s", &c) != EOF;) {
        x = (tree_t *)malloc(sizeof *x);
        x->ch = c; x->l = z; x->r = z;
        if ( c == '+' || c == '*' ) {
            x->r = pop(); x->l = pop();
        }
        push(x);
    }

    preorder_traverse();

    inorder_traverse();

    printf("\n");

    exit(0);

}
