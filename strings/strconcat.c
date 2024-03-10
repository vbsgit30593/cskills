#include <stdio.h>
#include <string.h>
int main(void)
{
    char str1[20] = "Hello";
    char str2[] = "asdasdsadasdaasdasdasdasdad";
    strncat(str1, str2, 20 - strlen(str1) - 1);
    printf("String %s of length %zd \n", str1, strlen(str1));
    return 0;
}