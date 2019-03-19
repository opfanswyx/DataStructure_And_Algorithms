#include<stdio.h>
int a[1001][1001],n;

int max(int x, int y)
{
    if(x>y)
        return x;
    else
        return y;
}

int f(int x,int y)
{
    if(x==n)
        return a[x][y];
    return a[x][y]+max(f(x+1,y),f(x+1,y+1));
}
int main()
{
    printf("please input :\n");
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    }
    printf("result=[%d]\n",f(1,1));
    return 0;
}