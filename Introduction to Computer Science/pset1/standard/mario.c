#include <cs50.h>
#include <stdio.h>

int main(void)
{
   
    int n;
    do
    {
        printf("heigth: ");
        n = GetInt();
  }while(n < 0 || n > 23);
    for(int i = 2;i < n + 2;i++)
    {
        int j = n - i + 1;
        while(j > 0)
        {
            printf(" ");
            j--;
        }
        j = i;
        while(j > 0)
        {
            printf("#");
            j--;
        }
        printf("\n");
   }

}
