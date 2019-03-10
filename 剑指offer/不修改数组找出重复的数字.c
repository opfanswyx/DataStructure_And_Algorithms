#include<stdio.h>
#define false -1
#define true 0
int countRange(const int *num, const int length, int start, int end)
{
    int i;
    int count = 0;
    if(num == NULL)
        return 0;
    for(i = 0; i < length; i++)
        if(num[i] >= start && num[i] <= end)    /* 统计start到end范围里的数的个数 */
            count++;
    return count;
}

int getDuplication(const int *num, const int length)
{
    if(num == NULL || length <= 0)
        return false;
    int start = 1;
    int end = length - 1;
    while(end >= start)
    {
        int middle = ((end - start) >> 1) + start;
        int count = countRange(num, length, start, middle);
        if(end == start)
        {
            if(count > 1)
                return start;
            else
                break;
        }
        if(count > (middle - start + 1))    /* 如果count比范围大，则说明范围里有重复数据 */
            end = middle;    
        else    
            start = middle + 1;
    }
    return false;
}

int main(int argc, char **argv)
{
    int num[] = {2,3,5,4,3,2,6,7};
    int len = sizeof(num)/sizeof(int);
    int ret = -1;
    ret = getDuplication(num,len);
    if(ret != -1)
        printf("find Duplication [%d]\n",ret);
    else
        printf("not find\n");
    return 0;
}