#include <stdio.h>

struct Vector {
    int x;
    int y;
};

void print_point(struct Vector v)
{
    printf("(x, y) : (%d, %d)\n", v.x, v.y);
}

void print_array(size_t size, int ar[])
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

int main(void)
{
    print_point((struct Vector){10, 20});
    print_array(5, (int []){1, 2, 3, 4, 5});
    return 0;
}