#include <stdio.h>
# include<string.h>
# include<stdlib.h>
void en_affine(int a,int b,char plaintext[],int n)
{
    char ans[n];
    for(int i=0;i<n;i++)
    {
        ans[i]=(char)((a*(int)(plaintext[i]-65)+b)%26+65);
        printf("%c",ans[i]);
    }
    printf("\n");
    
}
void dec_affine(int a,int b,char ciphertext[],int n)
{
    char ans[n];
    int inva=0;
    for(int i=0;i<26;i++)
    {
        if(a*i%26==1)
        {
            inva=i;
            break;
        }
    }
    for(int j=0;j<n;j++)
    {
        ans[j]=(char)((inva*((int)(ciphertext[j]+65)-b))%26+65);
        printf("%c",ans[j]);
        
    }
    printf("\n");
}

int main()
{
    char k[12]="CRYPTOGRAPHY";
    en_affine(5,4,k,12);
}

