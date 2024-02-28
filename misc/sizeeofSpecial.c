#include <stdio.h>
int main(void){
    int a = 10;
    printf("sizeof a: %lu \n", sizeof(++a));
    printf("a = %d\n", a);

    return 0;
}