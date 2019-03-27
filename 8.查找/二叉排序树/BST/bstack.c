#include"bstack.h"

BSTack Create()                        /* 创建栈 */
{
    BSTack bstack = (BSTack)malloc(sizeof(struct Stack));
    if(NULL == bstack)
    {
        printf("[%s] malloc error\n",__func__);
        return NULL;
    }
    bstack->top = NULL;
    bstack->size = 0;
    return bstack;
}


int IsEmpty(BSTack bstack)             /* 判断栈是否为空 */
{
    if(bstack->top == NULL || bstack->size == 0)
        return 1;
    return 0;
}

int Push(BSTack bstack, BSTree data)   /* 元素入栈 */
{
    pNode pnode = (pNode)malloc(sizeof(struct StackNode));
    if(NULL == pnode)
    {
        printf("[%s] malloc error\n",__func__);
        return -1;
    }
    pnode->data = data;
	pnode->next = getTop(bstack);
	bstack->top = pnode;
	bstack->size++;
	return 1;
}

pNode getTop(BSTack bstack)            /* 获取栈顶元素 */
{
	if(0 != bstack->size)
		return bstack->top;
	return NULL;
}

pNode Pop(BSTack bstack)              /* 弹出栈顶元素 */
{
	if(IsEmpty(bstack))
	{
		return NULL;
	}
	pNode node = bstack->top;
	bstack->top = node->next;
	bstack->size--;
	//free(node);
	return node;
}