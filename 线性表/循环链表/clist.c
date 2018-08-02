#include "clist.h"
#include<stdio.h>
#include<stdlib.h>
pHead ClistCreate()
{
	pHead ph=(pHead)malloc(sizeof(struct Head));
	if(ph==NULL)
	{
		printf("malloc error\n");
	}
	ph->length=0;
	ph->next=NULL;
	return ph;
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
int ClistInsert(pHead ph,int pos,int val)
{
	if(ph==NULL || pos<0 || pos>ph->length)
	{
		printf("error\n");
	}
	pNode pval=NULL;
	pval=(pNode)malloc(sizeof(struct Node));
	pval->data=val;
	if(IsEmpty(ph))
	{
		ph->next=pval;
		pval->next=pval;	//将第一个结点执行它自己
	}
	else
	{
		pNode pRear=ph->next;
		if(pos==0)				//在头结点后插入
		{
			while(pRear->next!=ph->next)	//在0号位置插入，需要先找到尾结点位置
			{
				pRear=pRear->next;
			}
			pval->next=ph->next;
			ph->next=pval;
			pRear->next=pval;	//这三个步骤不能改
		}
		else
		{
			pNode pCur=ph->next;
			int i;
			for(i=1;i<pos;i++)
			{
				pCur=pCur->next;
			}
			pval->next=pCur->next;
			pCur->next=pval;
		}
	}
	ph->length++;
	return 1;
}
void print(pHead ph)
{
	if(ph==NULL || ph->length==0)
	{
		printf("error\n");
	}
	pNode pTmp=ph->next;
	int i;
	for(i=0;i<ph->length;i++)
	{
		printf("%d ",pTmp->data);
		pTmp=pTmp->next;
	}
	printf("\n");
}
