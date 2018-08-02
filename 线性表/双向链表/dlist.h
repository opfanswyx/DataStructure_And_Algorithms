#ifndef _DLIST_H_
#define _DLIST_H_

struct Node;
typedef struct Head *pHead;
typedef struct Node *pNode;
//定义头结点
struct Head
{
	int length;
	pNode next;

};
//定义数据节点
struct Node
{
	int data;
	pNode pre;
	pNode next;
};
pHead DlistCreate();
int getLength(pHead ph);
int IsEmpty(pHead ph);
int DlistInsert(pHead ph, int pos, int val);
pNode DlistDelete(pHead ph, int val);
pNode DlistFind(pHead ph, int val);
void DlistDestory(pHead ph);
void printFront(pHead ph);
void printLast(pHead ph);
#endif