/**
 * Exercise 4-10, 4-11, 4-12
 * notes: details see "Infix to postfix conversion algorithm.md"
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "item.h"
#include "stack.h"

void
infix_prefix( char *in, size_t len, char **out) {
    char *prefix = malloc(len * sizeof(char));
    memset(prefix, 0x00, len * sizeof(char));

    size_t i, j;
    char x;

    stack_init(len);

    for ( i = 0, j = 0; i < len; i++)
    {
        if ((in[i] >= '0') && (in[i] <= '9'))
            {prefix[j++] = in[i]; prefix[j++] = ' ';}
        if (in[i] == '(')
            push(in[i]);
        if (in[i] == ')')
            while ((x = pop()) != '(')
                prefix[j++] = x;
        if ((in[i] == '*') || (in[i] == '+'))
            push(in[i]);
    }
    while (!is_empty()) prefix[j++] = pop();

    *out = prefix;
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
        if ( *p == '+' ) pile[dp++] = pile[--dp] + pile[--dp];
        if ( *p == '*' ) pile[dp++] = pile[--dp] * pile[--dp];
        if ( *p == '/' ) pile[dp++] = pile[--dp] / pile[--dp];
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
    char *in = "( 5 * ( ( 9 * 8 ) + ( 7 * ( 4 + 6 ) ) ) )";
    char *out;

    infix_prefix(in, strlen(in), &out);

    printf("%s\n", out);

    // printf("%f \n", eval_prefix(out, strlen(out)));

    free(out);
}
