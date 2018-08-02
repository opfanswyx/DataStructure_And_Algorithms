#define _CRT_SECURE_NO_WARNINGS
#include "clist.h"
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int m,n;
	printf("please input cirle total num:\n");
	scanf("%d",&m);
	if(m<=0)
	{
		printf("please input correct number\n");
		return 0;
	}
	printf("please input goto out num:\n");
	scanf("%d",&n);
	if(n<=0)
	{
		printf("please input correct number\n");
		return 0;
	}
	pHead ph=NULL;
	ph=ClistCreate();
	if(ph==NULL)
	{
		printf("ClistCreate faild\n");
		return 0;
	}
	int i;
	for(i=m;i>0;i--)
	{
		ClistInsert(ph,0,i);
	}
	print(ph);
	printf("out number:\n");
	pNode node=ph->next;
	while(node->next!=node)		//循环结束条件，结点指向其自身，此时剩余最后一个结点
	{
		int j;
		for(j=1;j<n-1;j++)		//j<n-1,报到n就重新开始
		{
			node=node->next;
		}
		pNode pTmp=node->next;	//pTmp指向要出局的结点

		//接下来先要判断这个结点是0号位置的结点还是其它位置的结点
		if(pTmp==ph->next) 	//如果此结点在0号位置
		{
			ph->next=pTmp->next;
			node->next=pTmp->next;
			printf("%d ",pTmp->data);
			free(pTmp);
			ph->length--;
		}
		else
		{
			node->next=pTmp->next;
			printf("%d ",pTmp->data);
			free(pTmp);
			ph->length--;
		}
		node=node->next;
	}
	node->next=node;
	printf("\n");
	printf("last num:\n");
	print(ph);
	system("pause");
	return 0;
}
