#include"function.h"

pNode BuyNewNode(DataType data)
{
	pNode pTempNode = NULL;
	pTempNode = (pNode)malloc(sizeof(pNode));
	if (pTempNode)
	{
		pTempNode->data = data;
		pTempNode->_pNext = NULL;
	}
	return pTempNode;
}

void InsertNodeByFrontToTail(pNode *pHead, DataType data)
{
	pNode pTemp = NULL;
	if (*pHead == NULL)
		*pHead = BuyNewNode(data);

	else
	{
		pTemp = BuyNewNode(data);
		pTemp->_pNext = *pHead;
		*pHead = pTemp;
	}
}

void InserttNodeByTailToFront(pNode *pHead, DataType data)
{
	pNode pTest = NULL;
	pNode pCur = *pHead;

	pTest = BuyNewNode(data);
	if (*pHead == NULL)
		(*pHead) = pTest;

	else
	{
		while (NULL != pCur->_pNext)
		{
			pCur = pCur->_pNext;
		}
		pCur ->_pNext = pTest;
	}

}

void PrintNodeProntToTail(pNode pHead)
{
	//pNode pTemp = pHead;
	if (NULL == pHead)
		return;

	while (pHead != NULL)
	{
		printf("%d -> ", pHead->data);
		pHead = pHead->_pNext;
	}
	printf("NULL");
	printf("\n");
}

pNode ReceiveNodeList(pNode pHead)
{
	pNode pTest = pHead;
	//pNode pNextNode = NULL;
	pNode pPre = NULL;
	//pNode pReverse = NULL;

	if (pHead == NULL || pHead->_pNext == NULL)
		return pHead;

	while (pTest != NULL)
	{
		pNode pNextNode = pTest->_pNext;
		pTest->_pNext = pPre;
		pPre = pTest;
		pTest = pNextNode;
	}
	return pPre;
}

pNode ReceiveNodeList_DG(pNode pHead)
{
	pNode pNewNode = NULL;
	if (pHead == NULL || pHead->_pNext == NULL)
		return pHead;

	pNewNode = ReceiveNodeList_DG(pHead->_pNext);

	pHead->_pNext->_pNext = pHead;                       //翻转链表的指向
	pHead->_pNext = NULL;                        //记得赋值NULL，防止链表错乱
	return pNewNode;                          //新链表头永远指向的是原链表的链尾

}

pNode MeryTwoSortNodeChangeOneSortNode(pNode pHead1, pNode pHead2)
{
	pNode pNewNode = NULL;
	pNode pTemp = NULL;
	pNode pNextNode = NULL;
	unsigned int Node1Len = 0;
	unsigned int Node2Len = 0;

	while (pHead1->_pNext != NULL)
	{
		++Node1Len;
	}
	while (pHead1->_pNext != NULL)
	{
		++Node2Len;
	}

	if (Node1Len < Node2Len)     //长的链表为pHead1
	{
		pTemp = pHead1;
		pHead1 = pHead2;
		pHead2 = pTemp;
	}

	while (pHead1 != NULL)
	{
		if (pHead1->data < pHead2->data)
		{
			pNextNode = pHead1;
			pHead1 = pHead1->_pNext;
			pNextNode = pNextNode->_pNext;
		}
		pNextNode = pHead2;
		pHead2 = pHead2->_pNext;
		pNextNode = pNextNode->_pNext;
	}
	if (pHead1 == NULL)
		return pNewNode;
	else
	{
		pNextNode = pHead1;
	}
	return pNewNode;
}

pNode MeryTwoSortNodeChangeOneSortNode_DG(pNode pHead1, pNode pHead2)
{
	pNode pNewHead = NULL;

	if (pHead1 == NULL)
		return pHead2;
	else if (pHead2 == NULL)
		return pHead1;
	else
	{
		if (pHead1->data > pHead2->data)
		{
			pNewHead = pHead2;
			pNewHead->_pNext = MeryTwoSortNodeChangeOneSortNode_DG( pHead1, pHead2->_pNext);
		}
		else
		{
			pNewHead = pHead1;
			pNewHead->_pNext = MeryTwoSortNodeChangeOneSortNode_DG(pHead1->_pNext, pHead2);
		}
	}
	return pNewHead;
}


void BubbleSortNodeList(pNode pHead)
{
	int pTempNode = 0;
	pNode pTail = NULL;
	pNode pPreCur = NULL;
	pNode pCur = NULL;
	int isFlag = 1;

	if (pHead == NULL || pHead->_pNext == NULL)
	{
		return;
	}

	while (pHead != pTail)
	{
		isFlag = 0;

		pPreCur = pHead;
		pCur = pHead->_pNext;

		while (pCur != pTail)
		{
			if (pCur->data < pPreCur->data)
			{
				pTempNode = pCur->data;
				pCur->data = pPreCur->data;
				pPreCur->data = pTempNode;

				isFlag = 1;
			}
			pPreCur = pCur;
			pCur = pCur->_pNext;
		}
		if (!isFlag)
			return;

		pTail = pPreCur;
	}
}


pNode SearchMIdNode(pNode pHead)
{
	pNode pFast = pHead;
	pNode pSlow = pHead;

	if (pHead == NULL || pHead->_pNext == NULL)
		return NULL;


	while (NULL != pFast && NULL != pFast->_pNext)
	{
		pSlow = pSlow->_pNext;
		pFast = pFast->_pNext->_pNext;
	}
	return pSlow;
}

