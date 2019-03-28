
#include "linkstack.h"

LinkStack Create()
{
	LinkStack lstack=(LinkStack)malloc(sizeof(struct Stack));
	if(lstack!=NULL)
	{
		lstack->top=NULL;
		lstack->size=0;
	}
	return lstack;
}

int IsEmpty(LinkStack lstack)
{
	if(lstack->top==NULL || lstack->size==0)
	{
		return 1;
	}
	return 0;
}

int getSize(LinkStack lstack)
{
	return lstack->size;
}

int Push(LinkStack lstack,int val)
{
	pNode node=(pNode)malloc(sizeof(struct Node));
	if(node != NULL)
	{
		node->data=val;
		node->next=getTop(lstack);		//新元素结点指向下一个结点
		lstack->top=node;
		lstack->size++;
	}
}

pNode getTop(LinkStack lstack)
{
	if(lstack->size!=0)
	{
		return lstack->top;
	}
	return NULL;
}

pNode Pop(LinkStack lstack)
{
	if(IsEmpty(lstack))
	{
		return NULL;
	}
	pNode node=lstack->top;
	lstack->top=lstack->top->next;
	lstack->size--;
	return node;
}

void Destory(LinkStack lstack)
{
	if(IsEmpty(lstack))
	{
		free(lstack);
		return;
	}
	do
	{
		pNode pTmp;
		pTmp=Pop(lstack);
		free(pTmp);
	}while(lstack->size>0);
	printf("Destory susess\n");
}
