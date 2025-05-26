#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum = 1;

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct Queue {
    ListNode *head;
    ListNode *tail;
    pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;
} Queue;

void queue_init(Queue *q) {
    ListNode *tmp = calloc(1, sizeof(ListNode));
    tmp->next = NULL;

    q->head = q->tail = tmp;
    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);
}

void enqueue(Queue *q, int val) {
    ListNode *newnode = calloc(1, sizeof(ListNode));
    assert(newnode != NULL);
    newnode->next = NULL;
    newnode->data = val;

    pthread_mutex_lock(&q->tail_lock);

    q->tail->next = newnode;
    q->tail = newnode;
    
    sum += val;
    pthread_mutex_unlock(&q->tail_lock);

}

int dequeue(Queue *q) {
    pthread_mutex_lock(&q->head_lock);

    ListNode *tmp = q->head;
    if (tmp->next == NULL) return -1;

    ListNode *next = tmp->next;
    tmp->next = NULL;
    q->head = next;
    pthread_mutex_unlock(&q->head_lock);
    
    free(tmp);
    return 0;
}

void print_list(Queue *q) {
    pthread_mutex_lock(&q->head_lock);
    pthread_mutex_lock(&q->tail_lock);

    ListNode *head = q->head;
    ListNode *tail = q->tail;



    pthread_mutex_unlock(&q->head_lock);
    pthread_mutex_unlock(&q->tail_lock);
}
void * thread_func(void *arg) {
    Queue *q = arg;
    printf("inside thread: %lu", (unsigned long int)pthread_self());
    for (int i = 0; i < 10000; i++)
    {
        enqueue(q, sum);
    }
    print_list(q);
    for (int i = 0; i < 10000; i++)
    {
        enqueue(q, sum);
    }

    return NULL;
}

void queue_release(Queue *q) {
    pthread_mutex_destroy(&q->head_lock);
    pthread_mutex_destroy(&q->tail_lock);
}

const int NUM_THREADS = 2;
int main(void) {
    pthread_t t[NUM_THREADS];
    Queue q;
    queue_init(&q);
    
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&t[i], NULL, thread_func, &q) != 0) {
            perror("Thread creation failed!");
            exit(0);
        }
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(t[i], NULL) != 0) {
            perror("Thread join failed!");
            exit(0);
        }
    }

    queue_release(&q);
    return 0;
}
