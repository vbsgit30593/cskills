#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int a; // Triggers an error if this variable is not externed in header file
int main(int argc, char* argv[])
{
    // a = 20;
    printf("%d \n",a);
    return 0;
}