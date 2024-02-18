#include <stdio.h>

int main(void){
    short int x = -16384;
    // int y = x;
    int y = 1073741824;
    printf("%hd %d\n", x, y);
    x = y; 
    // trimming takes place - y % 2^(bits in x)
    // 1073741824 % 2^16 => rem = 0
    printf("%hd %d\n", x, y);
    return 0;
}