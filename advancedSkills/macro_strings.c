#include <stdio.h>

#define print(a, b) printf("(%s, %s) = (%d, %d)\n", #a, #b, (a), (b))
#define VAR(x) new_##x
#define GETVAR(x) new_##x

int main(void)
{
    int a = 10, b = 20;
    int VAR(c) = 10;
    print(a, b);
    printf("New value : %d\n", GETVAR(c));
    return 0;
}
