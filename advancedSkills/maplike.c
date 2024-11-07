/*
Implement this functionality in C
>>> square = lambda x:x ** 2
>>> square(2)
4
>>> list(map(square, l))
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]

>>> cube = lambda x:x ** 3
>>> list(map(cube, l))
[0, 1, 8, 27, 64, 125, 216, 343, 512, 729]
*/

#include <stdio.h>
#include <stdlib.h>

int square(int x)
{
    return x * x;
}

int cube(int x)
{
    return x * x * x;
}

int* map(int *ar, size_t size, int (*func)(int))
{
    int *res = calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        res[i] = func(ar[i]);
    }
    return res;
}

void print(int *ar, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

int main(void)
{
    int ar[] = {10, 2, 30, 14, 5};

    int *squared = map(ar, 5, square);
    int *cubed = map(ar, 5, cube);
    print(squared, 5);
    print(cubed, 5);

    free(squared);
    free(cubed);
    squared = NULL;
    cubed = NULL;

    return 0;
}