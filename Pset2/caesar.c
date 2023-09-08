#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(int argn, string argv[]) {
    if (argn != 2) {
        printf("Erro! Digite exatamente uma chave.\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++) {
        if ((!isdigit(argv[1][i]))) {
            printf("./caesar key\n");
            return 1;
        }
    }
    int arg1 = atoi(argv[1]);
    string plaintext = get_string("Digite o texto: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int a = ((plaintext[i] + arg1 - 97) % 26) + 97;
            printf("%c", a);
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int b = ((plaintext[i] + arg1 - 65) % 26) + 65;
            printf("%c", b);
        }
        else 
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}