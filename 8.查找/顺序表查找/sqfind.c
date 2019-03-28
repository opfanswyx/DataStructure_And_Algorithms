int sq_find(int arr[], int n, int key)
{
    /* 在for循环中，算法近乎一半的时间消耗在数组的边界检查上面 */
    for(int i=0;i<n;i++) 
    {
        if(arr[i]==key)
            return i;
    }
    return -1;
}

int sq_find(int arr[], int n, int key)
{
    int i=n;
    arr[0]=key;     /* arr[0]设置为监视哨兵 */
    while(arr[i]!=key)
        i--;
    return i;
}