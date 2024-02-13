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

## Use of const in function param list
```c
    // Function to print the members of a structure
    void printStruct(const void *structurePtr, size_t size) {
        // Cast the structure pointer to a char pointer
        const char *ptr = (const char *)structurePtr;
        
        // other code
    }
```

* Here `const void *structurePtr` ensures that the function will not modify the actual memory.
* It also ensures that the parameter can take both const and non-const arguments

## Returning strings from functions
```c
    const char* getString(){
        return "test";
    }

    int main(void){
        const char* ptr = getString();
    }
```

* We use const here to indicate that string "test" is present in a different read-only area of memory(not stack/heap).
* Refer `returnString.c` for solution!

## Comparing strings
```c
int ret = strcmp(str1, str2)
```

* ret = 0, str1 == str2
* ret = 1, for any char asc(str1) > asc(str2)
* ret = -1, for any char asc(str1) < asc(str2)

```c
int ret1 = strncmp(str1, str2, numCharstoCompare)
int ret2 = memcmp(str1, str2, numCharstoCompare)
```

> **Difference**: memcmp doesn't stop at null char and `memcmp takes void*`!

## How to prevent memory padding?
```c
#pragma pack(1)
```
* align at 1 byte!
* applies for the whole compilation unit

## Reading multiple sentences from console
### Approach - 1
```c
    printf("Enter input text 1!\n");
    scanf("%[^\n]s", text1);
    printf("Inputed text: %s\n", text1);

    getchar();
    printf("Enter input text 2!\n");
    scanf("%[^\n]s", text2);
    printf("Inputed text: %s\n", text2);
```

`[^\n]` implies that we would read till we encounter a `\n`
We use a `getchar()` in between to ensure that the `\n` character is consumed

### Approach - 2
