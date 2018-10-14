void QuickSort(int arr[],int left,int right)
{
    if(left>=right)
        return;
    
    int i=left;
    int j=right;
    int key=arr[i];
    while(i<j)
    {
        while((i<j)&&(key<=arr[j]))
        {
            j--;
        }
        arr[i]=arr[j];

        while((i<j)&&(key>=arr[i]))
        {
            i++;
        }
        arr[j]=arr[i];
    }
    arr[i]=key;
    QuickSort(arr,left,i-1);
    QuickSort(arr,i+1,right);
}