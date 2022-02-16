// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 + 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for (int i = 0; i < 26; i++)
    {
        table[i]->word[0] = 'a' + i;
        table[i]->next = NULL;
    }
    for (int j = 26, m = 0; m < 26; j++, m++)
    {
        for (int n = 0; n < 26; n++, j++)
        {
            table[j]->word[0] = 'a' + m;
            table[j]->word[1] = 'a' + n;
            table[j]->next = NULL;
        }
    }
    // allocate memory for each string and node

    while (dictionary[i] != '\0')
    {
        node *tmp = malloc(sizeof(node));
        char *str[LENGTH + 1];
        int j = 0;
        while (dictionary[i] != "\n")
        {
            tmp->word[j] = dictionary[i];
            j++;
        }
        tmp->next = NULL;
        if (strlen(str) == 1)
        {
            for (int m = 0; m < 26; m++)
            {
                if (table[m] == str[0])
                {
                    for (node *n = table[m]; n->next != NULL; n = n->next)
                    {
                        if (n->next == NULL)
                        {
                            n = tmp;
                        }
                    }
                }
            }
        }
        else
        {
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