pNode FindLastKNode(pNode pHead, int key)
{
	pNode pCur = pHead;
	pNode pSlow = pHead;
	pNode pFast = pHead;

	if (pHead == NULL )
	{
		return NULL;
	}
	while (key--)
	{
		if (pFast == NULL)
			return NULL;
		pFast = pFast->_pNext;
	}
	while (pFast != NULL)
	{
		pFast = pFast->_pNext;
		pSlow = pSlow->_pNext;
	}
	return pSlow;
}

void DeleteLastKNode(pNode pHead, int key)
{
	pNode pPosDelNode = FindLastKNode(pHead, key+1);

	if (pPosDelNode == pHead)
	{
		free(pPosDelNode);
		return;
	}
	pPosDelNode->_pNext = pPosDelNode->_pNext->_pNext;
}

pNode FindDataInNodeList(pNode pHead, DataType k)
{
	pNode pCur = pHead;
	while (pCur != NULL)
	{
		if (pCur->data == k)
		{
			return pCur;
		}
		pCur = pCur->_pNext;
	}
	return NULL;
}

pNode pFrontNode(pNode pHead)       //返回链表第一个节点
{
	pNode pPcur = pHead;
	if (pHead == NULL)
		return NULL;
	return pPcur;
}

pNode pTailNode(pNode pHead)    //返回链表最后一个节点
{
	pNode pPcur = pHead;
	if (pHead == NULL)
		return NULL;
	while (pPcur != NULL && pPcur->_pNext != NULL)
	{
		pPcur = pPcur->_pNext;
	}
	return pPcur;
}

void GetCircleForList(pNode pHead)
{
	pNode pTemp = NULL;
	pTemp = FindDataInNodeList(pHead, 9);
	pTemp->_pNext = FindDataInNodeList(pHead, 7);
}

pNode isHaveCircle(pNode pHead)
{
	pNode pSlowNode = pHead;
	pNode pFastNode = pHead;

	if (pHead == NULL)
		return NULL;

	while (pFastNode != pSlowNode && pFastNode->_pNext != NULL)
	{
		pFastNode = pFastNode->_pNext->_pNext;
		pSlowNode = pSlowNode->_pNext;
	}
	return pSlowNode;
}

int GetCircleLength(pNode pHead)
{
	pNode MeetNode = NULL;
	pNode pCur = NULL;
	size_t count = 0;

	if (isHaveCircle(pHead) == NULL)
		return 0;

	MeetNode = isHaveCircle(pHead);
	pCur = MeetNode->_pNext;

	while (pCur != MeetNode)
	{
		count++;
		pCur = pCur->_pNext;

	}
	return count;
}


pNode GetCircleIntoNode(pNode pHead)
{
	pNode pCur = pHead;
	//在判断带环问题时，返回了环中快慢指针的相遇点。
	pNode pMeetNodeInCircle = NULL;
	pMeetNodeInCircle = isHaveCircle(pHead);

	while (pCur != pMeetNodeInCircle)
	{
		pCur = pCur->_pNext;
		pMeetNodeInCircle = pMeetNodeInCircle->_pNext;
	}
	return pMeetNodeInCircle;
}



void GetCircleForJoseph(pNode pHead)
{
	pNode front = NULL;
	pNode tail = NULL;
	front = pFrontNode(pHead);
	tail = pTailNode(pHead);

	tail->_pNext = front;
}


void GetJosephCircle(pNode pHead, size_t K)
{
	int count = K;
	pNode pPreNode = pHead;
	pNode pCurNode = NULL;

	if (pHead == NULL)
		return;
	while (pPreNode->_pNext != pPreNode)
	{
		count = K;
		while (--count)
		{
			pCurNode = pPreNode;
			pPreNode = pPreNode->_pNext;
		}

		pCurNode->_pNext = pPreNode->_pNext;
		printf("%d 号出去-> ", pPreNode->data);
		//free(pPreNode);
		pPreNode = pPreNode->_pNext;
	}
	//return pPreNode;
	printf("\n最后留下的人是： %d \n\n", pPreNode->data);
}

int GetNodeListLength(pNode pHead)
{
	int count = 0;
	pNode pCur = pHead;
	if (pHead == NULL)
		return 0;
	while (pCur)
	{
		count++;
	}
	return count;
}


void DeleteNotTailNode(pNode pos)
{
	assert(pos);
	pNode pTempNode = NULL;
	DataType temp = 0;
	if (pos == NULL)
		return;
	else
	{
		//交换节点值
		temp = pos->data;
		pos->data = pos->_pNext->data;
		pos->_pNext->data = temp;

		pTempNode = pos->_pNext;
		pos->_pNext = pTempNode->_pNext;
		//free(pTempNode);
		pTempNode = NULL;
	}
}


void InsertNotHead(pNode pos, DataType data)
{
	pNode pNewNode = NULL;
	pNode pCur = NULL;
	DataType pTemp = 0;

	if (pos == NULL)
		return;

	pNewNode = BuyNewNode(data);
	if (pNewNode == NULL)
		return;

	pCur = pos;
	pNewNode->_pNext = pCur->_pNext;
	pCur->_pNext = pNewNode;

	pTemp = pCur->data;
	pCur->data = pNewNode->data;
	pNewNode->data = pTemp;
}