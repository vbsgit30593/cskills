#pragma once
#include <stdio.h>
#include <stdbool.h>

int naive_read_from_file(const char* filepath, char* words[]);
bool naive_search(char* words[], int size, const char *word);