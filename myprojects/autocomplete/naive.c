#include "naive.h"
#include "fileops.h"

int naive_read_from_file(const char *filepath, const char *words[]) {
  printf("%s: Reading words from file (%s)\n", __func__, filepath);
  return read_data(filepath, words, ARRAY);
}

bool naive_search(const char *words[], int size, const char *word) {
  // convert word to lowercase
  char *token = strdup(word);
  token_to_lower(token);
  for (int i = 0; i < size; ++i) {
    if (strcmp(token, words[i]) == 0) {
      return true;
    }
  }
  return false;
}

bool is_present(const char *token, const char *words[], size_t size) {
  for (int i = 0; i < size; ++i) {
    if (strcmp(words[i], token) == 0) {
      return true;
    }
  }
  return false;
}

int naive_prefix_search(const char *words[], int size, const char *word,
                        const char *matched[]) {
  // convert word to lowercase
  char *token = strdup(word);
  token_to_lower(token);
  int matchidx = 0;
  for (int i = 0; i < size; ++i) {
    if (strncmp(token, words[i], strlen(word)) == 0) {
      if (!is_present(words[i], matched, matchidx)) {
        matched[matchidx++] = words[i];
      }
    }
  }
  free(token);
  // returns the number of matches
  return matchidx;
}

size_t naive_mem_in_use(const char **tbl, size_t static_count,
                        size_t actual_token_count) {
  // total = sum of pointers + sizeof each string
  size_t total = sizeof(char *) * static_count;
  for (int i = 0; i < actual_token_count; ++i) {
    total += strlen(tbl[i]);
  }
  return total;
}

void naive_free(const char **words, size_t token_count) {
  for (int i = 0; i < token_count; ++i) {
    free((void *)words[i]);
  }
}
