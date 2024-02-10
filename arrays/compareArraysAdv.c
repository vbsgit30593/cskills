#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(){
    int ar1[] = {1, 2, 3, 4};
    int ar2[] = {1, 2, 3, 4};

    if (0 == memcmp(ar1, ar2, 4 * sizeof(int))) {
        printf("Arrays are same\n");
    }
    else {
        printf("Arrays are different\n");
    }

    return 0;
}