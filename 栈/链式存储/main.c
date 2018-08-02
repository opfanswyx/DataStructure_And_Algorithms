#include<stdio.h>
#include<stdlib.h>
#include "linkstack.h"

int main()
{
	srand((unsigned)time(0));
	LinkStack lstack=NULL;
	lstack=Create();

	int ret;
	ret=IsEmpty(lstack);
	if(ret)
	{
		printf("stack empty\n");
	}
	else
	{
		printf("stack not empty\n");
	}
	int i;
	for(i=0;i<10;i++)
	{
		Push(lstack,rand()%100);
	}

	ret=IsEmpty(lstack);
	if(ret)
	{
		printf("stack empty\n");
	}
	else
	{
		printf("stack not empty\n");
	}

	printf("stack length:%d\n", getSize(lstack));

	printf("stack top num:%d\n",*((int*)getTop(lstack)));

	while(lstack->size>0)
	{
		printf("%d ",*((int*)Pop(lstack)));
	}
	printf("\n");

	Destory(lstack);
	system("pause");
	return 0;
}
