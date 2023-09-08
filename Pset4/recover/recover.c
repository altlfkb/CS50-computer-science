#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t  BYTE;
int tamanho_file = 512;

void verificar_imagem (FILE *file);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Cannot open the file\n");
        return 1;
    }
    //chamando uma função para verificar se é um arquivo de imagem
    verificar_imagem(file);
    fclose(file);
}

void verificar_imagem(FILE *file) {
    
    FILE *jpeg_file;
    int jpeg_number = 0;
    
    while(true) {
        BYTE file_block[tamanho_file];
        
        int read_bytes = fread(&file_block, tamanho_file, 1, file);
        if (read_bytes != 1) {
            break;
        }
        if (file_block[0] == 0xff && file_block[1] == 0xd8 && file_block[2] == 0xff && (file_block[3] >= 0xe0 && file_block[3] <= 0xff)) {
            if (jpeg_number > 0) {
                fclose(jpeg_file);
            }
            
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_number);
            jpeg_number++;
            
            
            jpeg_file = fopen(filename, "w");
    
        }
        
        if (jpeg_number > 0) {
            fwrite(file_block, tamanho_file, 1, jpeg_file);
        }
    
    
        
    }
    if (jpeg_number > 0) {
        fclose(jpeg_file);
    }
}