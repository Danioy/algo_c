/**
 * Exercise 4-10, 4-11, 4-12
 * notes: the basic idea the same as 4-5.c.
 * TO DO:
 * [] 1) how to distinct (-1) and (0 - 1);
 * [] 2) make program more readable and strong.
 */

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#define STACK_MAX 256
#define BUF_SIZE 1024

/* evaluation functions */
double eval_uminus(double a, double b) { return -a;                 }
double eval_abs(double a, double b) { return (a >= 0) ? a : -a;     }
double eval_exp(double a, double b) { return pow(a, b);             }
double eval_mul(double a, double b) { return a * b;                 }
double eval_div(double a, double b) {
    if ( b < 0.00000001 ) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }
    return a / b;
}
double eval_mod(double a, double b) {
    if ( b < 0.00000001 ) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }
    return (double)((long)a % (long)b);
}
double eval_add(double a, double b) { return a + b;                 }
double eval_sub(double a, double b) { return a - b;                 }

/* operators section */
bool is_num( char ch ) {
    if ( ch >= '0' && ch <= '9') return true;
    if ( ch == '.') return true;
    return false;
}
/* associative identifier */
enum as_w { AS_NONE = 0, AS_LEFT, AS_RIGHT};

struct op_s {
    char        op;         /* operator */
    int         prec;       /* precidence */
    enum as_w   asoc;       /* associative */
    bool        unary;      /* unary operator or not */
    double      (*eval) (double a1, double a2);  /* evaluation func */
} ops[] = {
    {'_', 10, AS_RIGHT, true,  eval_uminus  },
    {'$', 9,  AS_RIGHT, true,  eval_abs     },
    {'^', 9,  AS_LEFT,  false, eval_exp     },
    {'*', 8,  AS_LEFT,  false, eval_mul     },
    {'/', 8,  AS_LEFT,  false, eval_div     },
    {'%', 8,  AS_LEFT,  false, eval_mod     },
    {'+', 5,  AS_LEFT,  false, eval_add     },
    {'-', 5,  AS_LEFT,  false, eval_sub     },
    {'(', 0,  AS_NONE,  false, NULL         },
    {')', 0,  AS_NONE,  false, NULL         }
};

struct op_s *
getop( char ch ) {
    for (size_t i = 0; i < (sizeof ops / sizeof ops[0]); ++i) {
        if (ops[i].op == ch) return ops + i;
    }
    return NULL;
}

/* stack section */
/* we are maintaining two stacks here, one for operators, and one
 * for number. Each have 4 methods push(), pop(), empty(), top().
*/
static struct op_s *stack_op[ STACK_MAX ];
static size_t opp = 0;

void push_op( struct op_s *op) {
    if (opp > STACK_MAX -1) {
        fprintf(stderr, "Error: op stack overflow.\n");
        exit(EXIT_FAILURE);
    }
    stack_op[opp++] = op;
}

struct op_s *pop_op() {
    if (opp == 0) {
        fprintf(stderr, "Error: poping empty op stack.\n");
        exit( EXIT_FAILURE );
    }
    return stack_op[--opp];
}

struct op_s *top_op() {
    if (opp == 0) return NULL;
    return stack_op[ opp-1 ];
}

bool empty_op() {
    return opp == 0;
}

static double stack_num[STACK_MAX];
static size_t dp;

void push_num( double v) {
    if (dp > STACK_MAX -1) {
        fprintf(stderr, "Error: op stack overflow.\n");
        exit(EXIT_FAILURE);
    }
    stack_num[dp++] = v;
}

double pop_num() {
    if (dp == 0) {
        fprintf(stderr, "Error: poping empty op stack.\n");
        exit( EXIT_FAILURE );
    }
    return stack_num[--dp];
}

double top_num() {
    if (dp == 0) return -1.0;
    return stack_num[ dp-1 ];
}

bool empty_num() {
    return dp == 0;
}


void
eval_op( struct op_s *op) {

    struct op_s *pop;
    double n1, n2;

    if (op->op == '(' ) { push_op( op ); return; }
    if (op->op == ')' ) {
        while ( !empty_op() && top_op()->op != '(' ) {
            pop = pop_op();
            n1 = pop_num();
            if (pop->unary) push_num(pop->eval(n1, 0));
            else {
                n2 = pop_num();
                push_num(pop->eval(n1, n2));
            }
        }
        if (!(pop = pop_op()) || pop->op != '(') {
            fprintf(stderr, "Error: No matching \'(\'\n");
            exit(EXIT_FAILURE);
        }
        return;
    }
    if (op->asoc == AS_RIGHT) {
        while ( !empty_op() && op->prec < top_op()->prec ) {
            pop = pop_op();
            n1 = pop_num();
            if (pop->unary) push_num( pop->eval(n1, 0));
            else {
                n2 = pop_num();
                push_num( pop->eval(n1, n2));
            }
        }
    }
    push_op(op);
}

void
infix_postify( struct op_s *op ) {}

int
main( void )
{
    char expr[ BUF_SIZE ];
    char post[ BUF_SIZE ];
    size_t = expr_len;

    if ( (getline( &expr, &expr_len, stdin ) < 0) ||
         (len && expr[0] = '\n') ) {
        free( expr );
        clearerr( stdin );
        exit(0);
    }

    expr[expr_len++] = ')';
    expr[expr_len] = '\0';
    struct op_s *op = NULL;
    struct op_s start = {'(', 0, AS_NONE, false, NULL};
    push_op(&start);
    char *p;
    char *num_end; /* tmp variable to ptr the end of double num.*/
    double n1, n2;
    char *j = expr; /* index of non-space char */
    size_t q = 0;
    struct op_s *tmp;


    for (p = expr ; *p ; p++) {
        /* try to identify unary -. if a '-' is:
            1) at first position; or
            2) tightly follow an operator except ')',
           we treate it a '_' op.
        */
        if ( isspace(*p) ) continue;

        if ( *p == '-') {
            if ( j == expr ) op = getop('_');
            else if ( *j != ')' || !is_num(*j) )
                op = getop('_');
            else op = getop('-');
            push_op(op);
            j = p;
        }

        if ( is_num( *p )) {
            n1 = strtod(p, &end);
            j = p;
            p = end;
            memcpy(&post[q], j, p-j);
            q += p-j;
        }

        if ( *p = ')') {
            while ( top_op() != '(') post[q++] = pop();
            j = p;
        }

        if (op = getop( *p )) {
            if (op->prec < top_op->prec) {
                tmp = pop_op();
                push_op(op);
                op = tmp;
            }
            post[q++] = op->op;
            j = p;
        }


    while (!empty_op()) {
        op = pop_op();
        n1 = pop_num();
        if ( op->unary ) push_num( op->eval(n1, 0));
        else {
            n2 = pop_num();
            push_num( op->eval(n2, n1));
        }
    }
    if (dp != 1) {
        fprintf(stderr, "Error, Number stack have more than proper %ld number left.\n", dp-1);
        exit(EXIT_FAILURE);
    }
    printf("%f \n", stack_num[0]);

    return 0;
}
