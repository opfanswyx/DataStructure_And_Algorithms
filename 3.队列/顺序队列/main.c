#include<stdio.h>
#include<stdlib.h>
#include "seqqueue.h"
int main()
{
	SeqQueue Sq=Create();
	srand((unsigned)time(0));
	int i;
	for(i=0;i<10;i++)
	{
		Insert(Sq,rand()%100);
	}
	printf("queue length:%d\n",getLength(Sq));
	printf("队头元素        出队元素\n");
	while(Sq->front!=Sq->rear)
	{
		int ret=GetHead(Sq);
		printf("%d\t\t",ret);
		ret=Del(Sq);
		printf("%d\n",ret);
	}
	printf("queue length:%d\n",getLength(Sq));
	Clear(Sq);
	Destory(Sq);
	system("pause");
	return 0;
}
