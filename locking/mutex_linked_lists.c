#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

pthread_mutex_t lock;
ListNode* head = NULL;

void insert(ListNode **head, int val) {
    pthread_mutex_lock(&lock);
    ListNode *temp = *head;
    ListNode *newnode = calloc(1, sizeof(ListNode));
    if (!newnode) {
        perror("Could not allocate memory!");
        exit(0);
    }

    newnode->data = val;
    newnode->next = temp;
    *head = newnode;
    pthread_mutex_unlock(&lock);
}

void delete_front(ListNode **head) {
    // this function deletes the node and also takes ownership
    // of the deleted node. It frees the memory for the node.

}

void delete_end(ListNode **head) {

}

void print_list(ListNode *head) {
    printf("Printing list\n");
    ListNode *temp = head;
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void* thread_func(void* arg) {
    int id = *(int *)arg;

    for (int i = 1; i <= 100; i++) {
        insert(&head, id + i);
    }
    insert(&head, 9999);
    print_list(head);

    return NULL;
}
int main(int argc, char *argv[]) {
    int ret;
    pthread_t threads[3];
    int tids[] = {1, 2, 3};

    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < 3; ++i) {
        if (pthread_create(&threads[i], NULL, thread_func, &tids[i]) != 0) {
            perror("Could not create thread");
            exit(0);
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Could not join threads");
            exit(0);
        }
    }
    pthread_mutex_destroy(&lock);
    return 0;
}

/*
* This version just grabs a mutex lock on the critical section
* its a global lock
*/
