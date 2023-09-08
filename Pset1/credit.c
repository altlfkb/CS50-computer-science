#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cartao, copiacartao; //definindo as variáveis
    int primeiro, segundo;
    int count = 0;
    int soma = 0;
    
    cartao = get_long("Digite o número do cartão: ");
    
    copiacartao = cartao;
    
    while (copiacartao) { //comçando a contagem dos caracteres e a verificação simultaneamente
        count++;
        if (count > 16) {
            break;
        }
        
        if (count%2) {
            soma += copiacartao%10;
        }
        else {
            soma += ((2*(copiacartao%10))%10) + (((2*(copiacartao%10))/10)%10);
        }
        
        if ((!(copiacartao/100)) && copiacartao/10) { //Achando o primeiro e o segundo dígito
            segundo = copiacartao%10;
            primeiro = (copiacartao/10)%10;
        }
        
        copiacartao /= 10;
    }
    
    if ((count < 13) || (count > 16)) { //Verificando a quantidade de números (pode ser colocado mais acima pra evitar a primeira parte do programa)
        printf("INVALID\n");
        return 0;
    }
    
    if (!(soma%10)) {
        if ((primeiro == 3) && (count == 15) && ((segundo == 4) || (segundo == 7))) {
           printf("AMEX\n");
           return 0;
        }
        
        else if ((primeiro == 4) && ((count >= 13) && (count <= 16))) {
            printf("VISA\n");
           return 0;
        }
        
        else if ((primeiro == 5) && (count == 16) && (segundo < 6)) {
           printf("MASTERCARD\n");
           return 0; 
        }
        
        else {
            printf("INVALID\n");
            return 0;
        }
        
    }
    
    else {
        printf("INVALID\n");
        return 0;
    }
}