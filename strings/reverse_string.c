#include <stdio.h>
#include <string.h>
#include <string.h>

void reverse_string(char *str)
{
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right)
    {
        // swap characters
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

int main(void)
{
    // reverse a given string
    char str[] = "Hello, World!";
    printf("Original string: %s\n", str);
    reverse_string(str);
    printf("Reversed string: %s\n", str);
    return 0;
}