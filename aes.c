//chakshu pragya
//201851034
#include <stdio.h>
# include<string.h>
# include<stdlib.h>
# include<inttypes.h>
// 128 bit aes- 128 bit plaintext
// 128 bit secret key
//round func=10
// 128 bit too big to handle
unsigned long subbox(unsigned long x)
{
    int row;
    int col;
    row=x>>4;
    col=x&0xf;
    unsigned long ans;
    unsigned long subbyte[16][16]={   0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

    ans=subbyte[row][col];
    return ans;
}
// defining function for multiplying it with x
unsigned long xmul(unsigned long s)
{
    
    unsigned long onebit=s>>7;
    if(onebit==1)
    {
        s=((s<<1)^27)&255;
    }
    else
    {s=(s<<1)&255;}
    return s;
}
unsigned long rotword(unsigned long b)
{
    unsigned long b0=b>>24;
    unsigned long b1=(b>>16)& 0xff;
    unsigned long b2=(b>>8)& 0xff;
    unsigned long b3=b& 0xff;
    unsigned long ans;
    ans=(b1<<24)|(b2<<16)|(b3<<8)|b0;
    return ans;
}
unsigned long subword(unsigned long b)
{
    unsigned long b0=b>>24;
    unsigned long b1=(b>>16)& 0xff;
    unsigned long b2=(b>>8)& 0xff;
    unsigned long b3=b& 0xff;
    unsigned long ans;
    ans=(subbox(b0)<<24)|(subbox(b1)<<16)|(subbox(b2)<<8)|(subbox(b3));
    return ans;
}

void f_func(unsigned long x[4][4])
{
    unsigned long s[4][4];
    unsigned long sdash[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            s[j][i]=subbox(x[j][i]);
        }
    }
    //performing shift rows
    unsigned long temp1=s[1][0];
    s[1][0]=s[1][1];
    s[1][1]=s[1][2];
    s[1][2]=s[1][3];
    s[1][3]=temp1;
    //second row is shifted
    unsigned long temp2=s[2][0];
    unsigned long temp3=s[2][1];
    s[2][0]=s[2][2];
    s[2][1]=s[2][3];
    s[2][2]=temp2;
    s[2][3]=temp3;
    //3rd row is shifted
    temp1=s[3][3];
    s[3][3]=s[3][2];
    s[3][2]=s[3][1];
    s[3][1]=s[3][0];
    s[3][0]=temp1;
    //4th row is shifted
    // shift row completed;


    //mix colmn
    for(int i=0;i<4;i++)
    {
        sdash[0][i]=xmul(s[0][i])^xmul(s[1][i])^s[1][i]^s[2][i]^s[3][i];
        sdash[1][i]=s[0][i]^xmul(s[1][i])^s[2][i]^xmul(s[2][i])^s[3][i];
        sdash[2][i]=s[0][i]^s[1][i]^xmul(s[2][i])^xmul(s[3][i])^s[3][i];
        sdash[3][i]=xmul(s[0][i])^s[0][i]^s[1][i]^s[2][i]^xmul(s[3][i]);
    }
    for(int l=0;l<4;l++)
        {
            for(int m=0;m<4;m++)
            {
                x[l][m]=sdash[l][m];
            }
        }

}
void sub_sift(unsigned long x[4][4])
{
    unsigned long s[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            s[j][i]=subbox(x[j][i]);
        }
    }
    //performing shift rows
    unsigned long temp1=s[1][0];
    s[1][0]=s[1][1];
    s[1][1]=s[1][2];
    s[1][2]=s[1][3];
    s[1][3]=temp1;
    //second row is shifted
    unsigned long temp2=s[2][0];
    unsigned long temp3=s[2][1];
    s[2][0]=s[2][2];
    s[2][1]=s[2][3];
    s[2][2]=temp2;
    s[2][3]=temp3;
    //3rd row is shifted
    temp1=s[3][3];
    s[3][3]=s[3][2];
    s[3][2]=s[3][1];
    s[3][1]=s[3][0];
    s[3][0]=temp1;
    //4th row is shifted
    // shift row completed;


    
    for(int l=0;l<4;l++)
        {
            for(int m=0;m<4;m++)
            {
                x[l][m]=s[l][m];
            }
        }

}

