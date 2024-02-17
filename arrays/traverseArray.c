#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define newline printf("\n")
int main(int argc, char* argv[])
{
    int array[] = {1, 2, 3, 4, 5};
    int *ptr = array;
    size_t size = sizeof(array)/ sizeof(int);
    printf("Size : %lu\n", size);

    // for (int i = 0; i < size; i++){
    //     printf("%d ", ptr[i]);
    // }
    for (int i = 0; i <= size; i++){
        printf("%p ", array + i);
        //sleep(1);
    }
    newline;
    for (int* ptr = &array[0]; ptr < &array[size]; ptr++){
        printf("%d ", *ptr);
        //sleep(1);
    }
    newline;
}