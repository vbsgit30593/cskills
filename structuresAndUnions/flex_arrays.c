#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// defining a struct with flexible array member
struct FlexArray {
    int size;
    int data[]; // flexible array member
};

int main(void) {

    int n = 5; // number of elements in the flexible array
    // allocate memory for the struct plus space for n integers
    struct FlexArray *fa = malloc(sizeof(struct FlexArray) + n * sizeof(int));
    if (fa == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    fa->size = n;
    // initialize the flexible array member
    for (int i = 0; i < n; i++) {
        fa->data[i] = i * 10;
    }
    // print the elements of the flexible array member
    for (int i = 0; i < fa->size; i++) {
        printf("fa->data[%d] = %d\n", i, fa->data[i]);
    }
    // Getting size of the struct with flexible array member using stddef.h
    printf("size with flexible array member: %d\n", struct_size(FlexArray, data, n)); 
    // free the allocated memory
    free(fa);
    return 0;
}