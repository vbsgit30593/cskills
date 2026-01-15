#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define NUM_OBJECTS 100

// Lets start off with a basic memory object structure
typedef struct {
    int a;
    int b;
    int c;
} OBJECT;

typedef struct {
    bool allocated;
    OBJECT obj;
} POOL_OBJECT;

POOL_OBJECT mempool[NUM_OBJECTS] = {0};

// Functions required for memory pool management
POOL_OBJECT *mempool_alloc(void)
{
    // basic: lets traverse and find a free slot
    for (int i = 0; i < NUM_OBJECTS; i++)
    {
        if (!mempool[i].allocated)
        {
            mempool[i].allocated = true;
            return &mempool[i];
        }
    }

    return NULL;
}

void mempool_free(POOL_OBJECT *ptr)
{
    assert(ptr->allocated == true);
    // lets initially traverse and free
    /* for (int i = 0; i < NUM_OBJECTS; i++) */
    /* { */
    /*     POOL_OBJECT *cur = &mempool[i]; */
    /*     if (cur == ptr) */
    /*     { */
    /*         mempool[i].allocated = false; */
    /*         return; */
    /*     } */
    /* } */

    unsigned int freeidx = ((uintptr_t)ptr - (uintptr_t)mempool) / sizeof(POOL_OBJECT);
    assert(&mempool[freeidx] == ptr);
    mempool[freeidx].allocated = false;
    // this should not happen; if it happens then this would be a bug
    /* assert(false && "Could not match the passed address"); */
}

int main(void) {
    // Allocate some objects from the memory pool
    #define NUM_ALLOCS 120
    // Whats the reason for using an array of object pointers here?
    // We have a statically allocated memory pool of OBJECTs. These objects
    // are structs stored in the mempool array. To access any struct, we need to
    // know its address. By using an array of OBJECT pointers, we can keep track
    // of the addresses of the allocated objects in the memory pool. This allows
    // us to easily reference and manipulate the allocated objects later in the code.
    POOL_OBJECT *allocated_objects[NUM_ALLOCS] = {0};
    for (int i = 0; i < NUM_ALLOCS; i++)
    {
        // we request for any available slot
        allocated_objects[i] = mempool_alloc();
        if (allocated_objects[i])
        {
            assert(allocated_objects[i]->allocated == true);
            printf("%d: Allocated: %p\n", i, allocated_objects[i]);
        }
        else
        {
            printf("%d: Allocation request failed!!\n", i);
        }
    }
    // freeing all the allocated space
    for (int i = 0; i < NUM_ALLOCS; i++)
    {
        if (!allocated_objects[i])
        {
            printf("%d: Object not allocated\n", i);
            continue;
        }
        if (allocated_objects[i]->allocated)
        {
            mempool_free(allocated_objects[i]);
            printf("Freed allocated slot %d\n", i);
        }
    }

    return 0;
}
