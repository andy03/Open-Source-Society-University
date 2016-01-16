/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int min=0, max= n-1;
    if(value>0){
           while(min<=max)
           {
                int center= (min+max)/2;
                if(min==max)
                { 
                    if(values[min]==value) return true; 
                }
                
                if(value<values[center])
                {
                    max=center-1;
                }
                else
                { 
                    if(value>values[center]) 
                    {
                        min=center+1;
                    }
                    else 
                    {
                        if (value==values[center]) 
                        return true;
                    }
                }
                
           }
           return false;
    }
    else 
        {return false;}
}






/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int ok=0;
    while(ok==0){
    ok=1;
    for(int i=0;i<n-1;i++)
    {
        if(values[i]>values[i+1]) {int tmp = values[i]; values[i]= values[i+1]; values[i+1] = tmp; ok=0;}
    }
   }
}
