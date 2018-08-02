#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
int Max(int x,int y)
{
    return x>y?x:y;
}
void Create(BiTree &T)  //先序建一颗二叉树
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
    T=NULL;
    else
    {
        T=(BiTNode *)malloc(sizeof(BiTNode));
        T->data=ch;
        Create(T->lchild);
        Create(T->rchild);
    }
}
void Preorder(BiTree &root)  //先序遍历打印二叉树
{
    if(root!=NULL)
    {
        printf("%c ",root->data);
        Preorder(root->lchild);
        Preorder(root->rchild);
    }
}
void Inorder(BiTree &root)  //中序遍历打印二叉树
{
    if(root!=NULL)
    {
        Inorder(root->lchild);
        printf("%c ",root->data);
        Inorder(root->rchild);
    }
}
void Postorder(BiTree &root)  //后续遍历打印二叉树
{
    if(root!=NULL)
    {
        Postorder(root->lchild);
        Postorder(root->rchild);
        printf("%c ",root->data);
    }
}
void Preorderleaf(BiTree &root) //先序遍历输出叶子节点
{
    if(root!=NULL)
    {
        if(root->lchild==NULL&&root->rchild==NULL)
        printf("%c ",root->data);
        Preorderleaf(root->lchild);
        Preorderleaf(root->rchild);
    }
}
int LeafCount(BiTree &root)  //统计叶子节点的个数
{
    int leaf;
    if(root==NULL)
    leaf=0;
    else if(root->lchild==NULL&&root->rchild==NULL)
    leaf=1;
    else
    leaf=LeafCount(root->lchild)+LeafCount(root->rchild);
    return leaf;
}
int PostTreeDepth(BiTree &root)  //统计树的高度
{
    int hl,hr,max;
    if(root!=NULL)
    {
        hl=PostTreeDepth(root->lchild);
        hr=PostTreeDepth(root->rchild);
        max=Max(hl,hr);
        return max+1;
    }
    else
    return 0;
}
void dowork()
{
    BiTree cam;
    Create(cam);
    Preorder(cam);
    printf("\n");
    Inorder(cam);
    printf("\n");
    Postorder(cam);
    printf("\n");
    printf("叶子节点：");
    Preorderleaf(cam);
    printf("\n");
    printf("叶子节点的个数为:%d\n",LeafCount(cam));
    printf("树的深度为:%d\n",PostTreeDepth(cam));
}
int main()
{
    dowork();
    return 0;
}
