#define _CRT_SECURE_NO_WARNINGS
#include "dlist.h"
#include<stdio.h>
#include<stdlib.h>
int main()
{
	pHead ph = NULL;
	ph=DlistCreate();

	int num;
	printf("请输入要插入的元素，输入0结束:\n");
	while(1)
	{
		scanf("%d",&num);
		if(num==0)
		{
			break;
		}
		DlistInsert(ph,0,num);
	}
	printf("双链表的长度:%d\n",getLength(ph));
	printFront(ph);
	DlistInsert(ph,3,99);
	printFront(ph);
	printLast(ph);

	int val;
	printf("请输入要查找的元素:\n");
	scanf("%d",&val);
	DlistFind(ph,val);

	int del;
	printf("请输入要删除的元素:\n");
	scanf("%d",&del);
	DlistDelete(ph,del);
	printFront(ph);

	DlistDestory(ph);
	printf("destory scuuess!length:%d\n",ph->length);
	system("pause");
	return 0;
}
