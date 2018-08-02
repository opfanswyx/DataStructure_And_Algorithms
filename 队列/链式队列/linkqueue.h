#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

typedef struct Node* pNode;
typedef struct Queue* LQueue;
struct Node
{
	int data;
	pNode next;
};

struct Queue
{
	pNode front;
	pNode rear;
	int length;
};

LQueue Create();
int getLength(LQueue Lq);
int IsEmpty(LQueue Lq);
void Insert(LQueue Lq, int val);
int GetHead(LQueue Lq);
pNode Del(LQueue Lq);
void Clear(LQueue Lq);
#endif
