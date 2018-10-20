void InsertSort(int arr[], int n)
{
    int i,j;
    for(i=1;i<n;i++)
    {
        int tmp=arr[i];
        if(tmp>arr[i-1])
        {
            for(j=i-1;j>=0&&tmp>arr[j];j--)
            {
                arr[j+1]=arr[j];
            }
            arr[j+1]=tmp;
        }
    }
}