#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// loop count
const int LOOPS = 10;

static int count = 1;

// a MAX buffer limit
#define MAX_BUCKETS 10

// declare a bounded buffer
int buffer[MAX_BUCKETS];

// fill index and empty index tracker
int fill = 0, use = 0;

// declare two semaphores - one for fill and other for empty
sem_t empty, full;
sem_t mutex;

// function to put to buffer
void put(int val)
{
    buffer[fill] = val;
    fill = (fill + 1) % MAX_BUCKETS;
}

// function to get from buffer
int get()
{
    int tmp = buffer[use];
    use = (use + 1) % MAX_BUCKETS;
    return tmp;
}

// producer thread
void * producer(void *arg)
{
    /* for(int i = 0; i < LOOPS; i++) */
    int i = 1;
    while(i <= 100000)
    {
        // printf("%lu: Waiting for consumer\n", (unsigned long)pthread_self());
        sem_wait(&empty);
        sem_wait(&mutex);
        put(count++);
        i++;
        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

// consumer thread
void * consumer(void *arg)
{
    int i = 1;
    while (i <= 100000)
    {
        // printf("%lu: Waiting for producer\n", (unsigned long)pthread_self());
        sem_wait(&full);
        sem_wait(&mutex);
        int tmp = get();
        sem_post(&mutex);
        sem_post(&empty);
        i++;
        printf("Read value: %d\n", tmp);
    }
}

const int NUM_THREADS = 10;

// main function
int main(void)
{
    sem_init(&empty, 0, MAX_BUCKETS);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_t prod[NUM_THREADS], cons[NUM_THREADS];

    for(int i = 0;i < NUM_THREADS; i++)
    {
        if (pthread_create(&prod[i], NULL, producer, NULL) != 0)
        {
            perror("Could not create thread");
            exit(0);
        }
    }

    for(int i = 0;i < NUM_THREADS; i++)
    {
        if (pthread_create(&cons[i], NULL, consumer, NULL) != 0)
        {
            perror("Could not create thread");
            exit(0);
        }
    }

    for(int i = 0;i < NUM_THREADS; i++)
    {
        if (pthread_join(prod[i], NULL) != 0)
        {
            perror("Could not join thread");
            exit(0);
        }
    }

    for(int i = 0;i < NUM_THREADS; i++)
    {
        if (pthread_join(cons[i], NULL) != 0)
        {
            perror("Could not join thread");
            exit(0);
        }
    }


    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);
    printf("Final count: %d\n", count);
    return 0;
}
