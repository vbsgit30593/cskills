#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int rand_interval(int low, int high) {
    int interval = high - low;
    return (rand() % interval) + low;
}

double rand_double(){
    // gets us numbers between 0 and 1
    return rand() / (double)RAND_MAX;
}

double rand_double_range(int low, int high){
    // gets us floating point numbers between low and high
    return (rand_double() * (high - low)) + low;
}
int main(void) {
    srand(time(NULL));
    // Get a number between 50 and 150
    int num = rand() % 100 + 50;
    for (int i = 0; i < 10; i++){
        printf("%d \t", rand_interval(50, 150));
    }
    printf("\n\n");
    for (int i = 0; i < 10; i++){
        printf("%lf \t", rand_double());
    }
    printf("\n\n");
    for (int i = 0; i < 10; i++){
        printf("%lf \t", rand_double_range(50, 150));
    }
    printf("\n\n");
    return 0;
}