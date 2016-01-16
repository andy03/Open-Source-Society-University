#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<stdio.h>

int main(void)
{
    string s = GetString();
    int n = strlen(s);
    if(isalpha(s[0])) printf("%c", toupper(s[0]));
    for(int i = 1; i<n;i++)
    {
        
        if(!(isalpha(s[i-1]))&&(isalpha(s[i]))) printf("%c",toupper(s[i]));
    }   
    printf("\n");
    return 0;
}
