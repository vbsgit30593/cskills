// incomplete type for TRIENODE
typedef struct TRIENODE TRIENODE;

TRIENODE* trie_createnode();
bool trie_insertword(TRIENODE** root, const char* word);
void trie_print(TRIENODE* root);
bool trie_search(TRIENODE* root, const char* word);
