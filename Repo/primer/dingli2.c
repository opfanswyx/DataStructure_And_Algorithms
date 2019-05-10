#include<stdio.h>
#include<stdlib.h>
unsigned long long int func(unsigned long long int n)
{
        unsigned long long int k,x;
        if(n<2)
                return -1;
        else
        {
                int flag = 0;
                x=n+1;
                while(!flag && --x >= 2)
                {
                        flag = 1;
                        for(k=2;k*k <= x; k++)
                        {
                                if(x%k==0)
                                {
                                        flag = 0;
                                        break;
                                }
                        }
                }
                return x;
        }
}

int main(int argc, char **argv)
{
        unsigned long long int num,res;
        num = 18446744073709551615;
        printf("num=%llu\n",num);
        res = func(num);
        printf("%llu\n",res);
}
