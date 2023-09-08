#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argn, string argv[]) {
    if (argn != 2) {
        printf("./ Chave de substituição.\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++) { //acessando cada letra e testando outras consições simultaneamente
        if (isdigit(argv[1][i]) || n != 26) {
            printf("A chave deve conter 26 caracteres alfabéticos sem repetição.\n");
            return 1;
        }
        for (int j = i + 1; j < n; j++) { //verificando se a letra da posição é igual a alguma outra letra a frente
            if (i + 1 > 26) {
                break;
            }
            else if (argv[1][i] == argv [1][j]) {
                printf("A chave deve conter 26 caracteres alfabéticos sem repetição.\n");
                return 1;
            }
        }
    }
    string s = get_string("plaintext: "); 
    
    printf("ciphertext: ");
    
    for (int k = 0, m = strlen(s); k < m; k++) {
        if (islower(s[k])) {
            printf("%c", tolower(argv[1][s[k]-97]));
        }
        else if (isupper(s[k])) {
            printf("%c", toupper(argv[1][s[k] -65]));
        }
        else {
            printf("%c", s[k]);
        }
    }
    printf("\n");
    return 0;
}