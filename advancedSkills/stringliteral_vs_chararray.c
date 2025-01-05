#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const char* str = "I am a string"; // rodata
    char array[] = "I am char array"; 
    char *news = strdup(str); // heap
    news[0] = 'A';
    printf("Strings: %s | %s | %s\n", str, array, news);
    return 0;
}