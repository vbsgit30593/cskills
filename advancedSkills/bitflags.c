#include <stdio.h>

typedef unsigned int FLAGS_TYPE;

#define FLAG_A (1 << 0)
#define FLAG_B (1 << 1)
#define FLAG_C (1 << 2)


void take_action(FLAGS_TYPE flags)
{
    if (flags & FLAG_A)
    {
        printf("FLAG_A\n");
    }
    if (flags & FLAG_B)
    {
        printf("FLAG_B\n");
    }
    if (flags & FLAG_C)
    {
        printf("FLAG_C\n");
    }
    printf("---\n");
}

int main(void)
{
    take_action(FLAG_A);
    take_action(FLAG_A | FLAG_B);
    take_action(FLAG_B | FLAG_C);
    return 0;
}