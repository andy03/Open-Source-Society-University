#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int n;
    float change;
    do
    {   
        printf("How much change is owed?\n");
        change=GetFloat();
        n= (int) roundf(change*100);
    }while(n<0);
    int quarters = n / 25;
    n = n - quarters * 25;
    int dimes = n / 10;
    n = n - dimes * 10;
    int nickels = n / 5;
    n = n - nickels * 5;
    int pennies =n;
       
    
    int sum = quarters+dimes+nickels+pennies;
    printf("%i\n" , sum );
  
}

