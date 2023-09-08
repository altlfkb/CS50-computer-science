#include "helpers.h"
#include <math.h>
#include <string.h>

BYTE check_limits(int a);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            BYTE media = round(((float)image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3);
            image[h][w].rgbtRed = media;
            image[h][w].rgbtGreen = media;
            image[h][w].rgbtBlue = media;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            RGBTRIPLE original = image[h][w];
            image[h][w].rgbtRed = check_limits(round(.393 * original.rgbtRed + .769 * original.rgbtGreen + .189 * original.rgbtBlue));
            image[h][w].rgbtGreen = check_limits(round(.349 * original.rgbtRed + .686 * original.rgbtGreen + .168 * original.rgbtBlue));
            image[h][w].rgbtBlue = check_limits(round(.272 * original.rgbtRed + .534 * original.rgbtGreen + .131 * original.rgbtBlue));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width / 2; w++) {
                RGBTRIPLE aux = image[h][w];
                image[h][w] = image[h][width - 1 - w];
                image[h][width - 1 - w] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //primeiro criar uma cópia da original, pq os bytes serao modificados
    RGBTRIPLE original[height][width];
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            original[h][w] = image[h][w];
        }
    }
    //agora outro for para passar pixel a pixel 
    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            int count = 0, red = 0, green = 0, blue = 0;
            for (int aux_h = h - 1; aux_h <= h + 1; aux_h++) {
                if (aux_h < 0 || aux_h > height - 1) {
                    continue;
                }
                for (int aux_w = w - 1; aux_w <= w + 1; aux_w++) {
                    if (aux_w < 0 || aux_w > width - 1) {
                        continue;
                    }
                    red += original[aux_h][aux_w].rgbtRed;
                    green += original[aux_h][aux_w].rgbtGreen;
                    blue += original[aux_h][aux_w].rgbtBlue;
                count++;    
                } 
            }
            image[h][w].rgbtRed = round((float) red / count);
            image[h][w].rgbtGreen = round((float) green / count);
            image[h][w].rgbtBlue = round((float) blue / count);
        }
    }
    
    return;
}

//Funções auxiliares
    //Função para Sépia
BYTE check_limits(int a) {
    if (a > 255) {
        return 255;
    }
    return a;
}

