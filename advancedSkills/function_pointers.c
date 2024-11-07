#include <stdio.h>

int sum(int a, int b)
{
    return a + b;
}

int diff(int a, int b)
{
    return a - b;
}

int main(int argc, char **argv)
{
    int a = 10, b = 20;
    int (*f)(int, int) = sum;
    printf("Sum of numbers: %d\n", f(a, b));
    f = diff;
    printf("Diff of numbers: %d\n", f(a, b));
    return 0;
}