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