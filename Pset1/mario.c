#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int a;
    do
    {
        a = get_int("Digite a altura da priâmide(entre 1 e 8): ");
    }
    while (a < 1 || a > 8);
    for (int i = 0; i < a; i++)
    {
        for (int space = 0; space < a - i - 1; space++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        {
            printf("  ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        {
            printf("\n");
        }
    }
}

