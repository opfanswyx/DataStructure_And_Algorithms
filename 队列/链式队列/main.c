#include<stdio.h>
#include<stdlib.h>
#include "linkqueue.h"
int main()
{
	LQueue Lq=Create();
	srand((unsigned)time(0));
	int i;
	for(i=0;i<10;i++)
	{
		Insert(Lq,rand()%100);
	}
	printf("queue length:%d\n",getLength(Lq));
	printf("queue head num:%d\n",GetHead(Lq));
	printf("队头元素	出队元素\n");
	while(getLength(Lq)>0)
	{
		int ret=GetHead(Lq);
		printf("%d\t\t",ret);
		ret=Del(Lq)->data;
		printf("%d\n",ret);
	}
	Clear(Lq);
	system("pause");
	return 0;
}
