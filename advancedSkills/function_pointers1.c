#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool iseven(int num)
{
    return (num % 2 == 0);
}

bool alltrue(int num)
{
    return true;
}

void print_if(int ar[5], bool (*func)(int))
{
    for (int i = 0; i < 5; ++i)
    {
        if (func(ar[i]))
        {
            printf("%d\n", ar[i]);
        }
    }
}

int compare(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}

int main(int argc, char **argv)
{
    int ar[] = {10, 2, 30, 14, 5};
    print_if(ar, iseven);
    printf("------\n");
    print_if(ar, alltrue);
    qsort(ar, 5, sizeof(int), compare);
    printf("------\n");
    print_if(ar, alltrue);
    return 0;
}