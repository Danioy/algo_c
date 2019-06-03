#include <stdio.h>
#include <string.h>
#include "item.h"
#include "stack.h"

int
main(int argc, char *argv[])
{
    char *a = argv[1];
    size_t i, N = strlen(a);

    stack_init(N);

    for ( i = 0; i < N; i++)
    {
        if (a[i] == ')')
            printf("%c ", pop());
        if ((a[i] == '*') || (a[i] == '+'))
            push(a[i]);
        if ((a[i] >= '0') && (a[i] <= '9'))
            printf("%c ", a[i]);
    }

    printf("\n");
}
