#include<stdio.h>
void InsertSort(int arr[], int n)
{
    int i,j;
    //初始时默认arr[0]为有序arr[1...n]无序
    for(i=1;i<n;i++)    
    {
        int tmp=arr[i];
        if(tmp>arr[i-1])    //后一个数大于前一个数，稳定排序
        {
            for(j=i-1;j>=0&&tmp>arr[j];j--)
            {
                arr[j+1]=arr[j];
            }
            arr[j+1]=tmp;
        }
    }
}


void insert_sort(int a[], int n)
{
    int i, j, k;

    for (i = 1; i < n; i++)
    {
        //为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
        for (j = i - 1; j >= 0; j--)
            if (a[j] < a[i])
                break;

        //如找到了一个合适的位置
        if (j != i - 1)
        {
            //将比a[i]大的数据向后移
            int temp = a[i];
            for (k = i - 1; k > j; k--)
                a[k + 1] = a[k];
            //将a[i]放到正确位置上
            a[k + 1] = temp;
        }
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

    InsertSort(arr,10);

    printf("after sort:\n");
    for(i=0;i<10;i++)
        printf("[%d] ",arr[i]);
    printf("\n");
    return 0;
}
