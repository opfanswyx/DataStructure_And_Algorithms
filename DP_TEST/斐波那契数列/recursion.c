#include<stdio.h>

int fib(int n)
{
    if(n==0)
        return 1;
    if(n==1)
        return 1;
    return fib(n-1)+fib(n-2);
}

int main(int argc, int **argv)
{
    int num;
    num = atoi(argv[1]);
    printf("argv[1] = %d\n",num);

    printf("fib(%d)=[%d]\n",num,fib(num));

    return 0;
}