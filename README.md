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
```c
fgets(text, 100, stdin)
text[strlen(text) - 1] = '\0';
```
* We need to set to `\0` since fgets reads the \n char as well.

## strcpy vs strncpy
### strcpy
* copies the null character as well
* performs unrestricted copy and hence more prone to buffer overflow

### strncpy
* doesn't copy null terminator if count is reached before the entire string is copied
* limits the number of character copied

```c
strncpy(dest, src, strlen(src) + 1)
```
* This ensures that the null character is copied! or just add a null terminator at the end of the copied string.

## clean way to convert for to while loop
```c
int i = -1;
while (++i < size){
    printf("%d\n", ar[i])
}
```

## Array varible special behavior
```c
int ar[] = {1, 2, 3};
ar = ar + 1;
```

* This does not work and generates a compilation error
`Arrays in C and C++ are not modifiable lvalues; you cannot assign values to them as a whole.`

```c
int ar[] = {1, 2, 3};
int *ptr = ar;
ptr++;
```

* This works without any issues since `array variable decays to a ptr`.

## Dynamic memory reallocation
```c
mem1 = realloc(mem1, 64 * sizeof(int));
```

Its important to store the returned value in the array because realloc might sometimes free the existing memory and allocate the whole block again if its unable to find enough adjacent memory.

## Passing and updating structs
```c
void getMiddle(const Point* p1, const Point* p2, Point* mid){
    // logic
}

int main(void){
    Point p1, p2, mid;
    getMiddle(&p1, &p2, &mid);
}
```

* `const` used here indicates that we dont modify p1 and p2 memory locations
* The benefit of passing the address to mid is that we don't need to worry about stack or freeing heap memory issues.

## How to obtain the actual variable name while printing
```c
#define PRINT_VAR(X) \
    printf(#X " is %d at addr %p\n", X, &X)
// a is 10 at addr 0x16dc46ce8

PRINT_VAR(a);
// PRINT_VAR(10); 
```

`PRINT_VAR(10)` will have a compilation error!

```c
#define SWAP(A, B) A ^= B ^= A ^= B
```

> The above is a one line SWAP !!

## function pointers
```c
// <return type> (*identifier) (param1, param2, ...)
long long sum(int a, int b);
int main(void){
    long long (*fptr) (int, int);
    fptr = &sum;
    int s = fptr(10, 20);
}
```
## Integer type conversions
* When expanding variables, we see the `Sign Bit and padding the larger number accordingly`.

```c
short int x = -16384;
int y = 1073741824;
x = y;
// result: (x, y) = (0, 1073741824)
```

* We are trying to assign a bigger type to a smaller type
* C takes the LSBits of the bigger number and assigns it to smaller number
* `trimming` : Effectively does a modulo `y % 2^(bits in x)`

## Unions and Anonymous unions
```c
typedef union {
    unsigned int v4addr;
    char octets[4];
} Example;
```
* Here, on updating v4addr we can obtain individual octets.

```c
typedef struct {
    union 
    {
       float value;
       double valueExtended;
    };

    bool isExtended;
} CustomFloat;
```

## Writing to a file
```c
FILE *fp = fopen("file.dat", "w");
if (fp == NULL){
    return 1;
}

// write a buffer of data to file
size_t bytes_written = fwrite(buf, size_per_elem, nitems, fp);
if (bytes_written != nitems){
    return 2;
}
```

#### File read
```c
fp_in = fopen("point.dat", "r");
if (fp_in == NULL){
    return 1;
}

// read to  buffer
if (fgets(inp_buf, 256, fp_in) == NULL){
    fclose(fp_in);
    return 3;
}

// read from buffer to struct
sscanf(inp_buf, fmt, &p1.x, &p1.y);
fclose(fp_in);
```

> The above steps are called `Serialization `and `De-Serialization`

