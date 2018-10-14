typedef struct BitNode
{
    DataType data;
    struct BitNode *lchild, *rchild, *parent;
}BitNode;

//查找，参数：f指向T的双亲，当查找成功，则p指向该数据元素节点，返回1
//否则，指针p指向查找路径上访问的最后一个节点，返回-1
BiTree searchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if(!T)
    {
        *p=f;
        return NULL;
    }
    else if(T->data==key)
    {
        *p=T;
        return T;
    }
    else if(T->data>key)
        return searchBST(T->lchild,key,T,p);
    else
        return searchBST(T->rchild,key,T,p);
}

int InsertBST(BitNode *T, int key)
{
    BitNode *p,*s;
    if(!searchBST(T,key,NULL,&p))
    {
        s=(BitNode*)malloc(sizeof(BitNode));
        s->data=key;
        s->lchild=s->rchild=NULL;
        if(!p)
            T=s;
        else if(key<p->data)
            p->lchild=s;
        else
            p->rchild=s;
        return 1;
    }
    else
        return 0;
}

void DeleteBST(BitNode *T, int key)
{
    BitNode *q,*s;
    BitNode *node=searchBST(T,key,NULL,&s);
    if(node==NULL)
    {
        printf("\n此树中没有此节点\n");
        return ;
    }
    else
    {
        if(node->lchild==NULL && node->rchild==NULL)
        {
            printf("此节点是一个叶子节点\n");
            node->parent->lchild=node->parent->rchild=NULL;
            free(node);
        }
        else if(node->rchild==NULL)
        {
            printf("此节点只有左子树\n");
            q=node;
            node=node->lchild;
            if(q==q->parent->rchild)
                q->parent->rchild=node;
            else
                q->parent->lchild=node;

            free(q);
        }
        else if(node->lchild==NULL)
        {
            printf("此结点只有右子树\n");
            q=node;
            node=node->rchild;
            if(q==q->parent->rchild)
                q->parent->rchild=node;
            else
                q->parent->lchild=node;

            free(q);
        }
        else
        {
            q=node;
            s=node->lchild;
            while(s->rchild)
            {
                q=s;
                s=s->rchild;
            }
            node->data=s->data;
            if(q!=node)
                q->rchild=s->lchild;
            else
                q->lchild=s->lchild;
            free(s);
        }
    }
}