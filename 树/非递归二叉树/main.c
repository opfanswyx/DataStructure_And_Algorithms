#include<stdio.h>
#include<stdlib.h>
#include"linkstack.h"
BitNode *GoFarLeft(BitNode *T,LinkStack ls)
{
	if(T==NULL)
		return NULL;
	while(T->lchild!=NULL)	//左子树不为空，就一直往下寻找
	{
		Push(ls,T);
		T=T->lchild;
	}
	return T;
}

void MyOrder(BitNode *T)
{
	LinkStack ls=Create();
	BitNode *t=GoFarLeft(T,ls);
	while(t!=NULL)
	{
		printf("%c",t->data);
		if(t->rchild!=NULL)
			t=GoFarLeft(t->rchild,ls);
		else if(!IsEmpty(ls))
		{
			t=getTop(ls)->data;
			Pop(ls);
		}
		else
		{
			t=NULL;
		}
	}
}

int main()
{
	BitNode nodeA,nodeB,nodeD,nodeF,nodeI,nodeL;
	BitNode *new;
	memset(&nodeA,0,sizeof(BitNode));
	memset(&nodeB,0,sizeof(BitNode));
	memset(&nodeD,0,sizeof(BitNode));
	memset(&nodeF,0,sizeof(BitNode));
	memset(&nodeI,0,sizeof(BitNode));
	memset(&nodeL,0,sizeof(BitNode));

	nodeA.data='A';
	nodeB.data='B';
	nodeD.data='D';
	nodeF.data='F';
	nodeI.data='I';
	nodeL.data='L';

	nodeA.lchild=&nodeB;
	nodeA.rchild=&nodeD;
	nodeB.rchild=&nodeF;
	nodeF.lchild=&nodeL;
	nodeD.lchild=&nodeI;

	printf("BiTree bulid succes\n");

	printf("非递归中序遍历:");
	MyOrder(&nodeA);
	printf("\n");

	system("pause");
	return 0;
}
