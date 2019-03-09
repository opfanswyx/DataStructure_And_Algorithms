#include<stdio.h>

int BinarySort(int arr[], int n)
{
    int i,j;
    int low,high,m;
    int tmp;
    for(i=1;i<n;i++)
    {
        tmp=arr[i];
        low=0;
        high=i-1;
        while(low<=high)
        {
            m=(low+high)/2;
            if(tmp>arr[m])
                high=m-1;
            else
                low=m+1;
        }

        for(j=i-1;j>=high+1;j--)
        {
            arr[j+1]=arr[j];
        }
        arr[high+1]=tmp;
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

    BinarySort(arr,10);

    printf("after sort:\n");
    for(i=0;i<10;i++)
        printf("[%d] ",arr[i]);
    printf("\n");
    return 0;
}