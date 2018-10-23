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
void BubbleSort(int arr[], int n)
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
