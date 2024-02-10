#include <stdio.h>
#include <stdbool.h>

bool areEqualArrays(int *ar1, size_t size1, int *ar2, size_t size2){
    if (size1 != size2){
        return false;
    }

    int countSameItems = 0;
    while (*ar1 == *ar2){
        countSameItems++;
        ar1++;
        ar2++;
    }
    return (countSameItems == size1);
}
int main(){
    int ar1[] = {1, 2, 3, 4};
    int ar2[] = {1, 2, 3, 4};
    int ar3[] = {1, 2, 5, 4};
    int size1 = sizeof(ar1)/sizeof(int);
    int size2 = sizeof(ar2)/sizeof(int);
    int size3 = sizeof(ar3)/sizeof(int);

    printf("Is ar1 == ar2 : %d\n", areEqualArrays(ar1, size1, ar2, size2));
    printf("Is ar2 == ar3 : %d\n", areEqualArrays(ar2, size2, ar3, size3));

    return 0;
}