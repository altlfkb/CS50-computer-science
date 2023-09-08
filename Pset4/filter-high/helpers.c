#include "helpers.h"
#include <math.h>
#include <string.h>

BYTE check_limits(float a);

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

// Detect edges

int GX[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
int GY[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //definindo a matriz a ser multiplicada
    
    //fazendo cópia dos pixel das imagens
    RGBTRIPLE original[height][width];
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            original[h][w] = image[h][w];
        }
    }
    // agora passar pixel a pixel
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            //agora fazer a matriz 3 x 3, excluindo as bordas
            int redgx = 0, redgy = 0, greengx = 0, greengy = 0, bluegx = 0, bluegy = 0;
            int edge_h = 0;
            for (int aux_h = h - 1; aux_h <= h + 1; aux_h++ ) {
                if (aux_h < 0 || aux_h > height - 1) {
                    edge_h++;
                    continue;
                }
                int edge_w = 0;
                for (int aux_w = w - 1; aux_w <= w + 1; aux_w++) {
                    if (aux_w < 0 || aux_w > width - 1) {
                        edge_w++;
                        continue;
                    }
                    redgx += original[aux_h][aux_w].rgbtRed * GX[edge_h][edge_w];
                    redgy += original[aux_h][aux_w].rgbtRed * GY[edge_h][edge_w];
                    greengx += original[aux_h][aux_w].rgbtGreen * GX[edge_h][edge_w];
                    greengy += original[aux_h][aux_w].rgbtGreen * GY[edge_h][edge_w];
                    bluegx += original[aux_h][aux_w].rgbtBlue * GX[edge_h][edge_w];
                    bluegy+= original[aux_h][aux_w].rgbtBlue * GY[edge_h][edge_w];
                    edge_w++;
                }
                edge_h++;
            }
            image[h][w].rgbtRed = check_limits((float) sqrt(redgx * redgx + redgy * redgy));
            image[h][w].rgbtGreen = check_limits((float) sqrt(greengx * greengx + greengy * greengy));
            image[h][w].rgbtBlue = check_limits((float) sqrt(bluegx * bluegx + bluegy * bluegy));
        }
    }

    return;
}


//Funções auxiliares
    //Função para Sépia
BYTE check_limits(float color) {
    if (color > 255) {
        return 255;
    }
    return round(color);
}
