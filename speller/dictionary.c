// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
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
    // return toupper(word[0]) - 'A';
    int hash = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash += (int)word[i];
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // check dictionary is empty or not
    if (dictionary == NULL)
    {
        return false;
    }

    // assign character key to the hash table array
    // from a-z
    for (int i = 0; i < 26; i++)
    {
        table[i]->word[0] = 'a' + i;
        table[i]->next = NULL;
    }
    // from aa-zz
    for (int j = 26, m = 0; m < 26; j++, m++)
    {
        for (int n = 0; n < 26; n++, j++)
        {
            table[j]->word[0] = 'a' + m;
            table[j]->word[1] = 'a' + n;
            table[j]->next = NULL;
        }
    }

    // loop through each char
    while (dictionary[i] != '\0') // check condition if char not equal to null
    {
        // allocate memory for temporary node and store string and set next as a null pointer
        node *tmp = malloc(sizeof(node));
        char *str = malloc(LENGTH + 1);
        int j = 0;

        // assign word to tmp node
        while (dictionary[i] != "\n")
        {
            str[j] = dictionary[i];
            tmp->word[j] = dictionary[i];
            j++;
        }
        // assign next to null
        tmp->next = NULL;

        // check string len
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
        free(str);
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
