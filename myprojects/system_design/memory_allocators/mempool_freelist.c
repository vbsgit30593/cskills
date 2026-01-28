/*
 * What's different:
 * Freelist keeps track of the list of free array entries.
 * freelist should have borrow and return functionality.
 * expected T(n) for both should be O(1). Previously borrow was O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define NUM_OBJECTS 1000000
#define MIN(a, b) (a > b ? a : b)

// Lets start off with a basic memory object structure
typedef struct {
    int a;
    int b;
    int c;
} OBJECT;

typedef struct POOL_OBJECT {
    OBJECT obj;
    struct POOL_OBJECT *next;
} POOL_OBJECT;

POOL_OBJECT mempool[NUM_OBJECTS] = {0};

POOL_OBJECT *freelist = NULL;
static int freelist_size = NUM_OBJECTS;

__attribute__((constructor)) void freelist_init()
{
    printf("%s called\n", __FUNCTION__);
    for (int i = 0; i < NUM_OBJECTS - 1; i++)
    {
        mempool[i].next = &(mempool[i + 1]);
        /* freelist_size++; */
    }
    
    freelist = mempool;
    mempool[NUM_OBJECTS - 1].next = NULL;
}

// Functions required for memory pool management
OBJECT *mempool_alloc(void)
{
    // add to freelist
    if (!freelist) return NULL;

    // freelist points to the head of the list always.
    // return the entry at the head and move forward in the list
    POOL_OBJECT *borrowed_obj = freelist;
    freelist = freelist->next;
    borrowed_obj->next = NULL;
    freelist_size--;
    return &(borrowed_obj->obj);
}

bool mempool_free(OBJECT *ptr)
{
    if (freelist_size == NUM_OBJECTS || !ptr || !freelist) return false;
    unsigned int idx = ((uintptr_t)ptr - (uintptr_t)mempool) / sizeof(POOL_OBJECT);
    assert(&(mempool[idx].obj) == ptr);
    // a pool obj is being returned to the pool.
    // add it to the head of freelist and update head

    mempool[idx].next = freelist;
    freelist = &(mempool[idx]);
    freelist_size++;
    return true;
}

int main(void) {
    // Allocate some objects from the memory pool
    #define NUM_ALLOCS (NUM_OBJECTS)
    // Whats the reason for using an array of object pointers here?
    // We have a statically allocated memory pool of OBJECTs. These objects
    // are structs stored in the mempool array. To access any struct, we need to
    // know its address. By using an array of OBJECT pointers, we can keep track
    // of the addresses of the allocated objects in the memory pool. This allows
    // us to easily reference and manipulate the allocated objects later in the code.
    int round = 1;
    while (round <= 20)
    {
        OBJECT *allocated_objects[NUM_ALLOCS] = {0};
        int alloc_count = rand() % NUM_ALLOCS;
        printf("alloc_count = %d\n", alloc_count);
        int real_alloc = 0;
        for (int i = 0; i < alloc_count; i++)
        {
            // we request for any available slot
            allocated_objects[i] = mempool_alloc();
            if (allocated_objects[i])
            {
                real_alloc++;
            }
            /* else */
            /* { */
            /*     printf("%d: Allocation request failed!!\n", i); */
            /* } */
        }
        printf("Allocated %d objects from the pool, expected = %d\n",
               real_alloc, alloc_count);
        
        // freeing some memory
        int free_count = MIN(rand() % NUM_ALLOCS, real_alloc);
        int real_free = 0;
        for (int i = 0; i < free_count; i++)
        {
            if(mempool_free(allocated_objects[i])) real_free++;
        }
        printf("Freed %d objects and returned to pool, expected = %d\n",
               real_free, free_count);
        printf("Freelist size: %d\n", freelist_size);
        round++;
    }

    return 0;
}
