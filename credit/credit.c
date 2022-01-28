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

    int digit_num = get_digit_num(num);
    printf("digit number is %i\n", digit_num);

    if (digit_num < 13 || digit_num > 16 || digit_num == 14)
    {
        printf("INVALID\n");
    }

    long temp_num = num;

    for (int i = 0; i < digit_num; i++)
    {

        double divided_num = temp_num / 10.00;
        temp_num = divided_num;
        int digit = round((divided_num - temp_num) * 10);
        printf("the last digit is:%i\n", digit);
        if (i % 2 == 1)
        {
            if(digit>9)
            {
                checksum += 1;
                checksum += digit-10;
            }
            else
            {
                checksum += digit*2;
            }
            printf("add digit %i\n",digit);
        }
        // printf("float number is: %f\n", divided_num);
        // printf("integer number is: %li\n", temp_num);
    }

    printf("checksum: %i\n", checksum);
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