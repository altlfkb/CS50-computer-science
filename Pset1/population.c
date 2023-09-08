#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    
    //Solicite o valor inicial e o valor final
    int inicio, fim, copiaini;
    int count = 0;
    do
    {
        inicio = get_int("Digite o valor de lhamas inicial(no mínimo 9): ");
    }
    while (inicio < 9);
    
    do
    {
        fim = get_int("Digite o valor final de lhamas final(no mínimo igual ao valor inicial): ");
    }
    while (fim < inicio);
    
    copiaini = inicio;
    while (copiaini < fim)
    {
        copiaini = (copiaini/3 - copiaini/4) + copiaini;
        count += 1;
    }
    //imprimir o num de anos na tela
    printf("Years: %i\n", count);
}