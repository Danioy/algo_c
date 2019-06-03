/**
 * Exercise 4-9
 * notes: details see "Infix to postfix conversion algorithm.md"
 */

#include <stdio.h>
#include <string.h>
#include "item.h"
#include "stack.h"

int
main(void )
{
    char *in = "( 5 * ( ( 9 * 8 ) + ( 7 * ( 4 + 6 ) ) ) )";
    char post[100];
    memset(post, 0x00, 100 * sizeof(char));

    size_t i, j, N = strlen(in);
    char x;

    stack_init(N);

    for ( i = 0, j = 0; i < N; i++)
    {
        if ((in[i] >= '0') && (in[i] <= '9'))
            post[j++] = in[i];
        if (in[i] == '(')
            push(in[i]);
        if (in[i] == ')')
            while ((x = pop()) != '(')
                post[j++] = x;
        if ((in[i] == '*') || (in[i] == '+'))
            push(in[i]);
    }
    while (!is_empty()) post[j++] = pop();

    printf("%s\n", post);
}
