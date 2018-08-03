#include "seqstack.h"
#include<stdlib.h>
#include<stdio.h>

void InitStack(SeqStack *stack)
{
	stack->top= -1;
}

int IsEmpty(SeqStack *stack)
{
	if(stack->top== -1)
	{
		return 1;
	}
	return 0;
}

int SeqStack_Top(SeqStack *stack)
{
	if(!IsEmpty(stack))
	{
		return stack->data[stack->top];
	}
	return INFINITY;		//只是作一个简单标识，有可能栈顶元素也为-1
}

int SeqStack_Pop(SeqStack *stack)
{
	if(!IsEmpty(stack))
	{
		return stack->data[stack->top--];
	}
	return INFINITY;
}

void SeqStack_Push(SeqStack *stack,int val)
{
	if(stack->top >= MAXSIZE-1)
	{
		return;
	}
	stack->top++;
	stack->data[stack->top]=val;
}

void SeqStack_Destory(SeqStack *stack)
{
	if(!IsEmpty(stack))
	{
		free(stack);
	}
}
