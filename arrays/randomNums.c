#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
    time_t secondsSinceEpoch = time(NULL);
    // time function actually takes a ptr - Returns the value and saves time in that ptr

    srand(secondsSinceEpoch);
    printf("%d \n", rand());
    printf("%d \n", rand());
    printf("%d \n", rand());
    return 0;
}