#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(void){
    char str1[] = "101";
    char str2[] = "1111111111111111111111111111111111";
    char str3[] = "124 name";
    char str4[] = "0x124";
    char str5[] = "01011";

    int num = atoi(str1);
    printf("Original string: %s, Converted number: %d\n", str1, num);

    /* Problem 1 */
    num = atoi(str2);
    printf("Original string: %s, Converted number: %d\n", str2, num);
    // note that for very large numbers atoi will just randomly
    // provide you junk values without highlighting any issues
    // undefined behavior beyond MAX_INT/MIN_INT

    /* Problem 2 */
    num = atoi(str3);
    printf("Original string: %s, Converted number: %d\n", str3, num);
    // Gives no hint about where the conversion to int stopped

    /* Problem 3 */
    num = atoi(str4);
    printf("Original string: %s, Converted number: %d\n", str4, num);
    // Conversion from other bases isnt possible

    /* Solution : use strto functions */
    long int newnum = strtol(str4, NULL, 16);
    printf("Original string: %s, Converted number: %ld\n", str4, newnum);

    newnum = strtol(str5, NULL, 0);
    printf("Original string: %s, Converted number: %ld\n", str5, newnum);

    char *next;
    newnum = strtol(str3, &next, 0);
    printf("Original string: %s, Converted number: %ld, name: %s \n", str5, newnum, next);

    newnum = strtol(str2, &next, 0);
    printf("Original string: %s, Converted number: %ld, name: %s \n", str2, newnum, next);
    printf("%d, %s\n", errno, strerror(errno));
    return 0;
}