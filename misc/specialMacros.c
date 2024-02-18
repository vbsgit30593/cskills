#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// concatenate the actual variable name
#define PRINT_VAR(X) \
    printf(#X " is %d at addr %p\n", X, &X)

int main(void){
    int a = 10;
    PRINT_VAR(a);
    return 0;
}