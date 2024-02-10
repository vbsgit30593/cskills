#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(){
    int ar1[] = {1, 2, 3, 4};
    int ar2[] = {2, 5, 8, 10};

    memcpy(ar1, ar2, 4 * sizeof(int));
    printf("%d %d \n", ar1[0], ar1[2]);;

    return 0;
}