#include"cirqueue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

CirQueue Create()
{
	CirQueue Cq=(CirQueue)malloc(sizeof(struct Queue));
	Cq->front=Cq->rear=-1;
	memset(Cq->data,0,MAXSIZE *sizeof(int));
	return Cq;
}

int getLength(CirQueue Cq)
{
	return Cq->rear-Cq->front;
}

int IsEmpty(CirQueue Cq)
{
	if(Cq->front=Cq->rear)		//判断是否为空条件
	{
		return 1;
	}
	return 0;
}
//数组前边是对头，后边是队尾
void Insert(CirQueue Cq, int val)
{
	if((Cq->rear+1)%MAXSIZE==Cq->front)	//队列满
	{
		printf("seqqueue is full\n");
		return;
	}
	if(Cq->front==Cq->rear)		//队列为空
	{
		Cq->front=Cq->rear=0;
		Cq->data[Cq->rear]=val;
		Cq->rear++;
	}
	else
	{
		Cq->data[Cq->rear]=val;
		Cq->rear=(Cq->rear+1)%MAXSIZE;
	}
}

int Del(CirQueue Cq)
{
	if(Cq->front==Cq->rear)
	{
		printf("squeue is empty\n");
		return 1;
	}
	int temp=Cq->data[Cq->front];
	Cq->front=(Cq->front+1)%MAXSIZE;		//删除头元素，后移
	return temp;
}
int GetHead(CirQueue Cq)
{
	if(Cq->front==Cq->rear)
	{
		printf("seqqueue is empty\n");
		return 1;
	}
	return Cq->data[Cq->front];
}

void Clear(CirQueue Cq)
{
	Cq->front=Cq->rear=-1;
	printf("queue is clear over\n");
}

void Destory(CirQueue Cq)
{
	free(Cq);
	printf("Destory over\n");
}
