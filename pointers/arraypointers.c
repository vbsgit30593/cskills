#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void sizeof_quirks()
{
    int ar[] = {1, 2, 3};
    printf("sizeof(ar)=%zu, sizeof(ar + 1)=%zu\n", sizeof(ar), sizeof(ar + 1));
}

int main(void)
{
    int ar[] = {1, 3, 4};
    int ar1[] = {1, 3, 4};
    int *ptr1 = ar;
    int (*ptr2)[] = &ar;
    printf("Before: ptr1=%p, ptr2=%p\n", ptr1, ptr2);
    int (*ptr3)[3] = &ar;
    printf("After: ptr1=%p, ptr3=%p\n", ptr1, ptr3);
    ptr3++;
    printf("After increment: ptr1=%p, ptr3=%p\n", ptr1, ptr3);
    sizeof_quirks();

    int mat[2][3];
    memcpy(mat[0], ar, sizeof(ar));
    memcpy(mat[1], ar1, sizeof(ar1));
    int (*matptr)[3] = mat;
    int **matptr2 = (int **)mat;
    printf("matptr=%p, matptr2=%p\n", matptr, matptr2);
    matptr++;
    matptr2++;
    printf("After increment: matptr=%p, matptr2=%p\n", matptr, matptr2);

    return 0;
}
