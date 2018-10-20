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
        arr[high+1]=temp;
    }
}