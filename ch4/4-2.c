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
        if (a[i] == '+')
       push(pop() + pop());
     if (a[i] == '*')
       push(pop() * pop());
     if ((a[i] >= '0') && (a[i] <= '9'))
       push(0);
     while ((a[i] >= '0') && (a[i] <= '9'))
       push(10*pop() + (a[i++]-'0'));
    }

    printf("%d \n", pop());
}
