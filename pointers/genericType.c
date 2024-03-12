#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT = sizeof(int),
    FLOAT = sizeof(float),
    UINT_32 = sizeof(long int),
    UINT_64 = sizeof(long long int)
} Datatype;

typedef struct {
    Datatype type;
    size_t size;
    void* data;
    void* top;
} Stack;

Stack stackCreate(size_t size, Datatype type) {
    Stack s = {
        .type = type,
        .size = size,
        .data = malloc(size * type),
        .top = NULL
    };
    printf("stackCreate - Data addr: %p\n", s.data);
    return s;
}

void freeStack(Stack* s){
    free(s->data);
    s->data = NULL;
}

int main(int argc, char* argv[]) {
    Datatype type = FLOAT;
    size_t size = 5;
    Stack s = stackCreate(size, type);
    printf("main - Data addr: %p\n", s.data);

    for (int i = 0; i < size; i++){
        ((float *)s.data)[i] = 111.2 + i;
        s.top = ((float *)s.data) + i;
    }

    for (int i = 0; i < size; i++){
        printf("%f \t", ((float *)s.data)[i]);
    }
    printf("\n");

    freeStack(&s);

    return 0;
}