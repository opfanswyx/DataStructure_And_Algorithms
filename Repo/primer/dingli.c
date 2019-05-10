#include<stdio.h>
int fun(int n)
{
        int i,j;
        if(n<=1)
                return -1;
        for(i=n;i>=2;i--)
        {
                int flag = 0;
                for(j=2;j<i;j++)
                {
                        if(i%j==0)
                        {
                                flag = 1;
                        }
                }
                if(flag == 0)
                {
                        return i;
                }
        }
        return -1;
}
int main(int agrc, char **argv)
{
        int num, result;
        num = atoi(argv[1]);
        result = fun(num);
        printf("result = %d\n",result);
        return 0;
}
