#include <stdio.h>
#include "naive.h"
#include "main.h"
#include "string.h"
#include <sys/time.h>

#define ROOT_DATA_PATH "data"

// Start with a huge static array
// Make it dynamic later and realloc as per need
const char* words[1000000];

void naive(int token_count, const char* searchword)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    // if (naive_search(words, token_count, searchword))
    // {
    //     printf("WORD FOUND\n");
    // }
    // else
    // {
    //     printf("WORD NOT FOUND\n");
    // }

    // NAIVE PREFIX SEARCH
    const char* matches[1000];
    int num_matches = naive_prefix_search(words, token_count, searchword, matches);
    if (num_matches)
    {
        printf("## Here are your %d suggestions ##\n", num_matches);
        for (int i = 0; i < num_matches; ++i)
        {
            printf("%s\t", matches[i]);
        }
        printf("\n");
    }
    else
    {
        printf("'%s' not found in dictionary\n", searchword);
    }
    gettimeofday(&end, NULL);
    printf("Total naive search time: %fs\n", ((end.tv_usec - start.tv_usec) / 1e+6));
}

int main(int argc, char *argv[])
{
    char filepath[100];
    snprintf(filepath, 100, "%s/%s", ROOT_DATA_PATH, argv[1]);
    const char* searchword = argv[2];
    int token_count = naive_read_from_file(filepath, words);
    naive(token_count, searchword);
    return 0;
}