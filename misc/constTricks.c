#include <stdio.h>
#include <stdlib.h>

int main(void){
    // const ptr to integer
    int n = 10, m = 20;
    const int* ptr = &n;
    int* const ptr1 = &n;
    // *ptr = 20; // not allowed
    ptr = &m;
    *ptr1 = 30;
    // ptr1 = &m; // not allowed
    return 0;
}