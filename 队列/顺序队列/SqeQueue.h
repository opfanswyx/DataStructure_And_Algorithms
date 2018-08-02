#ifndef _SQQUEUE_H_
#define _SQQUEUE_H_

#define MAXSIZE 50
typedef struct Queue* SeqQueue;
struct Queue
{
	int front;	//队头
	int rear;	//队尾
	int data[MAXSIZE];
};

SeqQueue Create();
int getLength(SeqQueue Sq);
int IsEmpty(SeqQueue Sq);
void Insert(SeqQueue Sq,int val);
int Del(SeqQueue Sq);
int GetHead(SeqQueue Sq);
void Clear(SeqQueue Sq);
void Destory(SeqQueue Sq);
#endif
