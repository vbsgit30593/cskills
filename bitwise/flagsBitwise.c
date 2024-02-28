#include <stdio.h>

#define FIRST 0b01
#define SECOND 0b10
#define THIRD 0b10000

void checkFlags(unsigned char f){
    printf("\n");
    if (f & FIRST){
        printf("FIRST ENABLED\n");
    }
    if (f & SECOND){
        printf("SECOND ENABLED\n");
    }
    if (f & THIRD){
        printf("THIRD ENABLED\n");
    }
}
int main(void){
    unsigned char flags = FIRST | SECOND | THIRD;
    printf ("Flags: %hhu \n", flags);
    checkFlags(flags);
    // Disable FIRST now
    flags = flags & ~FIRST;
    checkFlags(flags);

    // Enable FIRST again
    flags = flags | FIRST;
    checkFlags(flags);
    return 0;
}