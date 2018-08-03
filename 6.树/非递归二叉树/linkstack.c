#include"linkstack.h"
#include<stdio.h>
#include<stdlib.h>

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
	if(lstack->top==NULL||lstack->size==0)
	{
		return 1;
	}
	return 0;
}

int Push(LinkStack lstack,BitNode *val)
{
	pNode node=(pNode)malloc(sizeof(struct Node));
	if(node !=NULL)
	{
		node->data=val;
		node->next=getTop(lstack);
		lstack->top=node;
		lstack->size++;
	}
	return 1;
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
