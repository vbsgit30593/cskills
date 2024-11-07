#include <stdlib.h>
#include <stdio.h>

enum foo {
    foo_2 = 0,
    foo_3,
    foo_4
};

static int squares[] = {
    [foo_2] = 4,
    [foo_4] = 9,
    [foo_3] = 16,
};

static char case_converter[] = {
    ['a'] = 'A',
    ['b'] = 'B',
    ['c'] = 'C',
};

int main(int argc, char **argv)
{
    printf("Square of %d is %d\n", foo_3, squares[foo_3]);
    printf("Upper case of 'a' is %c\n", case_converter['a']);
    return 0;
}