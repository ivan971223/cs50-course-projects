#include "helpers.h"
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
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
            int box_red = 0, box_green = 0, box_blue = 0, average_red, average_green, average_blue;
            int count = 0;

            for (int m = i - 1; m <= i + 1; m++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    if (m >= 0 && n >= 0 && m <= height && n <= width)
                    {
                        box_red += image[m][n].rgbtRed;
                        box_green += image[m][n].rgbtGreen;
                        box_blue += image[m][n].rgbtBlue;
                        count += 1;
                    }
                }
            }
            average_red = box_red / count;
            average_green = box_green / count;
            average_blue = box_blue / count;

            image[i][j].rgbtRed = average_red;
            image[i][j].rgbtGreen = average_green;
            image[i][j].rgbtBlue = average_blue;
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

            for (int m = i - 1; m <= i + 1; m++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    if (m >= 0 && n >= 0 && m <= height && n <= width)
                    {
                        box_red += image[m][n].rgbtRed;
                        box_green += image[m][n].rgbtGreen;
                        box_blue += image[m][n].rgbtBlue;
                    }
                }
            }
            average_red = box_red / count;
            average_green = box_green / count;
            average_blue = box_blue / count;

            image[i][j].rgbtRed = average_red;
            image[i][j].rgbtGreen = average_green;
            image[i][j].rgbtBlue = average_blue;
        }
    }
    return;
}
