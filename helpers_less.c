#include "helpers.h"
#include <math.h>
#include<stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float sum_pixel = 0;
    for (int i = 0; i < height ; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            sum_pixel = round((round(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)) / 3);

            image[i][j].rgbtRed = sum_pixel;
            image[i][j].rgbtGreen = sum_pixel;
            image[i][j].rgbtBlue = sum_pixel;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0;
    int sepiaGreen = 0;
    int sepiaBlue = 0;

    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i += 1)
    {
        int half = (width / 2);
        for (int j = 0; j < half; j += 1)
        {
            int k = (width - j - 1);

            int temp_pixRed =  image[i][j].rgbtRed;
            int temp_pixGreen = image[i][j].rgbtGreen;
            int temp_pixBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;

            image[i][k].rgbtRed = temp_pixRed;
            image[i][k].rgbtGreen = temp_pixGreen;
            image[i][k].rgbtBlue = temp_pixBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    long double average_Red  = 0;
    long double average_Green = 0;
    long double average_Blue = 0;

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i += 1)
    {
        if (i == 0)
        {
            for (int j = 0; j < width; j += 1)
            {
                if (j == 0)
                {
                    average_Red = round(((image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed)/4.0));
                    average_Green = round(((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen)/4.0));
                    average_Blue = round(((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue)/4.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue= average_Blue;
                }
                else if (j == (width - 1))
                {
                    average_Red = round(((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed) /4.0));
                    average_Green = round(((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen) /4.0));
                    average_Blue = round(((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue) /4.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue= average_Blue;
                }
                else
                {
                    average_Red = round(((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i][j+1].rgbtRed) / 6.0));
                    average_Green = round(((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i][j+1].rgbtGreen)/ 6.0));
                    average_Blue = round(((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i][j+1].rgbtBlue) / 6.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue = average_Blue;
                }

            }
        }
        else if (i == (height - 1))
        {
            for (int j = 0; j < width; j += 1)
            {
                if (j == 0)
                {
                    average_Red = round(((image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed) / 4.0));
                    average_Green = round(((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen) / 4.0));
                    average_Blue = round(((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue) / 4.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue = average_Blue;

                }
                else if (j == (width - 1))
                {

                    average_Red = round(((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed) / 4.0));
                    average_Green = round(((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen) / 4.0));
                    average_Blue = round(((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue) / 4.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue = average_Blue;

                }
                else
                {
                    average_Red = round(((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed) / 6.0));
                    average_Green = round(((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen)/ 6.0));
                    average_Blue = round(((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue) / 6.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue = average_Blue;
                }

            }
        }
        else
        {
            for (int j = 0; j < width; j += 1)
            {
                if (j == 0)
                {
                    average_Red = round(((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j].rgbtRed) / 6.0));
                    average_Green = round(((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j].rgbtGreen) / 6.0));
                    average_Blue = round(((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j].rgbtBlue) / 6.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue= average_Blue;
                }
                else if (j == (width - 1))
                {
                    average_Red = round(((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed) / 6.0));
                    average_Green = round(((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen) / 6.0));
                    average_Blue = round(((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue) / 6.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue = average_Blue;
                }
                else
                {
                    average_Red = round(round(round(image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed +  image[i+1][j+1].rgbtRed + image[i+1][j].rgbtRed +  image[i+1][j-1].rgbtRed) / 9.0));
                    average_Green = round(round(round(image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen)/ 9.0));
                    average_Blue = round(round(round(image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue) / 9.0));

                    temp[i][j].rgbtRed = average_Red;
                    temp[i][j].rgbtGreen = average_Green;
                    temp[i][j].rgbtBlue = average_Blue;
                }
            }
        }

    }

    for (int i = 0; i < height ; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return ;
}
