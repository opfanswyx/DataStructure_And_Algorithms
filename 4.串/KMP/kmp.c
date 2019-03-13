#include<stdio.h>
int KMP(char *t, char *p, int next[])
{
    int i = 0;
    int j = 0;
    /***********************************************
    *strlen()返回的是无符号的整形，直接比较会出现错误。
    *next数组中存在-1。-1<strlen()实际返回假，我们期待真。
    ************************************************/
    while(i < (int)strlen(t) && j < (int)strlen(p))
    {
        if(j == -1 || t[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if(j == strlen(p))
        return i - j;
    else
        return -1;
}
void getNext(char *p, int *next)
{
    next[0] = -1;
    int i = 0;      /*主串位置*/
    int j = -1;     /*子串位置*/
    while(i < strlen(p))
    {
        if(j == -1 || p[i] == p[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
#if 1   /*调试打印*/
    for(j=0;j<i;j++)
    {
        printf("%d ",next[j]);
    }
    printf("\n");
#endif
}
/* unit test */
int main()
{
    char source[1024],target[100];
    int next[100];
    int ret=0;
    printf("please input source str:\n");
    scanf("%s",source);
    printf("please input target str:\n");
    scanf("%s",target);
    printf("target num next:\n");
    getNext(target,next);
    ret = KMP(source,target,next);
    if(ret==-1)
    {
        printf("no find tagret in source %d\n",ret);
    }
    else
    {
        printf("find tagret in source %d\n",ret);
    }
    return 0;
}