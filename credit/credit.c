#include <stdio.h>
#include <cs50.h>
#include <math.h>

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

        double divided_num = num / 10.00;
        long temp_num = divided_num;
        int digit = (divided_num - temp_num)*10;

        printf("%f\n",divided_num);
        printf("%li\n",temp_num);
        printf("%i\n",digit);
        i++;
    }
}

int get_digit_num(num)
{
    int digit_num;
    while(num>0)
    {

    }

}