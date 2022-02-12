#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    int BLOCK_SIZE = 512;
    BYTE buffer[];

    if (argc != 2)
    {
        printf("take exact one argument only");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("The file is not readable.");
        return 1;
    }

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {

    }
}