/**
 * Exercise 4-10, 4-11, 4-12
 * notes: details see "Infix to postfix conversion algorithm.md"
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "item.h"
#include "stack.h"



bool is_op( char ch) {
    switch ( ch ) {
    case '+':  case '-': case '*': case '/': case '$':
    return true;
    }
    return false;
}

bool is_di_do( char ch) {
    if ((ch == '.') || ((ch >='0') && (ch <= '9'))) return true;
    return false;
}

int prece(char ch) {
    switch (ch) {
    case '+': case '-':
        return 2;
    case '*': case '/':
        return 4;
    case '$': case '^': case '_':
        return 6;
    case '(': return 0;
    }
    return 0;
}

void
infix_postfix( char *in, size_t len, char **out) {
    char *post = malloc(100 * sizeof(char));
    memset(post, 0x00, 100 * sizeof(char));

    size_t i, j;

    stack_init(len);

    for ( i = 0, j = 0; i < len; i++)
    {
        if ( in[i] == '(') push(in[i]);
        if (is_op(in[i])) {
            while (prece(top()) >= prece(in[i]))
            post[j++] = pop();
            push(in[i]);
        }
        if (is_di_do(in[i])) {
            while (is_di_do(in[i])){
                post[j++] = in[i];
                i++;
            }
            post[j++] = ' ';
        }
        if (in[i] == ')') {
            while (top() != '(') {
                post[j++] = pop();
            }
            pop();
        }

    }
    while (!is_empty()) post[j++] = pop();

    *out = post;
}


double
eval_prefix( char *in, size_t len ) {
    double pile[100];
    char *p, *end; size_t dp=0;
    double tmp;

    for ( p = in; *p != '\0'; p++)
    {
        if (( *p >= '0') && (*p <= '9')) {
            pile[dp++] = strtod(p, &end);
            p = end;
        }
        if ( *p == '+' ) {
            tmp = pile[--dp];
            tmp += pile[--dp];
            pile[dp++] = tmp;
        }
        if ( *p == '*' ) {
            tmp = pile[--dp];
            tmp *= pile[--dp];
            pile[dp++] = tmp;
        }
        if ( *p == '/' ) {
            tmp = pile[--dp];
            tmp /= pile[--dp];
            pile[dp++] = tmp;
        }
        if ( *p == '$' ) {
            tmp = pile[--dp];
            pile[dp++] = (tmp > 0) ? tmp : -tmp;
        }

        if (errno == ERANGE) {
            fprintf(stderr, " Error range, got %f\n", pile[dp-1]);
            errno = 0;
        }
    }

    return pile[dp-1];
}

int
main(void )
{
    char *in = "(-(-1) + $((-1) * (-1)-(4 * (-1))))/2";
    char *out;

    infix_postfix(in, strlen(in), &out);

    printf("%s\n", out);

    free(out);
}
