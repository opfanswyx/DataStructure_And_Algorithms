void Shellsort(int arr[], int n)
{
    int i,j,d;
    int tmp;
    d=n/2; //d为步长
    while(d>0)
    {
        for(i=d;i<n;i++) //d=n-d组，共d组，对每一组进行直接插入排序
        {
            tmp=arr[i];
            j=i-d;
            while(j>=0&&tmp>arr[j])
            {
                arr[j+d]=arr[j];
                j=j-d;
            }
            arr[j+d]=tmp;
        }
        d=d/2;
    }
}