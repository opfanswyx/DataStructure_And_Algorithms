#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_
typedef struct BitNode
{
	char data;
	struct BitNode *lchild,*rchild;
}BitNode;
//栈的结构
typedef struct Node *pNode;
typedef struct Stack *LinkStack;
struct Node
{
	BitNode *data;	//数据，BitNode结构体类型的指针
	pNode next;		//指针
};
struct Stack
{
	pNode top;		//栈顶元素
	int size;		//栈大小
};

LinkStack Create();
int IsEmpty(LinkStack lstack);
int Push(LinkStack lstack, BitNode *val);
pNode getTop(LinkStack lstack);
pNode Pop(LinkStack lstack);
#endif