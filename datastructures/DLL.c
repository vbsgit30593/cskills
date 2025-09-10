#include "DLL.h"
/*
* Create a DLL node .
*   The node should have next and prev pointers
* Create a DLList class
*   Maintain a list head and tail
*/

DLNode* create_node(void *val) {
    DLNode *newnode = calloc(1, sizeof(DLNode));
    if (newnode == NULL) {
        perror("calloc failed");
        exit(0);
    }
        
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->val = val;
    return newnode;
}

bool cmp_str(const void *a, const void *b) {
    if (strcmp(a, b) == 0) return true;

    return false;
}

void free_str(void *str, void *arg) {
    free(str);
}

DLL *create_dlist(void *clear_cb, void *cmpfn) {
    DLL *dll = calloc(1, sizeof(DLL));
    if (!dll) return NULL;

    DLNode *dummy_head = create_node(NULL);
    DLNode *dummy_tail = create_node(NULL);

    dummy_head->next = dummy_tail;
    dummy_tail->prev = dummy_head;

    dll->head = dummy_head;
    dll->tail = dummy_tail;

    dll->clear_cb = clear_cb;
    dll->cmpfn = cmpfn;
    dll->size = 0;
    return dll;
}

bool is_empty(DLL *dll) {
    return dll->size == 0;
}

void insert_between(DLL *dll, DLNode *prev, DLNode *next, void *val) {
    DLNode *newnode = create_node(val);

    newnode->next = next;
    newnode->prev = prev;
    prev->next = newnode;
    next->prev = newnode;

    dll->size++;
}


void insert_front(DLL *dll, void *val) {
    DLNode *next = NULL;
    if (is_empty(dll)) {
        next = dll->tail;
    } else {
        next = dll->head->next;
    }

    insert_between(dll, dll->head, next, val);
}

void insert_end(DLL *dll, void *val) {
    DLNode *prev = NULL;
    if (is_empty(dll)) {
        prev = dll->head;
    } else {
        prev = dll->tail->prev;
    }

    insert_between(dll, prev, dll->tail, val);
}

void delete_node(DLL *dll, void *val) {
    
}

void delete_front(DLL *dll) {
    if (is_empty(dll)) {
        printf("Empty list!");
        return;
    }
    
    /* DLNode *front_node = head->head->next; */

}

void delete_end(DLL *dll) {
    if (is_empty(dll)) {
        printf("Empty list!");
        return;
    }

}

void print_list(DLL *dll) {
    if (is_empty(dll)) {
        printf("Empty list!");
        return;
    }

    for (DLNode *first = dll->head->next; first != dll->tail; first = first->next) {
        printf("%s\t", (char *)first->val);
    }
    printf("\n");
}

void destroy_dlist(DLL *dll) {

}

DLNode* find_node(DLL *dll, void *val) {
    return NULL;
}

int main(void) {
    DLL *dll = create_dlist(&free_str, &cmp_str);

    insert_front(dll, "hello");
    insert_end(dll, "world");
    insert_front(dll, "hello1");
    insert_front(dll, "hello1");
    insert_end(dll, "world2");
    insert_end(dll, "world2");

    print_list(dll);
    delete_front(dll);
    delete_end(dll);
    print_list(dll);

    return 0;
}
