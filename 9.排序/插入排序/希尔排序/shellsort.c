#include<stdio.h>
void ShellSort(int arr[], int n)
{
    int i,j,d;
    int tmp;
    d=n/2;              //设置增量初值
    while(d>0)
    {
        for(i=d;i<n;i++)    //对所有间隔d的元素组进行直接插入排序
        {
            tmp=arr[i];
            j=i-d;
            while(j>=0 && tmp>arr[j])   //对每组中的数据进行排序
            {
                arr[j+d]=arr[j];
                j=j-d;
            }
            arr[j+d]=tmp;
        }
        d=d/2;
    }
}

int main()
{
    int i;
    //int arr[10]={10,9,8,7,6,5,4,3,2,1};
    int arr[10]={5,0,9,8,1,4,6,3,7,5};

    printf("before sort:\n");
    for(i=0;i<10;i++)
        printf("[%d] ",arr[i]);
    printf("\n");

    ShellSort(arr,10);

    printf("after sort:\n");
    for(i=0;i<10;i++)
        printf("[%d] ",arr[i]);
    printf("\n");
    return 0;
}