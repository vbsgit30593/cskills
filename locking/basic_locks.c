typedef struct lock {
    int lock;
} lock_t;

void init(lock_t *mutex)
{
    mutex->lock = 0;
}

void lock(lock_t *mutex)
{
    while (mutex->lock == 1);
    mutex->lock = 1;
}

void unlock(lock_t *mutex)
{
    mutex->lock = 0;
}

/*
Race condition:-
Thread 1 calls lock()
    while(...)
    Interrupt: switch to thread 2
Thread 2 calls lock()
    while(...)
Thread 2 acquires lock()
    mutex->lock = 1
    Interrupt: switch to thread 1
Thread 1 also acquires lock

Both threads enter the critical section and we failed the first principle - Mutual exclusion
*/