#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define MAX_CHARS 1024
int main(void) {
    char str[] = "123,0xf,0101 ";
    char *end = str;
    printf("Read string: %s\n", str);
    // Task: Read all numbers in a sentence
    long int num;
    long int sum = 0;
    while (*end != '\0'){
        num = strtol(end, &end, 0);
        printf("Num read: %ld\n", num);
        sum += num;
        while (*end == ' ' || *end == ','){
            end++;
        }
    }

    printf("SUM: %ld\n", sum);
    return 0;
}