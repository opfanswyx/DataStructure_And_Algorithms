#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_
#include<stdio.h>
#include<stdlib.h>
typedef struct Node *pNode;
typedef struct Stack *LinkStack;

struct Node
{
	int data;
	pNode next;
};

struct Stack		//此结构记录栈的大小和栈顶元素指针
{
	pNode top;
	int size;
};

LinkStack Create();
int IsEmpty(LinkStack lstack);
int getSize(LinkStack lstack);
int Push(LinkStack lstack,int val);
pNode getTop(LinkStack lstack);
pNode Pop(LinkStack lstack);
void Destory(LinkStack lstack);
#endif