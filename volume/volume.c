// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    FILE *file = fopen("1.txt", "a");
    FILE *file2 = fopen("2.txt", "a");
    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(header), 1, output);
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        // fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);
        printf("%u", header[i]);
        fprintf(file, "%u\n", header[i]);
    }

    uint8_t k;
    while (fread(&k, sizeof(uint8_t), 1, output))
    {
        fprintf(file2, "%u\n", k);
    }
    // TODO: Read samples from input file and write updated data to output file
    // int16_t buffer;
    // int i = 0;
    // while (fread(&buffer, sizeof(int16_t), 1, input))
    // {
    //     if (i > 21)
    //     {
    //         buffer *= factor;
    //         printf("%u\n", buffer);
    //         fwrite(&buffer, sizeof(int16_t), 1, output);
    //     }
    //     i++;
    // }

    // Close files
    fclose(input);
    fclose(output);
}
