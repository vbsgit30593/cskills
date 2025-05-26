#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

int count = 0;
int buffer;

pthread_cond_t cond;
pthread_mutex_t mutex;

int get()
{
    // confirm that get is called only when buffer has data
    assert(count == 1);
    count = 0;
    return buffer;
}

void put(int val)
{
    // call put only if buffer is empty
    assert(count == 0);
    count = 1;
    buffer = val;
}

// producer thread
void * producer(void* arg)
{
    int loops = (int) arg;
    for (int i = 1; i <= 100; i++)
    {
        pthread_mutex_lock(&mutex);
        // if not empty, wait
        if (count == 1)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        count = 1;
        put(i);
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


// consumer thread
void * consumer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if (count == 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        int tmp = get();
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        printf("Consumed val: %d\n", tmp);
    }

}


int main(void) {
    return 0;
}
