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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    long double average_RedX  = 0;
    long double average_RedY  = 0;
    long double average_GreenX = 0;
    long double average_GreenY = 0;
    long double average_BlueX = 0;
    long double average_BlueY = 0;

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i += 1)
    {
        if (i == 0)
        {
            for (int j = 0; j < width; j += 1)
            {
                if (j == 0)
                {

                    average_RedX = round(image[i][j+1].rgbtRed*2.0  + image[i+1][j+1].rgbtRed*1);
                    average_RedY = round(image[i+1][j].rgbtRed*2.0  + image[i+1][j+1].rgbtRed*1);
                    long double final_red = round(sqrtl(pow(average_RedX,2) + pow(average_RedY,2)));
                    average_GreenX = round(image[i][j+1].rgbtGreen*2.0  + image[i+1][j+1].rgbtGreen*1);
                    average_GreenY = round(image[i+1][j].rgbtGreen*2.0  + image[i+1][j+1].rgbtGreen*1);
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i][j+1].rgbtBlue*(2.0)  + image[i+1][j+1].rgbtBlue*(1));
                    average_BlueY = round(image[i+1][j].rgbtBlue*(2.0)  + image[i+1][j+1].rgbtBlue*(1));
                    long double final_blue = round(sqrtl(pow(average_BlueX,2.0) + pow(average_BlueY,2.0)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue = final_blue;
                }
                else if (j == (width - 1))
                {
                    average_RedX = round(image[i][j-1].rgbtRed*(-2)  + image[i+1][j-1].rgbtRed*(-1));
                    average_RedY = round(image[i+1][j-1].rgbtRed*1  + image[i+1][j].rgbtRed*2);
                    long double final_red = round(sqrtl(pow(average_RedX,2) + pow(average_RedY,2)));
                    average_GreenX = round(image[i][j-1].rgbtGreen*(-2)  + image[i+1][j-1].rgbtGreen*(-1));
                    average_GreenY = round(image[i+1][j-1].rgbtGreen*1  + image[i+1][j].rgbtGreen*2);
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i][j-1].rgbtBlue*(-2)  + image[i+1][j-1].rgbtBlue*(-1));
                    average_BlueY = round(image[i+1][j-1].rgbtBlue*1  + image[i+1][j].rgbtBlue*2);
                    long double final_blue = round(sqrtl(pow(average_BlueX,2) + pow(average_BlueY,2)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue= final_blue;
                }

                else
                {
                    average_RedX = round(image[i][j-1].rgbtRed*(-2)  + image[i+1][j-1].rgbtRed*(-1) + image[i][j+1].rgbtRed*2 + image[i+1][j+1].rgbtRed*1);
                    average_RedY = round(image[i+1][j-1].rgbtRed*1  + image[i+1][j].rgbtRed*2 + image[i+1][j+1].rgbtRed*1);
                    long double final_red = round(sqrtl(round(pow(average_RedX,2) + pow(average_RedY,2))));
                    average_GreenX = round(image[i][j-1].rgbtGreen*(-2)  + image[i+1][j-1].rgbtGreen*(-1) + image[i][j+1].rgbtGreen*2 + image[i+1][j+1].rgbtGreen*1);
                    average_GreenY = round(image[i+1][j-1].rgbtGreen*1  + image[i+1][j].rgbtGreen*2 +image[i+1][j+1].rgbtGreen*1);
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i][j-1].rgbtBlue*(-2.0)  + image[i+1][j-1].rgbtBlue*(-1.0) + image[i][j+1].rgbtBlue*2.0 + image[i+1][j+1].rgbtBlue*1.0);
                    average_BlueY = round(image[i+1][j-1].rgbtBlue*1.0  + image[i+1][j].rgbtBlue*2.0 + image[i+1][j+1].rgbtBlue*1.0);
                    long double final_blue = round(sqrtl(pow(average_BlueX,2.0) + pow(average_BlueY,2.0)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue= final_blue;
                }

            }
        }
        else if (i == (height - 1))
        {
            for (int j = 0; j < width; j += 1)
            {
                if (j == 0)
                {
                    average_RedX = round(image[i-1][j+1].rgbtRed*1  + image[i][j+1].rgbtRed*2);
                    average_RedY = round(image[i-1][j].rgbtRed*(-2)  + image[i-1][j+1].rgbtRed*(-1));
                    long double final_red = round(sqrtl(pow(average_RedX,2) + pow(average_RedY,2)));
                    average_GreenX = round(image[i-1][j+1].rgbtGreen*1  + image[i][j+1].rgbtGreen*2);
                    average_GreenY = round(image[i-1][j].rgbtGreen*(-2)  + image[i-1][j+1].rgbtGreen*(-1));
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i-1][j+1].rgbtBlue*1  + image[i][j+1].rgbtBlue*2);
                    average_BlueY = round(image[i-1][j].rgbtBlue*(-2)  + image[i-1][j+1].rgbtBlue*(-1));
                    long double final_blue = round(sqrtl(pow(average_BlueX,2) + pow(average_BlueY,2)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue= final_blue;

                }
                else if (j == (width - 1))
                {
                    average_RedX = round(image[i][j-1].rgbtRed*(-2)  + image[i-1][j-1].rgbtRed*(-1));
                    average_RedY = round(image[i-1][j].rgbtRed*(-2)  + image[i-1][j-1].rgbtRed*(-1));
                    long double final_red = round(sqrtl(pow(average_RedX,2) + pow(average_RedY,2)));
                    average_GreenX = round(image[i][j-1].rgbtGreen*(-2)  + image[i-1][j-1].rgbtGreen*(-1));
                    average_GreenY = round(image[i-1][j].rgbtGreen*(-2)  + image[i-1][j-1].rgbtGreen*(-1));
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i][j-1].rgbtBlue*(-2)  + image[i-1][j-1].rgbtBlue*(-1));
                    average_BlueY = round(image[i-1][j].rgbtBlue*(-2)  + image[i-1][j-1].rgbtBlue*(-1));
                    long double final_blue = round(sqrtl(pow(average_BlueX,2) + pow(average_BlueY,2)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue= final_blue;

                }
                else
                {
                    average_RedX = round(image[i][j-1].rgbtRed*(-2)  + image[i-1][j-1].rgbtRed*(-1) + image[i][j+1].rgbtRed*2 + image[i-1][j+1].rgbtRed*1);
                    average_RedY = round(image[i-1][j-1].rgbtRed*(-1)  + image[i-1][j].rgbtRed*(-2) + image[i-1][j+1].rgbtRed*(-1));
                    long double final_red = round(sqrtl(round(pow(average_RedX,2) + pow(average_RedY,2))));
                    average_GreenX = round(image[i][j-1].rgbtGreen*(-2)  + image[i-1][j-1].rgbtGreen*(-1) + image[i][j+1].rgbtGreen*2 + image[i-1][j+1].rgbtGreen*1);
                    average_GreenY = round(image[i-1][j-1].rgbtGreen*(-1)  + image[i-1][j].rgbtGreen*(-2) +image[i-1][j+1].rgbtGreen*(-1));
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i][j-1].rgbtBlue*(-2)  + image[i-1][j-1].rgbtBlue*(-1) + image[i][j+1].rgbtBlue*2 + image[i-1][j+1].rgbtBlue*1);
                    average_BlueY = round(image[i-1][j-1].rgbtBlue*(-1)  + image[i-1][j].rgbtBlue*(-2) + image[i-1][j+1].rgbtBlue*(-1));
                    long double final_blue = round(sqrtl(pow(average_BlueX,2) + pow(average_BlueY,2)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue= final_blue;
                }

            }
        }
        else
        {
            for (int j = 0; j < width; j += 1)
            {
                if (j == 0)
                {
                    average_RedX = round(image[i-1][j+1].rgbtRed*(1)  + image[i][j+1].rgbtRed*(2) + image[i+1][j+1].rgbtRed*1);
                    average_RedY = round(image[i-1][j].rgbtRed*(-2)  + image[i-1][j+1].rgbtRed*(-1) + image[i+1][j].rgbtRed*(2) + image[i+1][j+1].rgbtRed*(1));
                    long double final_red = round(sqrtl(round(pow(average_RedX,2) + pow(average_RedY,2))));
                    average_GreenX = round(image[i-1][j+1].rgbtGreen*(1)  + image[i][j+1].rgbtGreen*(2) + image[i+1][j+1].rgbtGreen*1);
                    average_GreenY = round(image[i-1][j].rgbtGreen*(-2)  + image[i-1][j+1].rgbtGreen*(-1) +image[i+1][j].rgbtGreen*(2) + image[i+1][j+1].rgbtGreen*(1));
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i-1][j+1].rgbtBlue*(1)  + image[i][j+1].rgbtBlue*(2) + image[i+1][j+1].rgbtBlue*1);
                    average_BlueY = round(image[i-1][j].rgbtBlue*(-2)  + image[i-1][j+1].rgbtBlue*(-1) + image[i+1][j].rgbtBlue*(2) + image[i+1][j+1].rgbtBlue*(1));
                    long double final_blue = round(sqrtl(pow(average_BlueX,2) + pow(average_BlueY,2)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue= final_blue;

                }
                else if (j == (width - 1))
                {
                    average_RedX = round(image[i-1][j-1].rgbtRed*(-1)  + image[i][j-1].rgbtRed*(-2) + image[i+1][j-1].rgbtRed*(-1));
                    average_RedY = round(image[i-1][j-1].rgbtRed*(-1)  + image[i-1][j].rgbtRed*(-2) + image[i+1][j-1].rgbtRed*(1) + image[i+1][j].rgbtRed*(2));
                    long double final_red = round(sqrtl(round(pow(average_RedX,2) + pow(average_RedY,2))));
                    average_GreenX = round(image[i-1][j-1].rgbtGreen*(-1)  + image[i][j-1].rgbtGreen*(-2) + image[i+1][j-1].rgbtGreen*(-1));
                    average_GreenY = round(image[i-1][j-1].rgbtGreen*(-1)  + image[i-1][j].rgbtGreen*(-2) +image[i+1][j-1].rgbtGreen*(1) + image[i+1][j].rgbtGreen*(2));
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i-1][j-1].rgbtBlue*(-1)  + image[i][j-1].rgbtBlue*(-2) + image[i+1][j-1].rgbtBlue*(-1));
                    average_BlueY = round(image[i-1][j-1].rgbtBlue*(-1)  + image[i-1][j].rgbtBlue*(-2) + image[i+1][j-1].rgbtBlue*(1) + image[i+1][j].rgbtBlue*(2));
                    long double final_blue = round(sqrtl(pow(average_BlueX,2) + pow(average_BlueY,2)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue= final_blue;
                }

                else
                {
                    average_RedX = round(image[i-1][j-1].rgbtRed*(-1)  + image[i][j-1].rgbtRed*(-2) + image[i+1][j-1].rgbtRed*(-1) + image[i-1][j+1].rgbtRed*(1)  + image[i][j+1].rgbtRed*(2) + image[i+1][j+1].rgbtRed*(1));
                    average_RedY = round(image[i-1][j-1].rgbtRed*(-1)  + image[i-1][j].rgbtRed*(-2) + image[i-1][j+1].rgbtRed*(-1) + image[i+1][j-1].rgbtRed*(1)  + image[i+1][j].rgbtRed*(2) + image[i+1][j+1].rgbtRed*(1));
                    long double final_red = round(sqrtl(round(pow(average_RedX,2) + pow(average_RedY,2))));
                    average_GreenX = round(image[i-1][j-1].rgbtGreen*(-1)  + image[i][j-1].rgbtGreen*(-2) + image[i+1][j-1].rgbtGreen*(-1) + image[i-1][j+1].rgbtGreen*(1)  + image[i][j+1].rgbtGreen*(2) + image[i+1][j+1].rgbtGreen*(1));
                    average_GreenY = round(image[i-1][j-1].rgbtGreen*(-1)  + image[i-1][j].rgbtGreen*(-2) + image[i-1][j+1].rgbtGreen*(-1) + image[i+1][j-1].rgbtGreen*(1)  + image[i+1][j].rgbtGreen*(2) + image[i+1][j+1].rgbtGreen*(1));
                    long double final_green = round(sqrtl(pow(average_GreenX,2) + pow(average_GreenY,2)));
                    average_BlueX = round(image[i-1][j-1].rgbtBlue*(-1)  + image[i][j-1].rgbtBlue*(-2) + image[i+1][j-1].rgbtBlue*(-1) + image[i-1][j+1].rgbtBlue*(1)  + image[i][j+1].rgbtBlue*(2) + image[i+1][j+1].rgbtBlue*(1));
                    average_BlueY = round(image[i-1][j-1].rgbtBlue*(-1)  + image[i-1][j].rgbtBlue*(-2) + image[i-1][j+1].rgbtBlue*(-1) + image[i+1][j-1].rgbtBlue*(1)  + image[i+1][j].rgbtBlue*(2) + image[i+1][j+1].rgbtBlue*(1));
                    long double final_blue = round(sqrtl(pow(average_BlueX,2) + pow(average_BlueY,2)));

                    if (final_blue > 255)
                    {
                        final_blue = 255;
                    }

                    if (final_green > 255)
                    {
                        final_green = 255;
                    }

                    if (final_red > 255)
                    {
                        final_red = 255;
                    }

                    temp[i][j].rgbtRed = final_red;
                    temp[i][j].rgbtGreen = final_green;
                    temp[i][j].rgbtBlue= final_blue;
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
