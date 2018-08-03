#include "seqstack.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	srand((unsigned)time(0));
	SeqStack stack;
	InitStack(&stack);

	int i;
	for(i=0; i<50; i++)
	{
		SeqStack_Push(&stack, rand()%1000);
	}
	printf("stack top num:%d\n",SeqStack_Top(&stack));

	printf("stack nums:\n");
	for(i=0;i<50;i++)
	{
		printf("%d ",SeqStack_Pop(&stack));
		if(i%5==0&&i!=0)
		{
			printf("\n");
		}
	}
	printf("\n");

	system("pause");
	return 0;
}
