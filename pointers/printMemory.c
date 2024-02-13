#include <stdio.h>
#include <stdlib.h>
// #pragma pack(2)

typedef struct{
    int test;
    char k;
    char str[10];
    int* p;
    short sh;
} Thing;

void printMemorySpace(const void* thing){
    unsigned char* ptr = (unsigned char *)thing;
    size_t size = sizeof(Thing);
    unsigned char data;
    for (int i = 0; i < size; ++i){
        if (i % 8 == 0){
            printf("\n");
        }
        data = ptr[i];
        printf("%03hhu ", data);
    }
    printf("\n");
}



int main(void){
    int a = 20;
    printf("ptr address :%p, struct size: %lu \n", &a, sizeof(Thing));
    Thing t = {10, 'A', "abcd", &a, 2};

    printMemorySpace(&t);
    return 0;
}
