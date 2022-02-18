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
    unsigned int index = hash(word);
    printf("%u", index);
    for (node *n = table[index]; n != NULL; n = n->next)
    {
        char *str = malloc(sizeof(word) + 1);
        for (int j = 0; n->word[j] != '\0'; j++)
        {
            str[j] = n->word[j];
        }
        printf("%s\n", str);
        if (strcmp(word, str) == 0)
        {
            printf("yes");
            free(str);
            return true;
        }
        free(str);
    }
    printf("no");
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    unsigned int hash;
    char *str = malloc(sizeof(word + 1));
    for (int i = 0; i < 2; i++)
    {
        int num;
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            str[i] = tolower(word[i]);
        }
        else
        {
            str[i] = word[i];
        }
    }
    if (strlen(word) == 1 || !(str[1] >= 'a' && str[1] <= 'z'))
    {
        int dec = str[0] - 97;
        hash = dec;
    }
    else
    {
        int dec1 = str[0] - 97 + 1; // a=1, z=26
        int dec2 = str[1] - 97 + 1;
        hash = dec1 * 26 + dec2 - 1;
    }
    free(str);
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    node *tmp;
    char c;

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
        tmp = malloc(sizeof(node));
        if (i == 0)
        {
            tmp->word[0] = 'a';
        }
        else
        {
            tmp->word[0] = 'a' + i;
        }
        tmp->next = NULL;
        table[i] = tmp;
    }
    // from aa-zz
    for (int j = 26, m = 0; m < 26; m++)
    {
        for (int n = 0; n < 26; n++, j++)
        {

            tmp = malloc(sizeof(node));
            if (m == 0)
            {
                tmp->word[0] = 'a';
            }
            else
            {
                tmp->word[0] = 'a' + m;
            }
            if (n == 0)
            {
                tmp->word[1] = 'a';
            }
            else
            {
                tmp->word[1] = 'a' + n;
            }
            tmp->next = NULL;
            table[j] = tmp;
        }
    }
    free(tmp);

    int i = 0;
    int len = 0;
    tmp = malloc(sizeof(node));

    while (fread(&c, sizeof(char), 1, file))
    {
        if (c != '\n')
        {
            tmp->word[i] = c;
            i++;
            len++;
        }
        else
        {
            tmp->next = NULL;
            if (len == 1)
            {
                for (int m = 0; m < 26; m++)
                {
                    if (table[m]->word[0] == tmp->word[0])
                    {
                        for (node *n = table[m]; n != NULL; n = n->next)
                        {
                            if (n->next == NULL)
                            {
                                n->next = tmp;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else
            {
                for (int m = 26; m < N; m++)
                {
                    if (table[m]->word[0] == tmp->word[0] && table[m]->word[1] == tmp->word[1])
                    {
                        for (node *n = table[m]; n != NULL; n = n->next)
                        {
                            if (n->next == NULL)
                            {
                                n->next = tmp;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            // reinitialize the variable and allocate memory for temporary pointer
            i = 0;
            len = 0;
            tmp = malloc(sizeof(node));
        }
    }
    free(tmp);
    free(file);
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
    for (int i = N - 1; i >= 0; i--)
    {
        node *n = table[i]->next;
        free_memory(n);
        free(table[i]);
    }
    return true;
}
