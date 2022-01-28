#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long num;

    do
    {
        num = get_long("Number: ");
    } while (num < 0);
    int i = 0;

    while (i < 1)
    {
        double divided = num / 100.00;
        printf("%f\n",divided);

        i++;
    }
}