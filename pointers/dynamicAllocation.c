#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int *mem1, *mem2;
    if (NULL == (mem1 = (int *)malloc(10* sizeof(int)))){
        return 1;
    };

    if (NULL == (mem2 = (int *)calloc(10, sizeof(int)))){
        return 2;
    }

    printf("Memstatus before!\n");
    for (int i = 0; i < 10; i++){
        printf("mem1[%d], mem2[%d]: (%d, %d) \n",i, i, mem1[i], mem2[i]);
    }

    memset(mem1, 0, 10 * sizeof(int));
    for (int i = 0; i < 10; i++){
        mem1[i] = i + 1;
        mem2[i] = i * i;
    }

    printf("Memstatus after!\n");
    for (int i = 0; i < 10; i++){
        printf("mem1[%d], mem2[%d]: (%d, %d) \n",i, i, mem1[i], mem2[i]);
    }

    // reallocate memory
    mem1 = realloc(mem1, 64 * sizeof(int));
    if (mem1 == NULL){
        return 3;
    }

    
    free(mem1);
    free(mem2);
}