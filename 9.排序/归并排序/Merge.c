void Merge(int arr[],int tmp[],int start,int mid,int end)
{
    int i=start,j=mid+1,k=start;
    while(i!=mid+1 && j!=end+1)
    {
        if(arr[i]>=arr[j])
            tmp[k++]=arr[j++];
        else
            tmp[k++]=arr[i++];
    }
    while(i!=mid+1)
        tmp[k++]=arr[i++];
    while(j!=end+1)
        tmp[k++]=arr[j++];
    for(i=start;i<end;i++)
        arr[i]=tmp[i];
}

void MergeSort(int arr[],int tmp[],int start,int end)
{
    int mid;
    if(start<end)
    {
        mid=(start+end)/2;
        MergeSort(arr,tmp,start,mid);
        MergeSort(arr,tmp,mid+1,end);
        Merge(arr,tmp,start,mid,end);
    }
}