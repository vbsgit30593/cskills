#include <stdio.h>
#include <string.h>

typedef struct Point{
    int x;
    int y;
}Point;

void printStruct(const void* data, size_t size){
    const char *ptr = (const char *)data;
    for (int i = 0; i < size; ++i){
        printf("%02x ", ptr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    Point p1 = {
        .x = 10,
        .y = 20
    };

    printStruct(&p1, sizeof(Point));
    return 0;
}