#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"
/*
 * Prereqs for a Trie -
 * We need a look up table to quickly lookup a particular char
 * I think that this can be a table of 26 pointers to TRIENODEs
 *
 * We need a TRIENODE struct which should contain terminal info and a list of
 * children
 *
 * */

#define NUMCHARS 26
typedef struct TRIENODE {
  struct TRIENODE *children[NUMCHARS];
  bool terminal;
} TRIENODE;

TRIENODE *trie_createnode() {
  TRIENODE *newnode = calloc(1, sizeof *newnode);
  // init all child nodes
  for (int i = 0; i < NUMCHARS; ++i) {
    newnode->children[i] = NULL;
  }
  newnode->terminal = false;

  return newnode;
}

bool trie_insertword(TRIENODE** root, const char* word) {
  // if node is NULL - create node
  if (*root == NULL)
  {
    *root = trie_createnode();
  }

  TRIENODE* temproot = *root;
  int len = strlen(word);

  for (int i = 0; i < len; ++i)
  {
    int map_idx = (unsigned int)word[i] - 97;
    if (temproot->children[map_idx] == NULL)
    {
      temproot->children[map_idx] = trie_createnode();
    }

    temproot = temproot->children[map_idx];
  }
  if (temproot->terminal == true) return false; // word already present
  temproot->terminal = true;
  return true;
}

static void trie_print_helper(TRIENODE* node, char* prefix, size_t length)
{
  if (node == NULL)
  {
    return;
  }
  // 1 for extra char and 1 for NULL char
  char newprefix[length + 2];
  memcpy(newprefix, prefix, length);
  newprefix[length + 1] = 0;

  if (node->terminal)
  {
    printf("%s\t", prefix);
  }

  // continue checking children
  for (int i = 0; i < NUMCHARS; ++i)
  {
    if (node->children[i] == NULL)
    {
      continue;
    }
    newprefix[length] = (char)(i + 97);
    trie_print_helper(node->children[i], newprefix, length + 1);
  }
}

void trie_print(TRIENODE* root) {
  if (root == NULL) 
  {
    printf("TRIE is empty\n");
    return;
  }

  printf("Current TRIE entries : ");
  trie_print_helper(root, NULL, 0);
  printf("\n");
}

bool trie_search(TRIENODE* root, const char* word) {
  if (root == NULL)
  {
    printf("TRIE is empty!! Go add something first my friend!\n");
    exit(0);
  }

  int len = strlen(word);
  for (int i = 0; i < len; ++i)
  {
    int mapidx = ( int )( word[i] ) - 97;
    if (root->children[mapidx] == NULL)
    {
      return false;
    }
    root = root->children[mapidx];
  }
  return root->terminal;
}

/* int main(void) */
/* { */
/*   TRIENODE* root = NULL; */
/*   trie_insertword(&root, "cat"); */
/*   trie_insertword(&root, "car"); */
/*   trie_insertword(&root, "bat"); */
/*   trie_insertword(&root, "vaibhav"); */
/*   trie_insertword(&root, "sing"); */
/**/
/*   trie_print(root); */
/**/
/*   printf("is `vaibhav` present: %d\n", trie_search(root, "vaibhav")); */
/*   printf("is `vishalv` present: %d\n", trie_search(root, "vishalv")); */
/*   printf("is `car` present: %d\n", trie_search(root, "car")); */
/*   printf("is `bar` present: %d\n", trie_search(root, "bar")); */
/**/
/*   return 0; */
/* } */
