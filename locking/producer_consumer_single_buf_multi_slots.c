#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

char uninit[10000];
char temp[10000];

#define MAX 5
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;
int buffer[MAX];
int val = 0;

FILE *f = NULL;

// put() function puts a value at the current slot in the buffer
void put(int val)
{
    buffer[fill_ptr] = val;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

// This function consumes the value in the current slot
int get()
{
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}

// producer produces till there available space in the buffer
void* producer(void *arg)
{
    int loops = *(int *)arg;
    for (int i = 0; i < loops; i++)
    {
        /* sleep(1); */
        pthread_mutex_lock(&mutex);
        while(count == MAX)
        {
            /* fprintf(f, "%s: TID: %lu waiting for queue data to be consumed\n", __func__, (unsigned long)pthread_self()); */
            pthread_cond_wait(&empty, &mutex);
        }
        val++;
        put(val);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


// consumer thread consumes till the buffer is empty
void* consumer(void *arg)
{
    int loops = *(int *)arg;
    for (int i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&mutex);
        while(count == 0)
        {
            /* fprintf(f, "%s: TID: %lu waiting for queue data to be filled\n", __func__, (unsigned long)pthread_self()); */
            pthread_cond_wait(&fill, &mutex);
        }
        int tmp = get();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        /* fprintf(f, "Value consumed by thread %lu : %d\n", (unsigned long int)pthread_self(), tmp); */
    }
    return NULL;
}

int main_old(void)
{
    pthread_t prod_t, cons_t;
    int prod_loops = 50;
    int cons_loops = 50;
    if(pthread_create(&prod_t, NULL, producer, &prod_loops) != 0)
    {
        perror("Could not create producer threads");
        exit(0);
    }
    if(pthread_create(&cons_t, NULL, consumer, &cons_loops) != 0)
    {
        perror("Could not create consumer threads");
        exit(0);
    }

    if(pthread_join(prod_t, NULL) != 0)
    {
        perror("Could not join producer");
        exit(1);
    }

    if(pthread_join(cons_t, NULL) != 0)
    {
        perror("Could not join consumer");
        exit(1);
    }

    return 0;
}

#define NUM_PRODS 10
#define NUM_CONS 10

int main(void)
{
    f = fopen("try.txt", "w");
    pthread_t prod_t[NUM_PRODS], cons_t[NUM_CONS];
    int prod_loops = 500000;
    int cons_loops = 500000;
    /* int prod_loops = 5000000; */
    /* int cons_loops = 5000000; */
    for(int i = 0; i < NUM_PRODS; i++)
    {
        if(pthread_create(&prod_t[i], NULL, producer, &prod_loops) != 0)
        {
            perror("Could not create producer threads");
            exit(0);
        }
    }
    for(int i = 0; i < NUM_CONS; i++)
    {
        if(pthread_create(&cons_t[i], NULL, consumer, &cons_loops) != 0)
        {
            perror("Could not create consumer threads");
            exit(0);
        }
    }

    for(int i = 0; i < NUM_PRODS; i++)
    {
        if(pthread_join(prod_t[i], NULL) != 0)
        {
            perror("Could not join producer");
            exit(1);
        }
    }

    for(int i = 0; i < NUM_CONS; i++)
    {
        if(pthread_join(cons_t[i], NULL) != 0)
        {
            perror("Could not join consumer");
            exit(1);
        }
    }

    fclose(f);
    return 0;
}
