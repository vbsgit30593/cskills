#pragma once
#include <stdlib.h>

// incomplete type for TRIENODE
typedef struct TRIENODE TRIENODE;

TRIENODE *trie_createnode();
bool trie_insertword(TRIENODE **root, const char *word);
void trie_print(TRIENODE *root);
bool trie_search(TRIENODE *root, const char *word);
int trie_read_from_file(const char *filepath, TRIENODE **trieroot);
void trie_search_all(TRIENODE *root, const char *prefix);
size_t trie_mem_usage(TRIENODE* root);

