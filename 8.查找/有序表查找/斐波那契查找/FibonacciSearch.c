int F[]={0,1,1,2,3,5,8,13,21,34,55,89};
int Fibonacci_Search(int *arr,int n,int key)
{
    int begin=0;
    int last=n-1;

    int k=0;
    while(n>F[k]-1)
        ++k;
    
    for(int i=n;i<F[k]-1;i++)
        arr[i]=arr[n-1];
    
    while(begin<=last)
    {
        int mid=begin+F[k-1]-1;
        if(key<arr[mid])
        {
            last=mid-1;
            k-=1;
        }
        else if(key>arr[mid])
        {
            begin=mid+1;
            k-=2;
        }
        else
        {
            if(mid<n)
                return mid;
            else
                return n-1;
        }
    }
    return -1;
}