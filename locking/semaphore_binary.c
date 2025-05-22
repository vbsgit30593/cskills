#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long sum = 0;
sem_t s;

void *thread(void *arg) {
  int loops = *(int *)arg;
  sem_wait(&s);

  for (int i = 0; i < loops; i++) {
    sum += i;
  }

  sem_post(&s);
  return NULL;
}

int main(void) {
  sem_init(&s, 0, 1);
  pthread_t t[2];
  int loops = 1000000;
  for (int i = 0; i < 2; i++) {
    if (pthread_create(&t[i], NULL, thread, &loops) != 0) {
      perror("Could not create thread!");
      exit(0);
    }
  }

  for (int i = 0; i < 2; i++) {
    if (pthread_join(t[i], NULL) != 0) {
      perror("Could not join threads!");
      exit(0);
    }
  }
  sem_destroy(&s);
  printf("Final sum: %lu\n", sum);
  return 0;
}
