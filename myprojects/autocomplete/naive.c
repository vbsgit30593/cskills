#include "fileops.h"
#include "naive.h"

int naive_read_from_file(const char* filepath, const char* words[])
{
    printf("%s: Reading words from file (%s)\n", __func__, filepath);
    return read_data(filepath, words);
}

bool naive_search(const char* words[], int size, const char *word)
{
    // convert word to lowercase
    char* token = strdup(word);
    token_to_lower(token);
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(token, words[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

bool is_present(const char* token, const char* words[], size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(words[i], token) == 0)
        {
            return true;
        }
    }
    return false;
}

int naive_prefix_search(const char* words[], int size, const char *word,
                        const char* matched[])
{
    // convert word to lowercase
    char* token = strdup(word);
    token_to_lower(token);
    int matchidx = 0;
    for (int i = 0; i < size; ++i)
    {
        if (strncmp(token, words[i], strlen(word)) == 0)
        {
            if (!is_present(words[i], matched, matchidx))
            {
                matched[matchidx++] = words[i];
            }
        }
    }

    free(token);
    // returns the number of matches
    return matchidx;
}