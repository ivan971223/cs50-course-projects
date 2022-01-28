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
    }
    while (num < 0);

    int digit_num = get_digit_num(num);
    // printf("digit number is %i\n", digit_num);

    if (digit_num < 13 || digit_num > 16 || digit_num == 14)
    {
        printf("INVALID\n");
        return 0;
    }
    long temp = num;
    double first_two = temp;
    for (int i = 0; i < digit_num - 2; i++)
    {
        first_two /= 10;
    }
    first_two = (int)first_two;
    // printf("first_two: %f",first_two);
    long temp_num = num;
    for (int i = 0; i < digit_num; i++)
    {

        double divided_num = temp_num / 10.00;
        temp_num = divided_num;
        int digit = round((divided_num - temp_num) * 10);
        // printf("the last digit is:%i\n", digit);
        if (i % 2 == 1)
        {
            int digit_prod = digit * 2;
            if (digit_prod > 9)
            {
                checksum += 1;
                checksum += digit_prod - 10;
            }
            else
            {
                checksum += digit_prod;
            }
            // printf("add digit %i\n", digit);
        }
        else
        {
            checksum += digit;
        }
        // printf("float number is: %f\n", divided_num);
        // printf("integer number is: %li\n", temp_num);
        printf("checksum: %i\n", checksum);
    }
    double final_checksum = checksum / 10.0;
    int temp_checksum = (int)final_checksum;
    int sum_digit = (int)(final_checksum * 10 - temp_checksum * 10);
    printf("%f\n", final_checksum);
    printf("%i\n", temp_checksum);
    printf("%i\n", sum_digit);
    if (sum_digit == 0 && first_two >= 40 && first_two < 50)
    {
        printf("VISA\n");
    }
    else if (sum_digit == 0 && first_two >= 51 && first_two <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (sum_digit == 0 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_digit_num(long num)
{
    int digit_num = 0;
    if (num == 0)
    {
        return 0;
    }
    while (num > 0)
    {
        num = num / 10;
        digit_num++;
    }
    return digit_num;
}