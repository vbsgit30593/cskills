#include <stdio.h>
#include <stdlib.h>

int main(void){
    // start with printf
    char *text = "text";
    printf("Hello %s\n", text);

    // s'printf' -> Implies store to buffer
    char buf[20];
    sprintf(buf, "Hello %s", text);
    printf("buf after sprintf : %s\n", buf);

    // problem is that it allows unrestricted buf copy and hence has potential for buf overflow
    // SOLUTION - USE `snprintf`
    snprintf(buf, 10, "hello %s", "snprintf");
    printf("buf after snprintf(10): %s\n", buf);

    fprintf(stderr, "Hello text %s", "fprintf\n");

    // safe options
    // sprintf_s(buf, "Hello %s", text);
    // printf("buf after snprintf(10): %s\n", buf);

    // other options
    // w - wide char
    // v - var args list

    return 0;
}