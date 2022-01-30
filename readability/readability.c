#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);

int main(void)
{
    string text = get_string("Text:");
    printf("Text: %s\n", text);
    printf("%i letters\n", count_letters(text));
    printf("%i words\n", count_words(text));
}

int count_letters(string text)
{
    int len = strlen(text);
    int letter_count = 0;
    for (int i = 0; i < len; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letter_count += 1;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int len = strlen(text);
    int word_count = 0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            word_count += 1;
        }
    }
    return word_count;
}