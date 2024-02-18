#include <stdio.h>

long long add(int a, int b){
    return a + b;
}

long long mul(int a, int b){
    return a * b;
}

void exec(long long (*func)(int, int)){
    printf("Exec result: %llu\n", func(10, 20));
}

int main(void){
    long long (*fptr)(int, int);
    fptr = &mul;
    printf("Result: %lld\n", fptr(10, 20));
    exec(&add);
    exec(&mul);

    char *ptr1[20];
    char* ptr2[20];
    printf("ptr1 size: %lu, ptr2 size: %lu\n", sizeof(ptr1), sizeof(ptr2));
    return 0;
}