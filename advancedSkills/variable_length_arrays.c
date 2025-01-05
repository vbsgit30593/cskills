#include <stdio.h>
#include <alloca.h>

#define FILL_ARRAY(count, array) do {          \
    for (int i = 0; i < count; i++)\
    {\
        array[i] = i + 1;\
    }\
} while(0)

#define PRINT_ARRAY(count, array) do { \
    for (int i = 0; i < count; i++)\
    {\
        printf("%d ", array[i]);\
    }\
    printf("\n"); \
} while(0)

int main(void)
{
    int length = 10;
    int array[length];
    int *other;
    other = alloca(length * (sizeof *other));
    FILL_ARRAY(10, array);
    PRINT_ARRAY(10, array);
    printf("############\n");
    FILL_ARRAY(10, other);
    PRINT_ARRAY(10, other);
    return 0;
}