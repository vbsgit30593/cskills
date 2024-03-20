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

## Reading & Writing to a file
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

> The above steps are called `Serialization` and `De-Serialization`

## Reading/Writing from/to binary file
```c
fp1 = fopen("point.bin", "wb");
if (fp1 == NULL ){
    return 1;
}

size_t elems_written = fwrite(&p1, sizeof(Point), 1, fp1);
if (elems_written == 0){
    return 2;
}
```

> Use a hex editor to check the file
* Note how this can help us in analysing memory!

#### Reading from binary file
```c
// Read from binary file
fp = fopen("point.bin", "rb");
size_t elems_read = fread(&point, sizeof(Point), 1, fp);
if (elems_read == 0){
    printf("Unsuccessful fread\n");
    return 3;
}
```

* fread reads to the memory location (Here struct).
* returns 0 in case of read failure.

### Improvements
```c
int bytes_wrote = fprintf(fp_out, fmt, p.x, p.y);
int elems_read = fscanf(fp_in, fmt, &p1.x, &p1.y);
```

```c
fp = fopen("point.dat", "w+");
```

* here, `w+` means -> open the file for reading and writing but if file already exists, overwrite it!
* trivially reading and writing wouldn't work since the cursor inside the file moves to next line after write
    * So, we need to fseek and move cursor back to start of file for reading.

```c
fseek(fp, 0, SEEK_SET);
```

### binary vs text files
* Binary files are arch dependent! (lack of portability)
    * Ex - a ptr is 4 bytes on 32 bit and 8 bytes on 64bit system
    * Also affected by endianness
* Text files need modification in format every time your change the structure
* Binary file read and write is fast while text file need to create buffer first
* Other options: `SEEK_SET`, `SEEK_CUR`, `SEEK_END`

## sizeof quirk
```c
int a = 10;
printf("sizeof a: %lu \n", sizeof(++a));
printf("a = %d\n", a);
```
* Here, a = 10 and not 11 since `sizeof` is a `compile time` operation.
* ++a substitutes to 10 before execution.

## const keyword
```c
int n = 10, m = 20;
const int* ptr = &n;
int* const ptr1 = &n;
// *ptr = 20; // not allowed
ptr = &m;
*ptr1 = 30;
// ptr1 = &m; // not allowed
```

#### ptr to const integer : `const int* ptr`
* Using this ptr, we can't modify the value stored at the pointer memory
* We can change what ptr points to

#### const ptr to integer: `int * const ptr`
* What this ptr points to cant change
* the memory being pointer can change

## gets issues and alternatives
```c
gets(buf)
```

* The problem is that gets allows us to read in unrestricted manner.
* So, we might end up copying way beyond the expected buffer size and corrupt the stack

#### use fgets
```c
fgets(buf, size, stdin)
```

* read from stdin or file (fd)
* reads only the size elements.

## renaming a file
```c
int res = rename("point1.dat", "point2.dat");
if (res == 0){
    printf("File renamed successfully\n");
}
else{
    char buf[256];
    printf("Failed to rename: %s\n", strerror(errno));
}
```
* Return 0 if successful!

## BITWISE ops to check flags
> Refer the code for `flagsBitwise.c`

### copy string using strdup
```c
char str[] = "hello"; 
char *new = strdup(str);
free(new);
```

* remember to free the allocated memory
* no limit on size of memory being copied

## converting strings to numbers
### Problems with atoi
* Conversions beyond max/min limits have undefined behavior
* No way to know when the conversion stops
* Cant convert from other bases!

```c
char str1[] = "1111111111111";
char str2[] = "101 name";
char str3[] = "0x10101";
int num = atoi(anystring);
```

### use strtok<> functions
```c
long int newnum = strtol(str4, NULL, 16);
newnum = strtol(str5, NULL, 0);
char *next;
newnum = strtol(str3, &next, 0);
```

* these family of function can help convert from any base to expected type
* we can specify a buf addr to obtain the location where we stop processing.
* the base can be automatically determined by using option 0 as 3rd arg

#### Sets errno if string is too large
```c
char str2[] = "1111111111111111111111111111111111";
newnum = strtol(str2, &next, 0);
printf("Original string: %s, Converted number: %ld, name: %s \n", str2, newnum, next);
printf("%d, %s\n", errno, strerror(errno));
```

#### Use it to check parsed numbers
```c
if (endptr == str){
    printf("Number could not be parsed\n");
    return;
}
if (errno == ERANGE) {
    printf("Number too large to parse!\n");
    return;
}
```

## Random numbers
### random in range
```c
int rand_interval(int low, int high) {
    int interval = high - low;
    return (rand() % interval) + low;
}
```
* Generates number betn low and high

