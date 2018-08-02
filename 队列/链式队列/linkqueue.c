#include "linkqueue.h"
#include<stdio.h>
#include<stdlib.h>
LQueue Create()
{
	LQueue Lq=(LQueue)malloc(sizeof(struct Queue));
	Lq->front=NULL;
	Lq->rear=NULL;
	Lq->length=0;
}
int getLength(LQueue Lq)
{
	return Lq->length;
}

int IsEmpty(LQueue Lq)
{
	if(Lq->length==0)
	{
		return 1;
	}
	return 0;
}

void Insert(LQueue Lq,int val)
{
	pNode pn=(pNode)malloc(sizeof(struct Node));
	pn->data=val;
	pn->next=NULL;

	if(IsEmpty(Lq))
	{
		Lq->front=pn;
		Lq->rear=pn;
	}
	else
	{
		Lq->rear->next=pn;
		Lq->rear=pn;	//移动rear指针指向最后一个元素
	}
	Lq->length++;
}
int GetHead(LQueue Lq)
{
	if(IsEmpty(Lq))
	{
		printf("queue is empty\n");
		return 1;
	}
	return Lq->front->data;
}
pNode Del(LQueue Lq)
{
	if(IsEmpty(Lq))
	{
		printf("queue is emtpy\n");
		return NULL;
	}
	pNode pTmp=Lq->front;
	Lq->front=pTmp->next;
	Lq->length--;
	return pTmp;
}

void Clear(LQueue Lq)
{
	Lq->front=NULL;
	Lq->rear=NULL;
	Lq->length=0;
	printf("queue have clear over\n");
}
