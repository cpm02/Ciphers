//Chakshu Pragya
//201851034
#include <stdio.h>
# include<string.h>
# include<stdlib.h>
void en_ceaser(char ptext[],int n,int key)
{
    char sol[n];
    for(int i=0;i<n;i++)
    {
        sol[i]=(char)((int)(ptext[i]+key-97)%26+97);
        printf("%c",sol[i]);
    }
}
void dec_ceaser(char ctext[],int n,int key)
{
    char sol[n];
    for(int i=0;i<n;i++)
    {
        sol[i]=(char)((int)(ctext[i]-key-97)%26+97);
        printf("%c",sol[i]);
    }
    
}

int main()
{
    char k[6]="crypto";
    en_ceaser(k,6,5);

}