#include <cs50.h>
#include <stdio.h>
#include <math.h>

//imput de troco do usuário
int main(void)
{
    float valor;
    int a = 25;
    int b = 10;
    int c = 5;
    int d = 1;
    do
    {
       valor = get_float("Digite o troco em reais: ");
    }
    while (valor < 0);
// transformando o float de troco em int em centavos
    int valor2 = round(valor * 100);
    int moedas = 0;
    
// Aqui começa a contagem do troco
    while (valor2 >= a) //25 centavos
    {
        moedas += 1;
        valor2 = valor2 - a;
        
    }
    while (valor2 >= b) //10 centavos
    {
        
        moedas += 1;
        valor2 = valor2 - b;

    }
    while (valor2 >= c) //5 centavos
    {
        moedas += 1;
        valor2 = valor2 - c; 
        
    }
    while (valor2 >= d) //1 centavo
    {
        moedas += 1;
        valor2 = valor2 - d;
        
    }
    printf("%i\n", moedas); //print número de moedas
    
}