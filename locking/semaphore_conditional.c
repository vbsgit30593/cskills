#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

sem_t s;
void *child(void *arg)
{
    printf("Child\n");
    sleep(2);
    sem_post(&s);
    printf("Child done\n");
    return NULL;
}

int main(void)
{
    printf("Parent starts\n");
    pthread_t t;
    sem_init(&s, 0, 0);
    pthread_create(&t, NULL, child, NULL);

    sem_wait(&s);
    printf("Parent done\n");
    return 0;
}
