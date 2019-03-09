#include<stdio.h>
//交换函数
void swap(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void SelectSort(int arr[], int n)
{
    int i,j,max;
    for(i=0;i<n;i++)
    {
        max=i;
        for(j=i+1;j<n;j++) //找出最大元素的下标
        {
            if(arr[max]<arr[j])
                max=j;
        }
        if(i!=max)
            swap(&arr[i],&arr[max]);
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

    SelectSort(arr,10);

    printf("after sort:\n");
    for(i=0;i<10;i++)
        printf("[%d] ",arr[i]);
    printf("\n");
    return 0;
}