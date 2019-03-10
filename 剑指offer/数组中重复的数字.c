#include<stdio.h>
#define true 1
#define false 0
int duplicate(int num[], int length, int *duplication)
{
    int i, temp;

    if(num == NULL || length == 0)
    {
        return false;
    }

    for(i = 0; i < length; i++)
    {
        if(num[i] < 0 || num[i] > length-1)
            return false;
    }

    for(i = 0; i < length; i++)
    {
        while(num[i] != i)
        {
            if(num[i] == num[num[i]])
            {
				printf("num[%d]=[%d]\n",i,num[i]);
                *duplication = num[i];
                return true;
            }
            temp = num[i];
            num[i] = num[temp];
            num[temp] = temp;
        }
    }
    return false;
}

/* test */
int main(int argc, char **argv)
{
    int num[] = {2,1,3,1,4};
   //int num[] = {4,3,2,1,0};
    int len = sizeof(num)/sizeof(int);
    int data = -1;
    printf("len=[%d]\n",len);
    if(duplicate(num,len,&data))
        printf("find duplication number:%d\n",data);
    else
        printf("not find duplication\n");

	printf("data=[%d]\n",data);
    return 0;
}