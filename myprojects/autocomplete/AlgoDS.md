Following are some skills and algorithms encountered as part of this work.

## Reading words from sentences in a file
Approach 1: Read complete file data and then tokenize
```
S: O(F + W)
F: size of file
W: Total number of words
```

Approach 2: Read line by line
```
S: O(L + W_l)
W_l: Words in longest sentence
L: Length of line
```

## Getting length of file in C

```c
    fseek(fptr, 0, SEEK_END);
    size_t size = ftell(fptr);
    rewind(fptr);
```

## String tokenization in C
```c
    char *token, *saveptr;
    char *delim = " ";
    token = strtok_r(buf, delim, &saveptr);
    int i = 0;
    while (token != NULL)
    {
        printf("Token: %s\n", token);
        token = strtok_r(NULL, delim, &saveptr);
    }
```

## Match prefixes rather than full words
```c
    if (strncmp(word, words[i], strlen(word)) == 0)
    {
        // matched word
    }
```
* This matches the first n characters only.

## Passing char** to const char**
* https://stackoverflow.com/questions/14562845/why-does-passing-char-as-const-char-generate-a-warning

## remember to use strdup while tokenizing
* Dont directly use the tokens from the buffer. The obtained token just points to the next token address
* We should ideally do a strdup of the token
* later we should free all the memory
