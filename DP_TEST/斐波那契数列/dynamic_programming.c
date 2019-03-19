#include<stdio.h>
int memo[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int fib(int n)
{
    memo[0] = 1;
    memo[1] = 1;
    for(int i = 2; i<=n;i++)
        memo[i] = memo[i-1] + memo[i-2];

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