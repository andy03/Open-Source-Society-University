#include<cs50.h>
#include<stdio.h>

long long putere( int counter)
{
long long n=1;
    while(counter>0)
    {
        n = n*10;
        counter --;
    }

return n;
}


int main(void)
{

    printf("Enter card value: \n");
    long long n = GetLongLong();
    
    int odd=0,even=0,counter=0;
    
    long long n1 = n;
    
    while(n1>0)
    {
        n1=n1/10;
        counter++;
    }
    
    for(int i=0; i<counter ; i++)
    {
        if(i%2!=0) 
        {
            odd = odd+i;
        }    
        else {
            int j = i*2;
            while(j>0)
            {
                even = even + j%10;
                j=j/10; 
            }
        }
    }
    
  

    if(counter>12&&counter<17){
        if(counter==15 && ( n/putere(counter-2)==34||n/putere(counter-2)==37)){
        printf("AMEX\n");
        }
        else if(counter==16 &&(n/putere(counter-2) >=51 && n/putere(counter-2) <=55)){
            printf("MASTERCARD\n" );
        }
        else if(counter>=13 && counter<=16 && n/putere(counter-1) == 4){
            printf("VISA\n" );
        }
        else{
            printf("INVALID\n" );  
        }
    }
    else{
        printf("INVALID\n" );      
    }      
    
    return 0;
}


