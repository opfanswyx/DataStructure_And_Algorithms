#ifndef __BSTACK__
#define __BSTACK__
#include"bstree.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct StackNode* pNode;
typedef struct Stack* BSTack;

struct StackNode                             /* 栈结点 */
{
    BSTree data;
    pNode next;
};
struct Stack                            /* 栈结构 */
{
    pNode top;
    int size;
};

BSTack Create();                        /* 创建栈 */
int IsEmpty(BSTack bstack);             /* 判断栈是否为空 */
int Push(BSTack bstack, BSTree data);   /* 元素入栈 */
pNode getTop(BSTack bstack);            /* 获取栈顶元素 */
pNode Pop(BSTack bstack);               /* 弹出栈顶元素 */
#endif