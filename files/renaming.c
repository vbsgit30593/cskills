#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    int res = rename("point1.dat", "point2.dat");
    if (res == 0){
        printf("File renamed successfully\n");
    }
    else{
        char buf[256];
        printf("Failed to rename: %s\n", strerror(errno));
    }
    return 0;
}