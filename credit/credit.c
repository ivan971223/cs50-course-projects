#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_digit_num(long num);

int main(void)
{
    long num;
    int checksum = 0;

    do
    {
        num = get_long("Number: ");
    } while (num < 0);

    int digit = get_digit_num(num);
    if (digit < 13 || digit > 16 || digit == 14)
    {
        printf("INVALID\n");
    }

    for (int i = 0; i < digit; i++)
    {
        if (i % 2 == 1)
        {
            double divided_num = num / 10.00;
            long temp_num = divided_num;
            int digit = (divided_num - temp_num) * 10;
            printf("%i\n", digit);
            checksum += digit;
        }
        // printf("%f\n", divided_num);
        // printf("%li\n", temp_num);

    }
}

int get_digit_num(long num)
{
    int digit_num = 0;
    if (num == 0)
    {
        printf("INVALID");
    }
    while (num > 0)
    {
        num = num / 10;
        digit_num++;
    }
    return digit_num;
}