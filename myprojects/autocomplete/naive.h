#pragma once
#include <stdio.h>
#include <stdbool.h>

int naive_read_from_file(const char* filepath, const char* words[]);
bool naive_search(const char* words[], int size, const char *word);
int naive_prefix_search(const char* words[], int size, const char *word, const char* matched[]);
size_t naive_mem_in_use(const char **tbl, size_t static_count, size_t actual_token_count);