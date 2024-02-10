## How to compare arrays
```c
memcmp(array1_ptr, array2_ptr, amount of mem to compare)
```
Returns 0 if the two arrays are the same!
Note that the first two args are void* here
Library: string.h

## How to copy arrays
```c
memcpy(dest, src, total mem to copy)
```
Copies from src to dest for the requested amt of memory.

## How to set a memory/array with some values
```c
memset(dest, value, total memory to set)
```

Set value to each byte of referenced memory