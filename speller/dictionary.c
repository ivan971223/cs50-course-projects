// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    unsigned int hash;
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

    int len = strlen(word);
    char *str = malloc(len + 1);
    for (int i = 0; i < len; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            str[i] = tolower(word[i]);
        }
        else
        {
            str[i] = word[i];
        }
    }

    int word_hash = hash(word);

    if (len == 1)
    {

        for (int k = 0; k < 26; k++)
        {
            if (table[k]->word[0] == str[0])
            {
                for (node *n = table[k]; n != NULL; n = n->next)
                {
                    if ((n->hash) == word_hash)
                    {
                        return true;
                    }
                }
            }
        }
    }
    else
    {
        for (int k = 26; k < N; k++)
        {
            if (table[k]->word[0] == str[0] && table[k]->word[1] == str[1])
            {
                for (node *n = table[k]; n != NULL; n = n->next)
                {
                    if ((n->hash) == word_hash)
                    {
                        return true;
                    }
                }
            }
        }
    }
    free(str);
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
        int num;
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            num = tolower(word[i]);
        }
        else
        {
            num = word[i];
        }

        hash += num * (num - i);
    }
    return hash;
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
    for (int i = 0; i < N ; i++)
    {
        node *n = table[i];
        printf("%c",n->word[0]);
    }

    // int i = 0;
    // int j = 0;
    // node *tmp = malloc(sizeof(node));
    // char *str = malloc(LENGTH + 1);

    // loop through each char
    // while (dictionary[i] != '\0') // check condition if char not equal to null
    // {
    //     // allocate memory for temporary node and store string and set next as a null pointer

    //     // assign word to tmp node
    //     if (dictionary[i] == '\n')
    //     {

    //         unsigned int hash_num = hash(str);
    //         tmp->hash = hash_num;
    //         // assign next to null
    //         tmp->next = NULL;

    //         // check string len
    //         if (strlen(str) == 1)
    //         {
    //             for (int m = 0; m < 26; m++)
    //             {
    //                 if (table[m]->word[0] == str[0])
    //                 {
    //                     for (node *n = table[m]; n != NULL; n = n->next)
    //                     {
    //                         if (n->next == NULL)
    //                         {
    //                             n->next = tmp;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //         else
    //         {
    //             for (int m = 26; m < N; m++)
    //             {
    //                 if (table[m]->word[0] == str[0] && table[m]->word[1] == str[1])
    //                 {
    //                     for (node *n = table[m]; n != NULL; n = n->next)
    //                     {
    //                         if (n->next == NULL)
    //                         {
    //                             n->next = tmp;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //         free(tmp);
    //         free(str);
    //         tmp = malloc(sizeof(node));
    //         str = malloc(LENGTH + 1);
    //         j = 0;
    //     }
    //     else
    //     {
    //         str[j] = dictionary[i];
    //         tmp->word[j] = dictionary[i];
    //         j++;
    //     }
    //     i++;
    // }
    // free(tmp);
    // free(str);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int size = 0;
    if (table[0] == NULL)
    {
        return 0;
    }

    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n->next != NULL)
        {
            size++;
            n = n->next;
        }
    }
    return size;
}

void free_memory(node *n)
{
    if (n == NULL)
    {
        return;
    }
    free_memory(n->next);
    free(n);
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        free_memory(n);
    }
    free(table);
    return false;
}
