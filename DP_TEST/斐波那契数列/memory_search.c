#include<stdio.h>
int memo[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int fib(int n)
{
    if(n==0)
        return 1;
    if(n==1)
        return 1;
    
    if(memo[n] == -1)
        memo[n] = fib(n-1) + fib(n-2);

    return memo[n];
}

int main(int argc, int **argv)
{
    int num;
    int i;
    num = atoi(argv[1]);
    printf("argv[1] = %d\n",num);
    printf("\nfib(%d)=[%d]\n",num,fib(num));
    return 0;
}