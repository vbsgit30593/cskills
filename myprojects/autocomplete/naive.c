#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>

#include "naive.h"

static inline
void open_file(FILE **fptr, const char* filepath)
{
    *fptr = fopen(filepath, "r");
    if (*fptr == NULL)
    {
        perror("Unable to open file");
        system("ls data/");
        exit(0);
    }
}

static inline
size_t get_file_size(FILE* fptr)
{
    fseek(fptr, 0, SEEK_END);
    size_t size = ftell(fptr);
    rewind(fptr);

    return size;
}

static inline
bool valid_token_to_lower(char *oldtoken, char *newtoken)
{
    for (int i = 0; i < strlen(oldtoken); ++i)
    {
        if (isalpha(oldtoken[i]) == 0)
        {
            return false;
        }
        newtoken[i] = tolower(oldtoken[i]);
    }
    return true;
}

static inline
bool token_to_lower(char *token)
{
    int lidx = 0;
    for (int i = 0; i < strlen(token); ++i)
    {
        if (isalpha(token[i]) > 0)
        {
            token[lidx++] = tolower(token[i]);
        }
    }
    token[lidx] = '\0';
    return (lidx > 0);
}

static inline
int read_whole_file_and_tokenize(FILE* fptr, char *words[])
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    size_t size = get_file_size(fptr);
    printf("Size of file: %zu \n", size);

    // reading data to a buf
    char *buf = malloc(size * sizeof(char));
    fread(buf, size, 1, fptr);

    // printf("data read: %s\n", buf);
    char *token, *saveptr;
    char *delim = " ";
    token = strtok_r(buf, delim, &saveptr);
    int i = 0;
    int total_tokens = 0;
    while (token != NULL)
    {
        if (token_to_lower(token))
        {
            // printf("Updated token: %s\n", token);
            words[i++] = token;
        }
        token = strtok_r(NULL, delim, &saveptr);
        total_tokens++;
    }

    free(buf);

    printf("Total tokens: %d, cleaned tokens: %d\n", total_tokens, i);

    gettimeofday(&end, NULL);
    printf("Total file read + tokenization time: %fs\n", (end.tv_usec - start.tv_usec) / 1e+6);
    return i;
}

int read_data(const char* filepath, char* words[])
{
    FILE *fptr;

    open_file(&fptr, filepath);
    int token_count = read_whole_file_and_tokenize(fptr, words);

    fclose(fptr);
    return token_count;
}

int naive_read_from_file(const char* filepath, char* words[])
{
    printf("%s: Reading words from file (%s)\n", __func__, filepath);
    return read_data(filepath, words);
}

bool naive_search(char* words[], int size, const char *word)
{
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(word, words[i]) == 0)
        {
            return true;
        }
    }
    return false;
}