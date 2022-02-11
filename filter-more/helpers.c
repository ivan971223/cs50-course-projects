#include "helpers.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int r_red[width];
        int r_green[width];
        int r_blue[width];
        for (int j = width - 1, n = 0; j >= 0; j--, n++)
        {
            r_red[n] = image[i][j].rgbtRed;
            r_green[n] = image[i][j].rgbtGreen;
            r_blue[n] = image[i][j].rgbtBlue;
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = r_red[j];
            image[i][j].rgbtGreen = r_green[j];
            image[i][j].rgbtBlue = r_blue[j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int box_red = 0, box_green = 0, box_blue = 0, average_red = 0, average_green = 0, average_blue = 0;
            int count = 0;

            for (int m = i - 1; m <= i + 1; m++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    if (m >= 0 && n >= 0 && m <= height - 1 && n <= width - 1)
                    {
                        printf("%i%i\n", m,n);
                        printf("%i\n", image[m][n].rgbtRed);
                        box_red += image[m][n].rgbtRed;
                        box_green += image[m][n].rgbtGreen;
                        box_blue += image[m][n].rgbtBlue;
                        count += 1;
                    }
                }
            }
            average_red = round(box_red / (float)count);
            average_green = round(box_green / (float)count);
            average_blue = round(box_blue / (float)count);

            image[i][j].rgbtRed = average_red;
            image[i][j].rgbtGreen = average_green;
            image[i][j].rgbtBlue = average_blue;
            printf("%s\n", "---");
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_Gx = 0, green_Gx = 0, blue_Gx = 0, red_Gy = 0, green_Gy = 0, blue_Gy = 0;
            int result_red, result_green, result_blue;

            for (int m = i - 1, k = 0; m <= i + 1; m++)
            {
                for (int n = j - 1; n <= j + 1; n++, k++)
                {
                    if (m >= 0 && n >= 0 && m <= height && n <= width)
                    {
                        red_Gx += image[m][n].rgbtRed * Gx[k];
                        red_Gy += image[m][n].rgbtRed * Gy[k];
                        green_Gx += image[m][n].rgbtGreen * Gx[k];
                        green_Gy += image[m][n].rgbtGreen * Gy[k];
                        blue_Gx += image[m][n].rgbtBlue * Gx[k];
                        blue_Gy += image[m][n].rgbtBlue * Gy[k];
                    }
                }
            }
            result_red = round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
            result_green = round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
            result_blue = round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));

            if (result_red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = result_red;
            }
            if (result_green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = result_green;
            }
            if (result_blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = result_blue;
            }
        }
    }
    return;
}
