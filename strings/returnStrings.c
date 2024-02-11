#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void getString(char *str){
    strcpy(str, "test");
}
int main(int argc, char* argv[]){
    char string[100];
    getString(string);
    printf("Original string: %s\n", string);

    string[0] = 'p';
    printf("New string: %s\n", string);
    return 0;
}