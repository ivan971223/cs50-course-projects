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

    while (dictionary[i] != '\0')
    {
        // allocate memory for temporary node and store string and set next as a null pointer
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
                if (table[m]->word[0] == str[0])
                {
                    for (node *n = table[m]; n != NULL; n = n->next)
                    {
                        if (n->next == NULL)
                        {
                            n->next = tmp;
                        }
                    }
                }
            }
        }
        else
        {
            for (int m = 26; m < N; m++)
            {
                if (table[m]->word[0] == str[0] && table[m]->word[1] == str[1])
                {
                    for (node *n = table[m]; n != NULL; n = n->next)
                    {
                        if (n->next == NULL)
                        {
                            n->next = tmp;
                        }
                    }
                }
            }
        }
        free(tmp);
    }
    return true;
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
