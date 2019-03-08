void HeapAdjust(int arr[], int i, int n)
{
    int nChild;
    int tmp;
    for(;2*i+1<n;i=nChild)
    {
        nChild=2*i+1;  //子节点的位置=2*(父节点位置)+1
        if(nChild<n-1&&arr[nChild+1]>arr[nChild)    //得到子节点中较大的节点
            ++nChild;
        if(arr[i]<arr[nChild])  //如果较大的子节点大于父节点，那么把较大的子节点往上移动，替换它的父节点
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
    //对序列中的每个非叶子节点执行调整算法，使该序列成为一个堆
    for(i=(n-1)/2;i>=0;i--)
        HeapAdjust(arr, i, n);
    //从最后一个元素开始对序列进行调整，不断缩小调整的范围直到第一个元素
    for(i=n-1;i>0;i--)
    {
        //把第一个元素和当前的最后一个元素交换
        //保证当前最后一个位置存放的是现在这个序列中最大的元素
        arr[i]=arr[0]^arr[i];
        arr[0]=arr[0]^arr[i];
        arr[i]=arr[0]^arr[i];
        //不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
        HeapAdjust(arr, 0, i);
    }
}