int main()
{
    unsigned long long textl =0x3243f6a8885a308d;//left 64 bit
    unsigned long long textr =0x313198a2e0370734;//right 64 bit
    //total 128 bit
    unsigned long x[4][4];
    x[0][0]=textl>>56;
    
    x[1][0]=(textl>>48)& 0xff;
    // printf("%lx \n",x[1][0]);
    x[2][0]=(textl>>40)& 0xff;
    x[3][0]=(textl>>32)& 0xff;
    x[0][1]=(textl>>24)& 0xff;
    x[1][1]=(textl>>16)& 0xff;
    x[2][1]=(textl>>8)& 0xff;
    x[3][1]=textl & 0xff;
    x[0][2]=textr>>56;
    x[1][2]=(textr>>48)& 0xff;
    x[2][2]=(textr>>40)& 0xff;
    x[3][2]=(textr>>32)& 0xff;
    x[0][3]=(textr>>24)& 0xff;
    x[1][3]=(textr>>16)& 0xff;
    x[2][3]=(textr>>8)& 0xff;
    x[3][3]=textr & 0xff;
//key generation******************


    unsigned long long cipherl =0X2b7e151628aed2a6;//left 64 bit
    unsigned long long  cipherr =0xabf7158809cf4f3c;//right 64 bit
    //total 128 bit
    unsigned long k[16];
    k[0]=cipherl>>56;
    //printf("%lu \n",k[0]);
    k[1]=(cipherl>>48)& 0xff;
    //printf("%lu \n",k[1]);
    k[2]=(cipherl>>40)& 0xff;
    //printf("%lu \n",k[2]);
    k[3]=(cipherl>>32)& 0xff;
    //printf("%lu \n",k[3]);
    k[4]=(cipherl>>24)& 0xff;
    //printf("%lu \n",k[4]);
    k[5]=(cipherl>>16)& 0xff;
    //printf("%lu \n",k[5]);
    k[6]=(cipherl>>8)& 0xff;
    //printf("%lu \n",k[6]);
    k[7]=cipherl & 0xff;
    //printf("%lu \n",k[7]);
    k[8]=cipherr>>56;
    //printf("%lu \n",k[8]);
    k[9]=(cipherr>>48)& 0xff;
    //printf("%lu \n",k[9]);
    k[10]=(cipherr>>40)& 0xff;
    //printf("%lu \n",k[10]);
    k[11]=(cipherr>>32)& 0xff;
    //printf("%lu \n",k[11]);
    k[12]=(cipherr>>24)& 0xff;
    //printf("%lu \n",k[12]);
    k[13]=(cipherr>>16)& 0xff;
    //printf("%lu \n",k[13]);
    k[14]=(cipherr>>8)& 0xff;
    //printf("%lu \n",k[14]);
    k[15]=cipherr & 0xff;
    //printf("%lu \n",k[15]);

    unsigned long Rcon[10]={0x01000000,
                            0x02000000,
                            0x04000000,
                            0x08000000,
                            0x10000000,
                            0x20000000,
                            0x40000000,
                            0x80000000,
                            0x1b000000,
                            0x36000000};
    
    unsigned long w[44];
    for(int i=0;i<4;i++)
    {
        w[i]=(k[4*i]<<24)|(k[4*i+1]<<16)|(k[4*i+2]<<8)|(k[4*i+3]);
    }
    for(int i=4;i<44;i++)
    {
        unsigned long temp=w[i-1];
        if(i%4==0)
        {
            temp=subword(rotword(temp))^Rcon[i/4-1];
        }
        w[i]=w[i-4]^temp;
    }

    unsigned long roundkey[11][4][4];
    int j=0;
    for(int i=0;i<11;i++)
    {
   
        roundkey[i][0][0]=w[j]>>24;
        roundkey[i][1][0]=(w[j]>>16)&0xff;
        roundkey[i][2][0]=(w[j]>>8)&0xff;
        roundkey[i][3][0]=w[j]&0xff;

        roundkey[i][0][1]=w[j+1]>>24;
        roundkey[i][1][1]=(w[j+1]>>16)&0xff;
        roundkey[i][2][1]=(w[j+1]>>8)&0xff;
        roundkey[i][3][1]=w[j+1]&0xff;

        roundkey[i][0][2]=w[j+2]>>24;
        roundkey[i][1][2]=(w[j+2]>>16)&0xff;
        roundkey[i][2][2]=(w[j+2]>>8)&0xff;
        roundkey[i][3][2]=w[j+2]&0xff;

        roundkey[i][0][3]=w[j+3]>>24;
        roundkey[i][1][3]=(w[j+3]>>16)&0xff;
        roundkey[i][2][3]=(w[j+3]>>8)&0xff;
        roundkey[i][3][3]=w[j+3]&0xff;
        j=j+4;
    }

    for(int i=0;i<10;i++)
    {
        for(int l=0;l<4;l++)
        {
            for(int m=0;m<4;m++)
            {
                x[m][l]=x[m][l]^roundkey[i][m][l];
               // printf("%lx ",x[m][l]);
            }
            //printf("\n");
        }
        //printf(" next %d \n",i);
        if(i<9){
        f_func(x);}
        if(i==9)
        {
            sub_sift(x);
             for(int l=0;l<4;l++)
        {
            for(int m=0;m<4;m++)
            {
                x[m][l]=x[m][l]^roundkey[i+1][m][l];
                //printf("%lx ",x[m][l]);
            }
            //printf("\n");
        }
        }
    }
    printf("final ans \n");
    for(int k=0;k<4;k++)
    {

        for(int p=0;p<4;p++)
        {
            printf("%lx ",x[k][p]);
        }
        printf("\n");
    }

}





