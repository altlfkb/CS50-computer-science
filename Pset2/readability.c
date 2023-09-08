#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {
    int palavras = 1;
    int sent = 0;
    int letras = 0;
    string s = get_string("Digite o texto: ");
    for(int i = 0, n = strlen(s); i < n; i++) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 65 && s[i] <= 90)) { // minúsculas e maiúsculas
            letras++;
        }
        if (s[i]==' ' || s[i]=='\n' || s[i]=='\t') {
            palavras++;
        }
        if (s[i] == '.' || s[i] == '!' || s[i] == '?') {
            sent++;
        }
    }
    float medletras = ((float)letras / palavras) * 100.0;
    float medsent = ((float)sent / palavras) * 100.0;
    float formula = 0.0588 * medletras - 0.296 * medsent - 15.8;
    if (formula < 1) {
        printf("Before Grade 1\n");
        return 0;
    }
    if (formula >= 16) {
        printf("Grade 16+\n");
        return 0;
    }
    else {
        int result = round(formula);
        printf("Grade %i\n", result);
        return 0;
    }
    //Testes
    //printf("Letras: %i\n", letras);
    //printf("Palavras: %i\n", palavras);
    //printf("sentenças: %i\n", sent);
    //printf("mletras: %f\n", medletras);
    //printf("msent: %f\n", medsent);
    //printf("Fórmula: %f\n", formula);
}