void QuickSort(int arr[],int left,int right)
{
    if(left>=right)
        return;
    
    int i=left;
    int j=right;
    int key=arr[i];
    while(i<j)
    {
        //从右向左找小于key的数
        while((i<j)&&(key<=arr[j]))
        {
            j--;
        }
        arr[i]=arr[j]; //将该数赋给arr[i]

        //从左向右找大于key的数
        while((i<j)&&(key>=arr[i]))
        {
            i++;
        }
        arr[j]=arr[i]; //将该数赋给arr[j]
    }
    arr[i]=key; //将key赋值给arr[i]
    //递归调用key两边的新区间，对新区间在调用快排
    QuickSort(arr,left,i-1); 
    QuickSort(arr,i+1,right);
}