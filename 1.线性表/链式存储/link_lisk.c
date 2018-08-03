#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "link_list.h"

//创建链表
pHead *createList()				//pHead是struct Header的别名，是头结点类型
{
	pHead *ph=(pHead*)malloc(sizeof(pHead));	//为头节点分配内存
	ph->length=0;								//为头结点初始化
	ph->next=NULL;
	return ph;					//返回头结点地址
}
//获取链表大小
int Size(pHead *ph)
{
	if(ph==NULL)
	{
		printf("ph==NULL\n");
		return 0;
	}
	return ph->length;
}
int Insert(pHead *ph,int pos, int val)	//在某个位置插入某个元素，插入成功返回1
{
	//先做健壮性判断
	if(ph==NULL || pos<0 || pos >ph->length)
	{
		printf("error\n");
		return 0;
	}
	List* pval=(List *)malloc(sizeof(List));
	pval->data=val;
	List *pCur=ph->next;
	if(pos==0)
	{
		ph->next=pval;
		pval->next=pCur;
	}
	else
	{
		int i;
		for(i=1;i<pos;i++)
		{
			pCur=pCur->next;
		}
		pval->next=pCur->next;
		pCur->next=pval;
	}
	ph->length++;
	return 1;
}
//查找某个元素
List *find(pHead *ph,int val)
{
	//先做健壮性判断
	if(ph==NULL)
	{
		printf("error\n");
		return NULL;
	}
	//遍历链表来查找元素
	List *pTmp=ph->next;
	do
	{
		if(pTmp->data==val)
		{
			return pTmp;
		}
		pTmp=pTmp->next;
	}while(pTmp->next!=NULL);
	printf("no find %d data\n",val);
	return NULL;
}
//删除元素
List *Delete(pHead *ph,int val)
{
	//先做健壮性判断
	if(ph==NULL)
	{
		printf("ph==NULL\n");
		return NULL;
	}
	List *pval=find(ph,val);
	if(pval==NULL)
	{
		printf("not find %d\n",val);
	}

	//遍历链表找到要删除的结点，并找出其前驱及后继结点
	List *pRe=ph->next;		//当前结点
	List *pCur=NULL;
	if(pRe->data==val)		//第一个结点
	{
		ph->next=pRe->next;
		ph->length--;
		return pRe;
	}
	else			//其它结点
	{
		int i;
		for(i=0;i<ph->length;i++)
		{
			pCur=pRe->next;
			if(pCur->data==val)
			{
				pRe->next=pCur->next;
				ph->length--;
				return pCur;
			}
			pRe=pRe->next;
		}
	}
}
//销毁链表
void Destory(pHead *ph)
{
	List *pCur=ph->next;
	List *pTmp;
	if(ph==NULL)
	{
		printf("error\n");
	}
	while(pCur->next != NULL)
	{
		pTmp=pCur->next;
		free(pCur);
		pCur=pTmp;
	}
	ph->length=0;
	ph->next=NULL;
}
//遍历打印链表
void print(pHead *ph)
{
	if(ph==NULL)
	{
		printf("ph==NULL\n");
	}
	List *pTmp=ph->next;
	while(pTmp!=NULL)
	{
		printf("%d	",pTmp->data);
		pTmp=pTmp->next;
	}
	printf("\n");
}
