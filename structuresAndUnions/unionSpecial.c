#include <stdio.h>
#include <stdbool.h>

typedef union {
    unsigned int v4addr;
    char octets[4];
} Example;


int main(int argc, char* argv[]){
    Example e;
    e.v4addr = 3232235777;
    printf("Number : %u\n", e.v4addr);
    for (int i = 0; i < 4; i++){
        printf("%hhu ", e.octets[i]);
    }
    printf("\n");

    e.octets[0] = 1;
    e.octets[1] = 1;
    e.octets[2] = 1;
    printf("Number : %u\n", e.v4addr);
    for (int i = 0; i < 4; i++){
        printf("%hhu ", e.octets[i]);
    }
    printf("\n");
    
    return 0;
}