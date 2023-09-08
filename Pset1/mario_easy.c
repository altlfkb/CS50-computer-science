#include <stdio.h>
#include <cs50.h>

int main(void)
{
   int n;
   do
   {
        n = get_int("Escolha a altura da pirâmide (entre 1 e 8): ");
   }
   while (n < 1 || n > 8);
     
   for (int i = 0; i < n; i++)
   {
       for (int space = 0; space < n - i - 1; space++)
      {
         printf(" ");
      }
      for (int j = 0; j <= i; j++)
        {
             printf("#");
        }
      printf("\n");
   }
}