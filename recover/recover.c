#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("The file is not readable.") return 1;
    }
    if (argc > 2)
    {
        printf("take exact one argument only");
        return 1;
    }
}