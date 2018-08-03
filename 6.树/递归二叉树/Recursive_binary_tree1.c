#include<stdio.h>
#include<stdlib.h>
typedef struct BitNode
{
	char data;
	struct BitNode *lchild,*rchild;
}BitNode;
//先序遍历
void preOrder(BitNode *T)
{
	if(T==NULL)
		return;
	printf("%c",T->data);
	if(T->lchild != NULL)
		preOrder(T->lchild);
	if(T->rchild!=NULL)
		preOrder(T->rchild);
}
//中序遍历
void inOrder(BitNode *T)
{
	if(T==NULL)
		return;
	if(T->lchild != NULL)
		inOrder(T->lchild);
	printf("%c",T->data);
	if(T->rchild!=NULL)
		inOrder(T->rchild);
}
//后序遍历
void lastOrder(BitNode *T)
{
	if(T==NULL)
		return;

	if(T->lchild != NULL)
		lastOrder(T->lchild);
	if(T->rchild!=NULL)
		lastOrder(T->rchild);
	printf("%c",T->data);
}
int sum=0;
void getLeafNum(BitNode *T)
{
	//int sum;
	if(T==NULL)
		return;
	if(T->lchild==NULL && T->rchild==NULL)
		sum++;
	getLeafNum(T->lchild);
	getLeafNum(T->rchild);
}

int Depth(BitNode *T)
{
	int depth=0;
	int dleft=0,dright=0;
	if(T==NULL)
		return 0;
	dleft=Depth(T->lchild);
	dright=Depth(T->rchild);
	return 1+(dleft>dright ? dleft:dright);
}

BitNode *copyTree(BitNode *T)
{
	BitNode *newT=(BitNode*)malloc(sizeof(BitNode));
	BitNode *newlchild=NULL;
	BitNode *newrchild=NULL;
	if(newT==NULL)
		return NULL;
	if(T==NULL)
		return NULL;
	newlchild=copyTree(T->lchild);
	newrchild=copyTree(T->rchild);
	newT->data=T->data;
	newT->lchild=newlchild;
	newT->rchild=newrchild;
	return newT;

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
	printf("先序遍历:");
	preOrder(&nodeA);
	printf("\n中序遍历:");
	inOrder(&nodeA);
	printf("\n后序遍历:");
	lastOrder(&nodeA);
	printf("\n");
	getLeafNum(&nodeA);
	printf("tree node:%d\n",sum);
	printf("tree depth:%d\n",Depth(&nodeA));
	sum=0;
	new=copyTree(&nodeA);
	printf("copy BiTree succes\n");
	printf("先序遍历:");
	preOrder(new);
	printf("\n中序遍历:");
	inOrder(new);
	printf("\n后序遍历:");
	lastOrder(new);
	printf("\n");
	getLeafNum(new);
	printf("tree node:%d\n",sum);
	printf("tree depth:%d\n",Depth(new));

	system("pause");
	return 0;
}
