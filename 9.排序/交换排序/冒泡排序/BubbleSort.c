#include<stdio.h>
//交换函数
void swap(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
//冒泡函数
void BubbleSort(int arr[], int n)
{
    int i,j;
    for(i=0; i<n-1; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(arr[j]<arr[j+1]) //注意这里是两个"j"比较，不是"j"和"i"比较
                swap(&arr[j],&arr[j+1]);
        }
    }
}
//优化版optimization
void BubbleSort_t(int arr[], int n)
{
    int i,j;
    int flag=1;     //标记
    for(i=0; i<n-1&&flag;i++)
    {
        flag=0; //初始化标记为0
        for(j=0; j<n-i-1; j++)
        {
            if(arr[j]<arr[j+1])
            {
                //如果在一次遍历过程中发生过交换者标记为1,
                //如果没发生交换则有序,flag依然为0，则结束循环。
                flag=1; 
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}
int main()
{
    int i;
    int arr[10]={1,2,3,4,5,6,7,8,9,10};

    printf("before sort:\n");
    for(i=0;i<10;i++)
        printf("[%d] ",arr[i]);
    printf("\n");

    BubbleSort(arr,10);

    printf("after sort:\n");
    for(i=0;i<10;i++)
        printf("[%d] ",arr[i]);
    printf("\n");
    return 0;
}
