#include <stdio.h>
# include<string.h>
# include<stdlib.h>
# include<inttypes.h>
unsigned long func(unsigned long r0,unsigned long key)
{
    unsigned long x0=r0 ^ key;
    
    unsigned long t2=x0 & 0xffff;
    unsigned long t1=x0 >> 16;
    unsigned long t12=t1 & 0xff;
    unsigned long t11=t1 >> 8;
    unsigned long t22=t2 & 0xff;
    unsigned long t21=t2 >>8;
    unsigned long b2=t11 & 0xf;
    unsigned long b1=t11 >> 4;
    unsigned long b4=t12 & 0xf;
    unsigned long b3=t12 >> 4;
    unsigned long b6=t21 & 0xf;
    unsigned long b5=t21 >> 4;
    unsigned long b8=t22 & 0xf;
    unsigned long b7=t22 >> 4;
    
    unsigned long s[16];
    for(int i=0;i<16;i++)
    {
        s[i]=(i+1)%16;
    }
    unsigned long y0=(s[part[7]]<<28)|(s[part[6]]<<24)|(s[part[5]]<<20)|(s[part[4]]<<16)|(s[part[3]]<<12)|(s[part[2]]<<8)|(s[part[1]]<<4)|(s[part[0]]);
    return y0;
}
unsigned long long en(unsigned long long pt,unsigned long key)
{
    unsigned long l0=pt>>32;
    unsigned long r0=pt & 0xffffffff;
    unsigned long l1=r0;
    unsigned long y0=func(r0,key);
    unsigned long r1=l0 ^ y0;
    unsigned long long ans=(l1<<32)|r1;
    return ans;

}
unsigned long long dec(unsigned long key,unsigned long long ct)
{
    unsigned long l1=ct>>32;
    unsigned long r1=ct & 0xffffffff;
    unsigned long r0=l1;
    unsigned long l0=r1 ^ func(l1,key);
    unsigned long long ans=(l0<<32)|r0;
    return ans;
}
int main()
{
    unsigned long long pt=1025872731371558909;
    unsigned long key=3125506294;
    unsigned long long ans=en(pt,key);
    printf("%lld \n",ans);
    printf("\n");
    unsigned long long ans1=dec(key,ans);
    printf("%lld",ans1);

}