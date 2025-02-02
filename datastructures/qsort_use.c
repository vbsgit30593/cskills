#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int *)a - *(int *)b);
}

void sort(int *ar, size_t size)
{
    qsort(ar, size, sizeof(int), compare);
}

void print_array(const char* label, int *ar, size_t size)
{
    for(int i = 0; i < size; ++i)
    {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

int main(void)
{
    int ar[] = {10, 2, 4, 5, 3, 6, 7};
    size_t size = sizeof(ar)/sizeof(ar[0]);
    print_array("before", ar, size);
    sort(ar, size);
    print_array("after", ar, size);
    return 0;
}