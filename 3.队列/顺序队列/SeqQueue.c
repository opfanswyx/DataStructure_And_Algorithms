#include"seqqueue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

SeqQueue Create()
{
	SeqQueue Sq=(SeqQueue)malloc(sizeof(struct Queue));
	Sq->front=Sq->rear=-1;
	memset(Sq->data,0,MAXSIZE *sizeof(int));
	return Sq;
}
int getLength(SeqQueue Sq)
{
	return Sq->rear-Sq->front;
}
int IsEmpty(SeqQueue Sq)
{
	if(Sq->front=Sq->rear)		//判断是否为空条件
	{
		return 1;
	}
	return 0;
}
//数组前边是对头，后边是队尾
void Insert(SeqQueue Sq, int val)
{
	if(Sq->rear==MAXSIZE-1)
	{
		printf("seqqueue is full\n");
		return;
	}
	if(Sq->front==Sq->rear)
	{
		Sq->front=Sq->rear=0;
		Sq->data[Sq->rear]=val;
		Sq->rear++;
	}
	else
	{
		Sq->data[Sq->rear]=val;
		Sq->rear++;
	}
}

int Del(SeqQueue Sq)
{
	if(Sq->front==Sq->rear)
	{
		printf("squeue is empty\n");
		return 1;
	}
	int temp=Sq->data[Sq->front];
	Sq->front++;		//删除头元素，后移
	return temp;
}
int GetHead(SeqQueue Sq)
{
	if(Sq->front==Sq->rear)
	{
		printf("seqqueue is empty\n");
		return 1;
	}
	return Sq->data[Sq->front];
}

void Clear(SeqQueue Sq)
{
	Sq->front=Sq->rear=-1;
	printf("queue is clear over\n");
}

void Destory(SeqQueue Sq)
{
	free(Sq);
	printf("Destory over\n");
}
