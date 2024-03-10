#include <stdio.h>
#include <string.h>

int main(void){
    /* Overall task: Find the number in the string (lets says age)*/

    // fetch a substring of the string such that the new string 
    // starts from the position where a number is present in the main string

    const char* orig = "Hello , I am 20 years old";
    char* new = NULL;

    // for (int i = 0; i < strlen(orig); i++) {
    //     if (orig[i] >= '0' && orig[i] <= '9') {
    //         new = (char *)orig + i;
    //         break;
    //     }
    // }

    new = strpbrk(orig, "0123456789");
    printf("Original : %s, New: %s \n", orig, new);

    // now we have the position where the number starts
    // we dont know when it ends 
    int count_num = strspn(orig, "0123456789");
    printf("strspn: Numeric data = ");
    for (int i = 0; i < strspn(new, "0123456789"); i++) {
        printf("%c", new[i]);
    }
    printf("\n");

    int count_not_num = strcspn(orig, "1234567890");
    printf("strcspn: Initial string data - %.*s\n", count_not_num, orig);

    return 0;

    
}