#include<stdio.h>
#include<stdlib.h>
#include "dlist.h"

pHead DlistCreate()
{
	pHead ph = (pHead)malloc(sizeof(struct Head));
	if(ph == NULL)
	{
		printf("malloc ph error\n");
	}
	ph->length=0;
	ph->next=NULL;
	return ph;
}

int getLength(pHead ph)
{
	if(ph==NULL)
	{
		printf("error\n");
	}
	return ph->length;
}

int IsEmpty(pHead ph)
{
	if(ph==NULL)
	{
		printf("error\n");
	}
	if(ph->length==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int DlistInsert(pHead ph, int pos, int val)
{
	pNode pval=NULL;
	if(ph==NULL||pos<0||pos>ph->length)
	{
		printf("error\n");
	}
	//如果参数无误，为元素分配结点空间
	pval =(pNode)malloc(sizeof(struct Node));
	pval->data=val;
	//判断在哪个位置插入，先判断链表是否为空
	if(IsEmpty(ph))
	{
		ph->next=pval;		//直接将结点插入头结点后
		pval->next=NULL;
		pval->pre=NULL;		//第一个结点不回指头结点
	}
	else
	{
		pNode pCur=ph->next;
		if(pos==0)		//在第一个位置(头结点后)插入
						//与链表为空的区别在与链表不空且在0位置插入
		{
			ph->next=pval;
			pval->pre=NULL;
			pval->next=pCur;
			pCur->pre=pval;
		}
		else
		{
			int i;
			for(i=1; i<pos; i++)	//i!=0因为pos=0做了特殊的处理
			{
				pCur=pCur->next;
			}
			//循环结束，此时pCur指向的是要插入的位置
			pval->next=pCur->next;
			pCur->next->pre=pval;
			pval->pre=pCur;
			pCur->next=pval;
		}
	}
	ph->length++;
	return 1;
}
pNode DlistDelete(pHead ph, int val)
{
	if(ph==NULL || ph->length==0)
	{
		printf("error\n");
	}
	pNode pval=DlistFind(ph,val);
	if(pval==NULL)
	{
		return NULL;
	}
	printf("Delete it\n");
	pNode pRe=pval->pre;
	pNode pNext=pval->next;

	pRe->next=pNext;
	pNext->pre=pRe;
	return pval;
}
pNode DlistFind(pHead ph, int val)
{
	if(ph==NULL)
	{
		printf("error\n");
	}
	pNode pTmp=ph->next;
	do
	{
		if(pTmp->data==val)
		{
			printf("get it\n");
			return pTmp;
		}
		pTmp=pTmp->next;

	}while(pTmp->next!=NULL);
	printf("not find\n");
	return NULL;
}
void DlistDestory(pHead ph)
{
	pNode pCur=ph->next;
	pNode pTmp;
	if(ph==NULL)
	{
		printf("error\n");
	}
	while(pCur->next!=NULL)
	{
		pTmp=pCur->next;
		free(pCur);
		pCur=pTmp;
	}
	ph->length=0;
	ph->next=NULL;
}
//从前打印
void printFront(pHead ph)
{
	if(ph==NULL)
	{
		printf("error\n");
	}
	pNode pTmp=ph->next;
	while(pTmp!=NULL)
	{
		printf("%d ",pTmp->data);
		pTmp=pTmp->next;
	}
	printf("\n");
}
//从后打印
void printLast(pHead ph)
{
	if(ph==NULL)
	{
		printf("error\n");
	}
	pNode pTmp=ph->next;
	while(pTmp->next!=NULL)
	{
		pTmp=pTmp->next;
	}
	int i;
	for(i=--ph->length;i>=0;i--)
	{
		printf("%d ",pTmp->data);
		pTmp=pTmp->pre;
	}
	printf("\n");
}