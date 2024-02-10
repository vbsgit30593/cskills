## How to compare arrays
```c
memcmp(array1_ptr, array2_ptr, amount of mem to compare)
```
Returns `0` if the two arrays are the same!
Note that the first two args are void* here
Library: `string.h`

## How to copy arrays
```c
memcpy(dest, src, total mem to copy)
```
Copies from `src` to `dest` for the requested amt of memory.

## How to set a memory/array with some values
```c
memset(dest, value, total memory to set)
```

Sets `value` to each byte of referenced memory

## How to search a byte in the array
```c
if (NULL != memchr(array, byteval, nElems * sizeof(type))) {
    printf("Found the byte\n");
} else {
    printf("Byte not found\n");
}
```

Return: NULL if not found and ptr to matched memory if found!