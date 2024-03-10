#include <stdio.h>
#include <string.h>

/*
# Task 1: Replace the first occurence of a substring with the new string
# Task 2: Replace all occurences of a substring with the new string
# Task 3: Delete all occurences of a substring in the main string
*/

char* string_replace(char* source, size_t sourceSize, char* substring, char* with) {
    // returns the substring end address of the updated string
    // or NULL if replacement failed */
    // handle case when replacement can cause mem overflow
    if (sourceSize < (strlen(source) + 1 + (strlen(with) - strlen(substring)))) {
        return NULL;
    }

    char* substring_start = strstr(source, substring);
    if (substring_start == NULL) {
        return NULL;
    }

    // move the memory to fit in the new replacement string
    memmove(
        substring_start + strlen(with),
        substring_start + strlen(substring),
        strlen(substring_start) - strlen(substring) + 1
    );

    // copy the replacement string
    memcpy(substring_start, with, strlen(with));

    // We used memcpy here instead of strcpy
    // since strcpy adds a \0 character at the end.
    return substring_start + strlen(with);
}

void string_replace_all(char* source, size_t sourceSize, char* substring, char* with){
    /* Replace all occurences of substring with new string */
    while(string_replace(source, sourceSize, substring, with) != NULL)
    {
        // Keep replacing until match is seen
    }
}

void string_delete_all(char* source, size_t sourceSize, char* substring){
    /* Delete all occurences of substring with new string */
    while(string_replace(source, sourceSize, substring, "") != NULL)
    {
        // Keep deleting until match is seen
    }
}
int main(int argc, char* argv[])
{
    char str[200] = "Replace apples with some more apples and other apples";

    printf("** Original input string **\n");
    printf("%s, Length: %zu\n\n",str, strlen(str));

    // Replace first occurence of apples with hamburgers
    if (string_replace(str, 200, "apples", "hamburgers")){
        printf("** String after first replacement **\n");
        printf("%s, Length: %zu\n\n", str, strlen(str));
    } else {
        printf("Unable to replace \n");
    }
    
    // Replace all occurences of apples with hamburgers
    string_replace_all(str, 200, "apples", "hamburgers");
    printf("** String after replacing all occurences **\n");
    printf("%s, Length: %zu\n\n", str, strlen(str));

    // Delete all occurences of hamburgers
    string_delete_all(str, 200, "hamburgers");
    printf("** String after deleting all occurences **\n");
    printf("%s, Length: %zu\n\n", str, strlen(str));
    return 0;
}