```c
double rand_double(){
    // gets us numbers between 0 and 1
    return rand() / (double)RAND_MAX;
}

double rand_double_range(int low, int high){
    // gets us floating point numbers between low and high
    return (rand_double() * (high - low)) + low;
}
```

## Good practices while freeing the memory
* Make sure to set ptr to NULL after free! Do this always
  * This will ensure that subsequent free calls dont cause issues
  * free doc says that if ptr is a null pointer then do nothing

```c
free(arr);
arr = NULL;
```

## String formatting
* Use format macros to prevent rewriting complex formats

```c
#define FORMAT "({%d}, {%d})"
printf("Point is : "FORMAT, a, b);
```

* String literals directly get concatenated

## strspn vs strcspn vs strpbrk
### `strspn`
* string span
* returns the length of the initial segment of the string that matches a given set of chars
* Note that it starts its check from the first character and would return 0 if check fails

```c
char* str = "20 years old";
size_t len = strspn(str, "0123456789")
```
* The above example returns len = 2 which can be used to print the substring

### strpbrk
* string pointer to break
* Returns the pointers to the character in the string where the first match occurs

```c
char *str = "Hello I am 20 years old";
char *ptr = strpbrk(str, "0123456789")
```

* Here, ptr = &(character 2) in str.

> Combine `strpbrk` and `strspn` to obtain the actual numeric substring.

### strcspn
* complement of string span
* returns the number of len of initial subset such that it doesn't match charset

## trick to print string slice in just one printf in C
```c
printf("strcspn: Initial string data - %.*s\n", count_not_num, orig);
```
* Here, `%.*s` implies variable width string and width can be provided dynamically

## size_t format specifier
```c
printf("%zd\n", i);
```
`%zd` is the special format spec for size_t

## String concatenation
### `strcat` vs `strncat`
#### strcat
* No restriction on number of characters concatenated and can hence lead to stack corruption

#### strncat
```c
strncat(firstString, secondString, numCharsToCopy);
```

In itself, it doesn't prove to be helpful, but we can use it to write a secure code
```c
char str1[MAX] = "Hello";
char str2[] = "asdasdsadasdaasdasdasdasdad";
strncat(str1, str2, MAX - strlen(str1) - 1);
```
Now, the `maxchar(str1) = MAX`

> strcat_s is the safer option but not available always. It leads to a crash though.

## String replace
```c
char* string_replace(char* source, size_t sourceSize, char* substring, char* with) {
    // returns the substring end address of the updated string
    // or NULL if replacement failed */
    // handle case when replacement can cause mem overflow
    if (sourceSize < (strlen(source) + 1 + (strlen(with) - strlen(substring)))) {
        return NULL;
    }

    char* substring_start = strstr(source, substring);
    if (substring_start == NULL) {
        return NULL;
    }

    // move the memory to fit in the new replacement string
    memmove(
        substring_start + strlen(with),
        substring_start + strlen(substring),
        strlen(substring_start) - strlen(substring) + 1
    );

    // copy the replacement string
    memcpy(substring_start, with, strlen(with));

    // We used memcpy here instead of strcpy
    // since strcpy adds a \0 character at the end.
    return substring_start + strlen(with);
}
```

## Header file #ifndef and #pragma once
```c
#ifndef HEADER_H
#define HEADER_H
void headerFunc(int, int);
#endif
///// or
#pragma once
void headerFunc(int, int);
```

* here, `#ifndef` ensures that the functions are included only once even if the header file is included multiple times.

> `#pragma once` does the same thing but isn't a standard.

## Pointers to pointers
* It is generally used when we want to change what pointer variable points to.
* For example, just having a `char *` as a parameter would lead to a local copy and updating this will not refelect the changes in the caller
* Pointers can infinite levels of dereferencing as well.

```c
    unrealPointers(&&&&&origptr);  
```

* This is an error since `&origptr is an r-value and & operator needs an l-value`
* So, we need to store the result always to get address further.

```c
void unrealPointers(char***** ptr) {
    ****ptr = "After final update";
}

// unusual pointers
char** str1 = &origptr;
char*** str2 = &str1;
char**** str3 = &str2;
unrealPointers(&str3);
```

## exec family of functions
* execl, execv, execlp, execvp, execlpe, execvpe
* Note that on triggering exec, current process is replaced by the new program
So, the rest of the code does not get executed.
```c
/* EXECVP */
char* cmd[] = {
    "ping",
    "-c",
    "2",
    "google.com",
    NULL
};
```

## strerror_r issues to think about
* https://www.club.cc.cmu.edu/~cmccabe/blog_strerror.html



