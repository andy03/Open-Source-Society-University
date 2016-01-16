#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>

int main(int argc, string argv[])
{


    
    if(argc!=2){
        printf("ERROR\n");
        return 1;
        
    }
    else{
        int count = atoi(argv[1]);
        string phrase= GetString();
        for(int i =0, n=strlen(phrase);i<n;i++){
            if(isalpha(phrase[i])) {
                if(phrase[i]>=97) phrase[i]=(phrase[i] -97 + count)%26+97;
                else phrase[i]=(phrase[i] -65 + count)%26+65;
                }
            }
        printf("%s\n" , phrase);
        return 0;
    }
  
}

