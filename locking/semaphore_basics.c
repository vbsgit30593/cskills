#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t s;

int main(void)
{
    sem_init(&s, 0, 1);
    return 0;
}
