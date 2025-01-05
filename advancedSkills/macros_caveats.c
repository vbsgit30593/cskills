#include <stdio.h>

#define SUM(a, b) do {             \
    int sum = 0;                \
    for (int i = a; i < b; i++) \
        sum += i;               \
    printf("Sum : %d\n", sum);  \
} while(0)

int main(void)
{
    int a = 10, b = 20;
    if (1)
        SUM(a, b);
    else
        printf("else\n");
    return 0;
}
