#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int BLOCK_SIZE = 512;
    int i = 0;
    int n = 0;
    BYTE buffer[512];
    char *name = malloc(8);

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
    FILE *jpg = NULL;
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (n >= 1)
            {
                i++;
            }
            n++;
            if (i < 10)
            {
                sprintf(name, "00%i.jpg", i);
            }
            else if (i >= 10 && i <= 99)
            {
                sprintf(name, "0%i.jpg", i);
            }
            else
            {
                sprintf(name, "%i.jpg", i);
            }
            jpg = fopen(name, "a");
        }

        if (jpg != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpg);
        }


    }
    free(name);
    fclose(jpg);
    fclose(file);
}