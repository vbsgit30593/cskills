int load_linked(int *ptr) { 
    return *ptr;
}

int store_conditional(int* ptr, int val) {
    int original = load_linked(ptr);
    if (*ptr == original)
    { 
        *ptr = val;
        return 1;
    }
    else {
        return 0;
    }
}

typedef struct Lock {
    int lock;
} lock_t;

void lock(lock_t *lock) {
    while(1)
    { 
        while(load_linked(&lock->lock) == 1);
        if(store_conditional(&lock->lock, 1) == 1) return;
    }
}
