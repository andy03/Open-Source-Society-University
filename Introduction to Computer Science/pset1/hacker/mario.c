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
  
    for(int i = 1;i < n + 1;i++)
    {
        int j = n - i ;
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
        
        printf("  ");
        
    
        j = i;
        while(j > 0)
        {
            printf("#");
            j--;
        }

printf("\n");
   }
   return 0;

}
