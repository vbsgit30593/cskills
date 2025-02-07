#pragma once
#include "trie.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef enum {
  ARRAY = 1,
  TRIE = 2,
} StorageType;

static inline void open_file(FILE **fptr, const char *filepath) {
  *fptr = fopen(filepath, "r");
  if (*fptr == NULL) {
    perror("Unable to open file");
    system("ls data/");
    exit(0);
  }
}

static inline size_t get_file_size(FILE *fptr) {
  fseek(fptr, 0, SEEK_END);
  size_t size = ftell(fptr);
  rewind(fptr);

  return size;
}

static inline bool valid_token_to_lower(const char *oldtoken, char *newtoken) {
  for (int i = 0; i < strlen(oldtoken); ++i) {
    if (isalpha(oldtoken[i]) == 0) {
      return false;
    }
    newtoken[i] = tolower(oldtoken[i]);
  }
  return true;
}

static inline bool token_to_lower(char *token) {
  int lidx = 0;
  for (int i = 0; i < strlen(token); ++i) {
    if (isalpha(token[i]) > 0) {
      token[lidx++] = tolower(token[i]);
    }
  }
  token[lidx] = '\0';
  return (lidx > 0);
}

static inline int read_whole_file_and_tokenize(FILE *fptr,
                                               const char *words[]) {
  struct timeval start, end;
  gettimeofday(&start, NULL);

  size_t size = get_file_size(fptr);
  printf("Size of file: %zu \n", size);

  // reading data to a buf
  char *buf = (char *)malloc(size * sizeof *buf);
  fread(buf, size, 1, fptr);

  // printf("data read: %s\n", buf);
  char *token, *saveptr;
  const char *delim = " ";
  token = strtok_r(buf, delim, &saveptr);
  int i = 0;
  int total_tokens = 0;
  while (token != NULL) {
    if (token_to_lower(token)) {
      // printf("Updated token: %s\n", token);
      words[i++] = strdup(token);
      // words[i++] = token;
    }
    token = strtok_r(NULL, delim, &saveptr);
    total_tokens++;
  }

  free(buf);

  printf("Total tokens: %d, cleaned tokens: %d\n", total_tokens, i);

  gettimeofday(&end, NULL);
  printf("Total file read + tokenization time: %fs\n",
         (end.tv_usec - start.tv_usec) / 1e+6);
  return i;
}

static inline int read_whole_file_and_build_trie(FILE *fptr,
                                                 TRIENODE **trieroot) {
  struct timeval start, end;
  gettimeofday(&start, NULL);
  size_t bufsize = get_file_size(fptr);
  char *buf = (char *)calloc(1, bufsize);
  size_t num_read = fread(buf, bufsize, 1, fptr);

  int total_tokens = 0, cleaned_tokens = 0;
  char *token, *saveptr;
  const char *delim = " ";
  token = strtok_r(buf, delim, &saveptr);
  while (token != NULL) {
    char *temptoken = strdup(token);
    // insert into TRIE
    if (token_to_lower(temptoken)) {
      trie_insertword(trieroot, temptoken);
      cleaned_tokens++;
    }
    token = strtok_r(NULL, delim, &saveptr);
    free(temptoken);
    total_tokens++;
  }
  gettimeofday(&end, NULL);
  printf("Total tokens: %d, cleaned tokens: %d\n", total_tokens,
         cleaned_tokens);
  printf("Time spent in reading a file and creating trie: %f\n",
         (end.tv_usec - start.tv_usec) / 1e+6);
  free(buf);

  return cleaned_tokens;
}

static inline int read_data(const char *filepath, const char *words[],
                            TRIENODE **trieroot, StorageType type) {
  FILE *fptr;
  int token_count = 0;

  open_file(&fptr, filepath);

  switch (type) {
  case ARRAY:
    token_count = read_whole_file_and_tokenize(fptr, words);
    break;

  case TRIE:
    token_count = read_whole_file_and_build_trie(fptr, trieroot);
    break;

  default:
    printf("INVALID storage type\n");
    exit(0);
  }

  fclose(fptr);

  return token_count;
}
