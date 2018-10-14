//
void swap(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
//
void BubbleSort(int arr[], int n)
{
    int i,j;
    for(i=0; i<n-1; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(arr[j]<arr[j+1])
                swap(&arr[j],&arr[j+1]);
        }
    }
}
//优化版optimization
void BubbleSort(int arr[], int n)
{
    int i,j;
    int flag=1;
    for(i=0; i<n-1&&flag;i++)
    {
        flag=0;
        for(j=0; j<n-i-1; j++)
        {
            if(arr[j]<arr[j+1])
            {
                flag=1;
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}
