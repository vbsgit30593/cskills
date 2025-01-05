#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int dec = 10;
    int oct = 0123;
    int hex = 0xffab;
    int bin = 0b0101010;

    printf("%d | %o | %x | %b \n", dec, oct, hex, bin);
    // Here %b is not C stqanda
    return 0;
}