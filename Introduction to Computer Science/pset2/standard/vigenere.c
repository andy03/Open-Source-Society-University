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
        string key = argv[1];
        int index =0 ;
        for(int i = 0 ; i<strlen(key) ; i++){
            if(isalpha(key[i])==0) { 
                printf("ERROR");
                return 1;
            }
            else key[i]=tolower(key[i]);
            
        }
        string phrase= GetString();
        for(int i =0, n=strlen(phrase);i<n;i++){
            if(isalpha(phrase[i])) {
                if(phrase[i]>=97) {
                    phrase[i]=(phrase[i] -97 + key[index]-97)%26+97;
                    if(index==strlen(key)-1) index=0;
                    else index++;   
                    }   
                else {
                    phrase[i]=(phrase[i] -65 + key[index]-97)%26+65;
                    if(index==strlen(key)-1) index=0;
                    else index++;  
                }
              }
            }
        printf("%s\n" , phrase);
        return 0;
    }
  
}

