#ifndef _CIRQUEUE_H_
#define _CIRQUEUE_H_

#define MAXSIZE 15
typedef struct Queue* CirQueue;
struct Queue
{
	int front;	//队头
	int rear;	//队尾
	int data[MAXSIZE];
};

CirQueue Create();
int getLength(CirQueue Cq);
int IsEmpty(CirQueue Cq);
void Insert(CirQueue Cq,int val);
int Del(CirQueue Cq);
int GetHead(CirQueue Cq);
void Clear(CirQueue Cq);
void Destory(CirQueue Cq);
#endif
