#include <stdio.h>

int getMultipleResults(int num1, int num2, int* sum, int* prod){
    if (sum == NULL || prod == NULL){
        return -1;
    }
    *sum = num1 + num2;
    *prod = num1 * num2;
    return 0;
}

int main(void){
    int n1 = 10, n2 = 20;
    int sum, prod;

    int ret = getMultipleResults(n1, n2, &sum, &prod);
    //int ret = getMultipleResults(n1, n2, NULL, &prod);
    if (ret == 0){
        printf("Sum: %d, Prod: %d\n", sum, prod);
    }
    else {
        printf("Something went wrong\n");
    }

    return 0;
}