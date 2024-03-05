#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void validate(char str[]) {
    char *endptr;
    long int num = strtol(str, &endptr, 0);
    if (endptr == str){
        printf("Number could not be parsed\n");
        return;
    }
    if (errno == ERANGE) {
        printf("Number too large to parse!\n");
        return;
    }
    printf("Parsed number: %ld\n", num);
}
/* Check if the number is actually parsed */
int main(void) {
    char str1[] = "1111111111111111111111";
    char str2[] = "Hello World!";
    validate(str1);
    validate(str2);

    // char *endptr;
    // long int num = strtol(str1, &endptr, 0);
    // printf ("Num : %ld\n", num);
    // printf("strerror : %s\n", strerror(errno));
    return 0;
}