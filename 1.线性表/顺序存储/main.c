#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "SeqList.h"

typedef struct _Teacher
{
	char name[32];
	int age;
}Teacher;

int main()
{
	int ret=0;
	int len=0;
	int i=0;
	SeqList *list=NULL;
	Teacher t1={
		"loci",
		32
	};
	Teacher t2={
		"coco",
		23
	};
	Teacher t3={
		"lili",
		21
	};
	Teacher t4={
		"fgfg",
		45
	};
	Teacher t5={
		"ktkt",
		28
	};
	//创建顺序表
	list=SeqList_Create(10);

	//插入结点
	ret=SeqList_Insert(list,(SeqListNode*)&t1,0);	//位置0表示始终头部插入
	ret=SeqList_Insert(list,(SeqListNode*)&t2,0);
	ret=SeqList_Insert(list,(SeqListNode*)&t3,0);
	ret=SeqList_Insert(list,(SeqListNode*)&t4,0);
	ret=SeqList_Insert(list,(SeqListNode*)&t5,0);

	printf("顺序表容量:%d\n",SeqList_Capacity(list));
	printf("顺序表长度:%d\n",SeqList_Length(list));
	len=SeqList_Length(list);

	//遍历顺序表
	printf("遍历顺序表：\n");
	for(i=0;i<len; i++)
	{
		Teacher *temp=(Teacher *)SeqList_Get(list,i);	//获取顺序表结点
		if(temp==NULL)
		{
			printf("func SeqList_Get() error\n");
			return;
		}
		printf("teachr name:%s\tage:%d\n",temp->name,temp->age);
	}

	//销毁链表
	printf("销毁顺序表：\n");
	while(SeqList_Length(list)>0)
	{
		Teacher *temp=(Teacher *)SeqList_Delete(list,0);	//删除头部元素
		if(temp==NULL)
		{
			printf("func SeqList_Delete error\n");
			return;
		}
		printf("teachr name:%s\tage:%d\n",temp->name,temp->age);
	}
	SeqList_Destory(list);
	system("pause");
	return 0;
}