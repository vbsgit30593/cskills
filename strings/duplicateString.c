#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Test{
    const char* stringtest;
}Test;
int main(void){
    Test t;
    char str[] = "hello"; 

    t.stringtest = strdup(str);
    printf("%s, %s\n", str, t.stringtest);
    printf("%p, %p\n",&str, &t.stringtest);
    free((char *)t.stringtest);
    t.stringtest = NULL;
    printf("%s, %s\n", str, t.stringtest);

    return 0;
}