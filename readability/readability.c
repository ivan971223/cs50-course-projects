#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text:");
    //printf("Text: %s\n", text);
    //printf("%i letters\n", count_letters(text));
    //printf("%i words\n", count_words(text));
    //printf("%i sentences\n", count_sentences(text));

    int num_letters = count_letters(text);
    int num_words = count_words(text);
    int num_sentences = count_sentences(text);
    float L = (float)num_letters / (float)num_words * 100.00;
    float S = (float)num_sentences / (float)num_words * 100.00;
    //printf("L:%f\n", L);
    //printf("S:%f\n", S);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    //printf("%i\n", index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
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
    int word_count = 1;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            word_count += 1;
        }
    }
    return word_count;
}

int count_sentences(string text)
{
    int len = strlen(text);
    int sentence_count = 0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count += 1;
        }
    }
    return sentence_count;
}