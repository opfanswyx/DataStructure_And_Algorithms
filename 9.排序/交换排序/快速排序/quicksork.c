#include<stdio.h>

void QuickSort(int arr[],int left,int right)
{
    if(left>=right)
        return;
    
    int i=left;
    int j=right;
    int key=arr[i];
    while(i<j)
    {
        //这里只能是'<=或>=',因为当key=arr[i]=arr[j]时会出问题，故快排是不稳定算法
        //从右向左找小于key的数
        while((i<j)&&(key<=arr[j]))
        {
            j--;
        }
        arr[i]=arr[j]; //将该数赋给arr[i]

        //从左向右找大于key的数
        while((i<j)&&(key>=arr[i]))
        {
            i++;
        }
        arr[j]=arr[i]; //将该数赋给arr[j]
    }
    arr[i]=key; //将key赋值给arr[i]
    //递归调用key两边的新区间，对新区间在调用快排
    QuickSort(arr,left,i-1); 
    QuickSort(arr,i+1,right);
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

    QuickSort(arr,0,9);

    printf("after sort:\n");
    for(i=0;i<10;i++)
        printf("[%d] ",arr[i]);
    printf("\n");
    return 0;
}