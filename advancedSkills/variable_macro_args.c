#include <stdio.h>

#define PRINTF_VARS(func, count, ...) do {           \
    for (int i = 0; i < count; ++i)       \
        printf("Function " #func ": " __VA_ARGS__);              \
} while (0)

void func();

int main(void)
{
    PRINTF_VARS(func, 2, "hello %d whats up %s\n", 10, "vaibhav");
    PRINTF_VARS(func, 3, "hello %d more args here %s - new arg %f\n", 10, "vaibhav", 1.1);
    return 0;
}