#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_

#define MAXSIZE 1024
#define INFINITY 65535
typedef struct
{
	int data[MAXSIZE];
	int top;			//指示栈定元素，在数组中相当于索引
}SeqStack;

void InitStack(SeqStack *stack);
int IsEmpty(SeqStack *stack);
int SeqStack_Top(SeqStack *stack);
int SeqStack_Pop(SeqStack *stack);
void SeqStack_Push(SeqStack *stack,int val);
void SeqStack_Destory(SeqStack *stack);
#endif
