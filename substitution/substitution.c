#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int checkkey(string key);

int main(int argc, string argv[])
{
    //printf("%s\n", argv[1]);

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];

    int num = checkkey(key);
    if (num == 1)
    {
        return 1;
    }
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        int index = 0;
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            index = (int)text[i] - 97;
            printf("%c", tolower(key[index]));
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            index = (int)text[i] - 65;
            printf("%c", toupper(key[index]));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}

int checkkey(string key)

{
    int key_len = strlen(key);
    if (key_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < key_len; i++)
    {
        if ((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z'))
        {
            for (int j = i + 1; j < key_len; j++)
            {
                if (key[i] == key[j])
                {
                    printf("Invalid key\n");
                    return 1;
                }
            }
        }
        else
        {
            printf("Invalid key\n");
            return 1;
        }
    }

    return 0;
}