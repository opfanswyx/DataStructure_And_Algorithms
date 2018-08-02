#define _CRT_SECURE_NO_WARNINGA
#include "link_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int ret;
	pHead *ph=createList();
	if(ph==NULL)
	{
		printf("error\n");
	}
	int arr[10]={1,2,3,4,5,6,7,8,9,10};
	int i;
	for(i=0;i<10;i++)
	{
		Insert(ph, 0, arr[i]);
	}
	printf("link length %d\n",Size(ph));

	printf("print link_list ele:\n");
	print(ph);
	printf("please input delete link ele:\n");
	int num;
	scanf("%d",&num);
	Delete(ph,num);
	printf("delete over,print link\n");
	print(ph);

	ret=find(ph,3);
	if(ret)
	{
		printf("get!\n");
	}
	else
	{
		printf("no!\n");
	}
	system("pause");
	return 0;
}
