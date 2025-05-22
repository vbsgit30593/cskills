#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t lock; 
uint64_t sum = 0;

void do_some_work(int reps) {
    pthread_mutex_lock(&lock);
    for(int i = 1; i <= reps; ++i) {
        sum += i;
    }
    pthread_mutex_unlock(&lock);
}
void* worker(void* arg) {
    printf("Created thread with id : %lu\n", (unsigned long)pthread_self());
    do_some_work(1000);
    return NULL;
}

int main(void) {
    pthread_t threads[3];

    pthread_mutex_init(&lock, NULL);

    // create threads
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, worker, NULL) != 0) {
            perror("Could not create thread: ");
            exit(0);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Could not join thread: ");
            exit(0);
        }
    }
    // join threads
    pthread_mutex_destroy(&lock);
    printf("Final sum: %llu\n", sum);
}
