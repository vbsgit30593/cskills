#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void printArray(void *ar, int size){
    for (int i = 0; i < size; ++i){
        printf("%02x ", ((char *)ar)[i]);
    }
    printf("\n");
}
int main(){
    int ar1[] = {30, 28, 32, 41}; // 16 bytes
    printArray(ar1, 4 * sizeof(int));

    long long ar2[] = {30, 28, 32, 41}; // 32  bytes
    printArray(ar2, 4 * sizeof(long long));

    return 0;
}