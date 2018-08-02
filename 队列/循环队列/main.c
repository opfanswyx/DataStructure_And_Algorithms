#include<stdio.h>
#include<stdlib.h>
#include "cirqueue.h"
int main()
{
	CirQueue Cq=Create();
	srand((unsigned)time(0));
	int i;
	for(i=0;i<10;i++)
	{
		Insert(Cq,rand()%100);
	}
	printf("queue length:%d\n",getLength(Cq));
	printf("队头元素        出队元素\n");
	while(Cq->front!=Cq->rear)
	{
		int ret=GetHead(Cq);
		printf("%d\t\t",ret);
		ret=Del(Cq);
		printf("%d\n",ret);
		if(ret==0)
			break;
	}
	printf("queue length:%d\n",getLength(Cq));
	for(i=0;i<10;i++)
	{
		Insert(Cq,rand()%100);
	}
	printf("queue length:%d\n",getLength(Cq));
	printf("队头元素        出队元素\n");
	while(Cq->front!=Cq->rear)
	{
		int ret=GetHead(Cq);
		printf("%d\t\t",ret);
		ret=Del(Cq);
		printf("%d\n",ret);
		if(ret==0)
			break;
	}
	printf("queue length:%d\n",getLength(Cq));
	Clear(Cq);
	Destory(Cq);
	system("pause");
	return 0;
}
