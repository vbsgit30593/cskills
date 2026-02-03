
// Script to try out qsort in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparator(const void *a, const void *b) {
    const char **word1 = (const char **)a;
    const char **word2 = (const char **)b;
    return (strcmp(*word1, *word2));
}

typedef void (*fptr)(int*, int*);

fptr funcs[10];
#define NUM_WORDS 3

int main(int argc, char *argv[]) {
    char *words[NUM_WORDS] = {"asdad", "wwww", "gsgsg"};

    qsort(words,  NUM_WORDS, sizeof(char *), comparator);
    for(int i = 0; i < NUM_WORDS; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");
    return 0;   
}
