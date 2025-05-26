#include <sys/_pthread/_pthread_cond_t.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct vsem {
    int value;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} vsem_t;


void vsem_init(vsem_t *sem, int val)
{
    sem->value = val;
    pthread_mutex_init(&sem->lock, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

void vsem_wait(vsem_t *sem)
{
    pthread_mutex_lock(&sem->lock);
    if (sem->value <= 0) pthread_cond_wait(&sem->cond, &sem->lock);
    sem->value--;
    pthread_mutex_unlock(&sem->lock);
}

void vsem_post(vsem_t *sem)
{
    pthread_mutex_lock(&sem->lock);
    sem->value++;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->lock);
}

void * child(void *arg)
{
    int id = (int)arg;

}
int main(void)
{
    // create threads and do something
    pthread_t th[5];
    for(int i = 0; i < 5; i++)
    {
        pthread_create(&th[i], NULL, child, (void *)i);
    }
    for(int i = 0; i < 5; i++)
    {
        pthread_join(th[i], NULL);
    }
}
