#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>
#define DataType int

struct Node
{
	DataType data;
	struct Node* _pNext;
};

typedef struct Node Node;
typedef Node *pNode;

pNode InitNodeList(pNode *pHead);//初始化

pNode BuyNewNode(DataType data);//新建节点

void InsertNodeByFrontToTail(pNode *pHead, DataType data);//头插法

void PrintNodeProntToTail(pNode pHead);//正序打印

void InserttNodeByTailToFront(pNode *pHead, DataType data);//尾插法

pNode ReceiveNodeList(pNode pHead);//反转链表—一般方法

pNode ReceiveNodeList_DG(pNode pHead);//反转链表——递归实现

pNode MeryTwoSortNodeChangeOneSortNode(pNode pHead1, pNode pHead2);//合并两个有序单链表——一般方法

pNode MeryTwoSortNodeChangeOneSortNode_DG(pNode pHead1, pNode pHead2);//合并两个有序单链表——递归实现

void BubbleSortNodeList(pNode pHead);//链表排序——冒泡法实现

pNode SearchMIdNode(pNode pHead);//查找中间节点——快慢指针法

pNode FindLastKNode(pNode pHead, int key);//找到倒数第K个节点

void InsertNotIntoKHead(pNode pos, DataType data);// 非头结点前插入data

pNode FindDataInNodeList(pNode pHead, DataType k);//寻找链表中data为K的节点

void DeleteLastKNode(pNode pHead, int key);//删除倒数第K个节点

void DeleteNotTailNode(pNode pos);//删除单链表的非尾结点

void GetCircleForJoseph(pNode pHead);//构造约瑟夫环

void GetJosephCircle(pNode pHead, size_t K);//单链表实现约瑟夫环

void GetCircleForList(pNode pHead);//构造带环链表

pNode isHaveCircle(pNode pHead);//判断链表是否带环

int GetCircleLength(pNode pHead);//求环的长度

pNode GetCircleIntoNode(pNode pHead);//求环的入口点

pNode pFrontNode(pNode pHead);//返回链表第一个节点

pNode pTailNode(pNode pHead); //返回链表最后一个节点

void InsertNotHead(pNode pos, DataType data);// 非头结点前插入data

#endif