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

Return: `NULL` if not found and `ptr to matched memory` if found!

## How to print bytes in hex
```c
printf("%02x ", element);
```

Here, `%02x` => Use atleast two character to represent number and pad rest with 0

## How to increase entropy in randomness in C
* Normally, if we use `rand()`, it generates the same random number in each run
* We can add a seed by calling `srand(seedval)`. But this will still return same val on each run.
* To increase entropy, we can use time - `srand(time(NULL))`

## How to tokenize a string?
```c
    char *word = strtok(sentence, " ");
    while (NULL != word){
        printf("%s\n", word);
        word = strtok(NULL, " ");
    }
```

* Here, in the next call we pass `NULL` to `strtok` as that hints it to continue tokenizing the string.
* Returns `NULL` when there are no more tokens left.
> **Warning:** strtok modifies the original string! It adds `\0` in the place of the delimiter.