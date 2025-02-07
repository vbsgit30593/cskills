#include "main.h"
#include "naive.h"
#include "string.h"
#include "trie.h"
#include <stdio.h>
#include <sys/time.h>

#define ROOT_DATA_PATH "data"
#define MAX_TOKEN_COUNT 1000000

void trieops(const char *filepath, const char *searchword) {
  TRIENODE *root = NULL;
  int token_count = trie_read_from_file(filepath, &root);
  // get trie memory size
  printf("TRIE memory usage: %fMB\n", trie_mem_usage(root)/1e+6);
  struct timeval start, end;
  gettimeofday(&start, NULL);

  /* if (trie_search(root, searchword)) { */
  /*   printf("Word %s found in TRIE\n", searchword); */
  /* } else { */
  /*   printf("Word %s not found in TRIE\n", searchword); */
  /* } */

  trie_search_all(root, searchword);

  gettimeofday(&end, NULL);
  printf("\nTotal trie search time: %fs\n",
         ((end.tv_usec - start.tv_usec) / 1e+6));

  // TODO: free memory used by TRIE
}

void naive(const char *filepath, const char *searchword) {
  const char *words[MAX_TOKEN_COUNT];
  int token_count = naive_read_from_file(filepath, words);
  // Note: this can be improved by chunked memory allocation but in our case
  // the current approach is fine if we tokenize the whole file as that's close
  // to a million tokens already.
  // With that knowledge, it would be more performant to simply have a huge
  // static memory
  printf("Naive token memory size: %fMB\n",
         naive_mem_in_use(words, MAX_TOKEN_COUNT, token_count) / 1e+6);

  // Start with a huge static array
  // Make it dynamic later and realloc as per need
  struct timeval start, end;
  gettimeofday(&start, NULL);
  /* if (naive_search(words, token_count, searchword)) { */
  /*   printf("WORD FOUND\n"); */
  /* } else { */
  /*   printf("WORD NOT FOUND\n"); */
  /* } */

  // NAIVE PREFIX SEARCH
  const char *matches[1000];
  int num_matches =
      naive_prefix_search(words, token_count, searchword, matches);
  if (num_matches) {
    printf("## Here are your %d suggestions ##\n", num_matches);
    for (int i = 0; i < num_matches; ++i) {
      printf("%s\t", matches[i]);
    }
    printf("\n");
  } else {
    printf("'%s' not found in dictionary\n", searchword);
  }
  gettimeofday(&end, NULL);
  printf("Total naive search time: %fs\n",
         ((end.tv_usec - start.tv_usec) / 1e+6));

  naive_free(words, token_count);
}

int main(int argc, char *argv[]) {
  char filepath[100];
  snprintf(filepath, 100, "%s/%s", ROOT_DATA_PATH, argv[1]);
  const char *searchword = argv[2];
  naive(filepath, searchword);
  printf("###########\n");
  trieops(filepath, searchword);
  return 0;
}
