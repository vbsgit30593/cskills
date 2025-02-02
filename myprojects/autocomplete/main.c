#include <stdio.h>
#include "naive.h"
#include "main.h"
#include "string.h"
#include <sys/time.h>

#define ROOT_DATA_PATH "data"

// Start with a huge static array
// Make it dynamic later and realloc as per need
char* words[1000000];

int main(int argc, char *argv[])
{
    struct timeval start, end;
    char filepath[100];
    snprintf(filepath, 100, "%s/%s", ROOT_DATA_PATH, argv[1]);
    int token_count = naive_read_from_file(filepath, words);
    gettimeofday(&start, NULL);
    if (naive_search(words, token_count, "buffalo"))
    {
        printf("WORD FOUND\n");
    }
    else
    {
        printf("WORD NOT FOUND\n");
    }
    gettimeofday(&end, NULL);
    printf("Total search time: %fs\n", ((end.tv_usec - start.tv_usec) / 1e+6));
    return 0;
}