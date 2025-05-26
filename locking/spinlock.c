typedef struct Spinlock {
    int lock;
} spinlock_t;

int TestAndSet(spinlock_t **lock, int cmpval) {
    return 1;
}

void init(spinlock_t *lock) {

}

void lock(spinlock_t *lock) {
    while(TestAndSet(&lock, 1) == 1);
}

int cas(int* ptr, int expected, int set) {
    int current = *ptr;
    if (expected == current) *ptr = set;

    return current;
}

void cas_lock(spinlock_t *lock) {
    // continue spinning if lock was already acquired else acquire
    while (cas(&lock->lock, 0, 1) == 1);
}

void unlock(spinlock_t *lock) {

}
/*
Case 1:
Lock is free
thread 1 comes and requests for lock
TestAndSet sets lock = 1 and returns 0 since lock was free
Condition fails and we dont spin wait

Case 2:
Lock is acquired
Thread 2 requests for lock
TestAndSet again sets lock = 1 and returns 1 as lock was already held
Thread 2 ends up spin waiting till Thread 1 frees the lock and sets it to 0
*/