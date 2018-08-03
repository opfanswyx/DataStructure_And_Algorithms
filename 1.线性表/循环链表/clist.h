#ifndef _CLIST_H_
#define _CLIST_H_
struct Node;
typedef struct Head* pHead;
typedef struct Node* pNode;

struct Head
{
	int length;
	pNode next;
};

struct Node
{
	int data;
	pNode next;
};
pHead ClistCreate();
int getLength(pHead ph);
int IsEmpty(pHead ph);
int ClistInsert(pHead ph,int pos,int val);
void print(pHead ph);
#endif