#include"function.h"

void test()
{
	pNode pHead1 = NULL;
	pNode pHead2 = NULL;
	pNode pNewHead = NULL;
	pNode pHead3 = NULL;
	pNode pSortNode = NULL;
	pNode LastKNum = 0;
	pNode pReverseNode = NULL;
	pNode pR = NULL;
	pNode pHead4 = NULL;
	pNode pCirclieNode = NULL;
	size_t CircleLength = 0;
	pNode pIntoCircleNode = NULL;
	pNode pHead5 = NULL;
	pNode JueNode = NULL;
	pNode pHead6 = NULL;
	pNode pDelNode = NULL;
	pNode pInsertNode = NULL;
	pNode pH = NULL;

	InsertNodeByFrontToTail(&pHead1, 9);
	InsertNodeByFrontToTail(&pHead1, 8);
	InsertNodeByFrontToTail(&pHead1, 6);
	InsertNodeByFrontToTail(&pHead1, 5);
	InsertNodeByFrontToTail(&pHead1, 2);
	InsertNodeByFrontToTail(&pHead1, 1);

	PrintNodeProntToTail(pHead1);

	printf("\n链表的反转、还原:\n");
	pReverseNode = ReceiveNodeList(pHead1);     //反转
	PrintNodeProntToTail(pReverseNode);

	pR = ReceiveNodeList_DG(pReverseNode);      //反转
	PrintNodeProntToTail(pR);

	pHead1 = pR;
	printf("\npHead1: ");
	PrintNodeProntToTail(pHead1);          //还原pHead1

	printf("\n");

	InserttNodeByTailToFront(&pHead2, 2);
	InserttNodeByTailToFront(&pHead2, 3);
	InserttNodeByTailToFront(&pHead2, 4);
	InserttNodeByTailToFront(&pHead2, 5);
	InserttNodeByTailToFront(&pHead2, 6);
	InserttNodeByTailToFront(&pHead2, 7);

	printf("pHead2: ");
	PrintNodeProntToTail(pHead2);

	printf("\n两个有序链表的合并:\n");
	pNewHead = MeryTwoSortNodeChangeOneSortNode_DG(pHead1, pHead2);
	PrintNodeProntToTail(pNewHead);


	//新建无序链表3
	InsertNodeByFrontToTail(&pHead3, 9);
	InsertNodeByFrontToTail(&pHead3, 4);
	InsertNodeByFrontToTail(&pHead3, 5);
	InsertNodeByFrontToTail(&pHead3, 7);
	InsertNodeByFrontToTail(&pHead3, 4);
	InsertNodeByFrontToTail(&pHead3, 0);
	InsertNodeByFrontToTail(&pHead3, 3);

	printf("\npHead3: ");
	PrintNodeProntToTail(pHead3);

	printf("\n排序好的链表3：");
	BubbleSortNodeList(pHead3);
	PrintNodeProntToTail(pHead3);

	printf("\npHead1中间节点：%d\n", (SearchMIdNode(pHead1)->data));
	printf("\npNewHead中间节点：%d\n", (SearchMIdNode(pNewHead)->data));

	printf("\n查找倒数第K个节点: ");
	LastKNum = FindLastKNode(pNewHead, 2);
	if (LastKNum != NULL)
		printf("%d\n", LastKNum->data);
	else
		printf("没有找到\n");

	printf("\n删除倒数第K个节点\n");
	DeleteLastKNode(pNewHead, 3);

	//构造一个带环链表4
	InsertNodeByFrontToTail(&pHead4, 9);
	InsertNodeByFrontToTail(&pHead4, 8);
	InsertNodeByFrontToTail(&pHead4, 6);
	InsertNodeByFrontToTail(&pHead4, 5);
	InsertNodeByFrontToTail(&pHead4, 2);
	InsertNodeByFrontToTail(&pHead4, 1);
	InsertNodeByFrontToTail(&pHead4, 3);
	InsertNodeByFrontToTail(&pHead4, 0);
	InsertNodeByFrontToTail(&pHead4, 7);

	printf("\n打印链表4：\n");
	PrintNodeProntToTail(pHead4);

	printf("\n构造带环链表\n");
	GetCircleForList(pHead4);
	printf("构造OK\n");

	pCirclieNode = isHaveCircle(pHead4);
	if (pCirclieNode == NULL)
		printf("不带环\n");
	else
		printf("带环\n");

	printf("\n求环的长度：");
	//PrintNodeProntToTail(pHead4);

	CircleLength = GetCircleLength(pHead4);
	printf("%d", CircleLength);

	printf("\n求环的入口：");
	pIntoCircleNode = GetCircleIntoNode(pHead4);
	printf("%d\n", pIntoCircleNode->data);

	//构造一个链表，pHead5：    头插法构造单链表
	InsertNodeByFrontToTail(&pHead5, 9);
	InsertNodeByFrontToTail(&pHead5, 8);
	InsertNodeByFrontToTail(&pHead5, 7);
	InsertNodeByFrontToTail(&pHead5, 6);
	InsertNodeByFrontToTail(&pHead5, 5);
	InsertNodeByFrontToTail(&pHead5, 4);
	InsertNodeByFrontToTail(&pHead5, 3);
	InsertNodeByFrontToTail(&pHead5, 2);
	InsertNodeByFrontToTail(&pHead5, 1);

	printf("\n约瑟夫环问题:\n");
	//构造环
	GetCircleForJoseph(pHead5);
	printf("构造OK\n");

	//PrintNodeProntToTail(pHead5);

	//约瑟夫环
	GetJosephCircle(pHead5, 4);

	printf("构造链表6\n");

	InsertNodeByFrontToTail(&pHead6, 6);
	InsertNodeByFrontToTail(&pHead6, 5);
	InsertNodeByFrontToTail(&pHead6, 4);
	InsertNodeByFrontToTail(&pHead6, 3);
	InsertNodeByFrontToTail(&pHead6, 2);

	PrintNodeProntToTail(pHead6);
	printf("\n删除倒数第 3 个节点后，链表为：\n");
	DeleteLastKNode(pHead6, 3);

	PrintNodeProntToTail(pHead6);
	printf("\n");

	PrintNodeProntToTail(pHead6);
	printf("删除非尾节点 3 :\n");
	pDelNode = FindDataInNodeList(pHead6, 3);
	DeleteNotTailNode(pDelNode);
	PrintNodeProntToTail(pHead6);

	printf("\n非头节点 5 前的插入:\n");
	PrintNodeProntToTail(pHead6);

	pInsertNode = FindDataInNodeList(pHead6, 5);

	InsertNotHead(pInsertNode, 99);
	PrintNodeProntToTail(pHead6);
	printf("\n");
}

int main()
{
	test();
	return 0;
}