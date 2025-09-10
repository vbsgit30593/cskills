#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef bool (*cmp_fn_t)(const void *a, const void *b);
typedef void (*clear_cb_t)(void *entry, void *arg);

typedef struct DLNode {
    void *val;
    struct DLNode *prev;
    struct DLNode *next;
} DLNode;

typedef struct DLL {
    DLNode *head;
    DLNode *tail;
    int size;

    cmp_fn_t cmpfn;
    clear_cb_t clear_cb;
} DLL;

/*
 * Keep a clear cb to free entries whenever they are removed
 * Add a cmp function to use for comparison which would be needed to find nodes
 */
DLNode *create_node(void *data);
DLL *create_dlist(void *clear_cb, void *cmp);

void insert_between(DLL *dll, DLNode *prev, DLNode *next, void *val);
