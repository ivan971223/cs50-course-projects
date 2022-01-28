#include <cs50.h>
#include <stdio.h>

void add_space(int n);
void add_brick(int n);

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    for (int i = 1; i <= h; i++)
    {

        add_space(h - i);
        add_brick(i);
        printf(" ");
        printf(" ");
        add_brick(i);
        printf("\n");

    }
}

void add_space(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

void add_brick(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}