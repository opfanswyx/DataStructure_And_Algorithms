void HeapAdjust(int arr[],int i,int n)
{
    int nChild;
    int tmp;
    for(;2*i+1<n;i=nChild)
    {
        nChild=2*i+1;
        if(nChild<n-1 && arr[nChild+1]>arr[nChild])
            ++nChild;

        if(arr[i]<arr[nChild])
        {
            tmp=arr[i];
            arr[i]=arr[nChild];
            arr[nChild]=tmp;
        }
        else 
            break;
    }
}
void HeapSort(int arr[], int n)
{
    int i;
    for(i=(n-1)/2;i>=0;i--)
        HeapAdjust(arr,i,n);
    for(i=n-1;i>0;i--)
    {
        arr[i]=arr[0]^arr[i];
        arr[0]=arr[0]^arr[i];
        arr[i]=arr[0]^arr[i];

        HeapAdjust(arr,0,i);
    }
}