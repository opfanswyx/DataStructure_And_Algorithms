#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "SeqList.h"
//创建顺序表
SeqList *SeqList_Create(int capacity)	//返回值为SeqList*类型，即顺序表的地址
{
	int ret;
	TSeqList *temp=NULL;
	temp=(TSeqList*)malloc(sizeof(TSeqList)); 	//为头节点分配地址
	if(temp==NULL)
	{
		ret=1;
		printf("func SeqList_Create() error:%d\n",ret);
		return NULL;
	}
	memset(temp, 0, sizeof(TSeqList));
	temp->capacity=capacity;
	temp->length=0;
	temp->node=(int*)malloc(sizeof(void*)*capacity);	//分配一个指针数组	char**malloc(sizeof(char*)*capacity)
	if(temp->node==NULL)
	{
		ret=2;
		printf("func SeqList_Create() error:%d\n",ret);
		return NULL;
	}
	return temp;
}
//求顺序表容量
int SeqList_Capacity(SeqList *list)
{
	TSeqList *temp=NULL;
	if(list==NULL)
	{
		return;
	}
	temp=(TSeqList *)list;
	return temp->capacity;
}
//获取顺序表长度
int SeqList_Length(SeqList *list)
{
	TSeqList *temp=NULL;
	if(list==NULL)
	{
		return;
	}
	temp=(TSeqList *)list;
	return temp->length;
}
//插入元素
int SeqList_Insert(SeqList *list,SeqListNode *node,int pos)
{
	int i;
	TSeqList *temp=NULL;
	if(list==NULL || node==NULL)	//健壮性判断
	{
		return -1;
	}
	temp=(TSeqList *)list;
	if(temp->length >= temp->capacity)	//如果顺序表已满
	{
		return -2;
	}
	//容错
	if(pos >temp->length)		//如果给出的pos位置在线性表长度之后，即中间有空余
	{
		pos=temp->length;		//就修正到最后一个元素后面
	}
	for(i=temp->length;i>pos;i--)	//将插入元素后的元素依次后移
	{
		temp->node[i]=temp->node[i-1];
	}
	temp->node[i]=(SeqListNode *)node;	//腾出的位置插入新元素
	temp->length++;				//插入成功后，长度加1
	return 0;
}
//删除元素
SeqList *SeqList_Delete(SeqList *list, int pos)
{
	int i;
	TSeqList *tlist=NULL;
	SeqListNode *temp=NULL;
	tlist=(TSeqList*)list;
	if(list==NULL || pos<0 || pos>=tlist->capacity)
	{
		printf("SeqList_Detele() error\n");
		return NULL;
	}
	temp=(SeqListNode*)tlist->node[pos];	//要删除的元素
	for(i=pos+1;i<tlist->length;i++)
	{
		tlist->node[i-1]=tlist->node[i];
	}
	tlist->length--;
	return temp;
}
//查找元素
SeqList *SeqList_Get(SeqList *list, int pos)
{
	TSeqList *tlist=NULL;
	SeqListNode *temp=NULL;
	tlist=(TSeqList *)list;
	if(list==NULL || pos<0 || pos>=tlist->capacity)
	{
		printf("SeqList_Get() error\n");
		return NULL;
	}
	temp=(SeqListNode *)tlist->node[pos];	//将表中pos位置的结点指针赋给temp
	return temp;
}
//清空顺序表
void SeqList_Clear(SeqList *list)
{
	TSeqList *temp=NULL;
	if(list==NULL)
	{
		return;
	}
	temp=(SeqList*)list;
	temp->length=0;
	memset(temp->node, 0, (temp->capacity*sizeof(void*)));
	return;
}
//销毁顺序表
void SeqList_Destory(SeqList *list)
{
	TSeqList *temp=NULL;
	if(list==NULL)
	{
		return;
	}
	temp=(TSeqList *)list;
	if(temp->node != NULL)
	{
		free(temp->node);	// 先释放头节点中的指针数组
	}
	free(temp);		//在释放头节点
	return;
}
