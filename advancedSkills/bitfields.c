#include <stdio.h>
#pragma pack(1)

typedef struct {
    int first: 4;
    int second: 4;
    int alone: 1;
    int last: 7;
} bitfields;

typedef struct {
    int first;
    int second;
    int alone;
    int last;
} non_bitfields;

int main(void)
{
    bitfields b;
    printf("sizeof b: %zu\n", sizeof b);
    printf("sizeof b: %zu\n", sizeof(non_bitfields));
    return 0;
}