void SelectSort(int arr[], int n)
{
    int i,j,max;
    for(i=0;i<n;i++)
    {
        max=i;
        for(j=i;j<n;j++)
        {
            if(arr[max]<arr[j])
                max=j;
        }
        if(i!=max)
            swap(&arr[i],&arr[max]);
    }
}