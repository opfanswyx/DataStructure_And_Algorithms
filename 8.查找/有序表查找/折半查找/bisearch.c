//非递归版
int BiSearch(int arr[],const int num,int begin,int last)
{
    int mid;
    if(begin>last)
        return -1;
    
    while(begin<=last)
    {
        mid=(begin+last)/2;
        if(num==arr[mid])
            return mid;
        else if(arr[mid]<num)
            begin=mid+1;
        esle if(arr[mid]>num)
            last=mid-1;
    }
    return -1;
}
//递归版
int IterBiSearch(int arr[],const int num,int begin,int last)
{
    int mid=-1;
    mid=(begin+last)/2;
    if(num==arr[mid])
        return mid;
    else if(num<arr[mid])
        return IterBiSearch(arr,num,begin,mid-1);
    else if(num>arr[mid])
        return IterBiSearch(arr,num,mid+1,last);
    return -1;
}