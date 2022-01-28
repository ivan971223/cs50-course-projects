#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    for(int i=0; i<h; i++)
    {
        for(int x=1; x<h; y++)
        {
            add_space(h-x)
            add_brick(i)
        }
        printf(" ");
        printf(" ");
        for(int j=0; j<h; j++)
        {

        }
    }
}

void add_space(int n)
{
    for(int i=0; i<n; i++)
    {
        printf(" ")
    }
}

void add_brick(int n)
{
    for(int i=0; i<n; i++)
    {
        printf("#")
    }
}