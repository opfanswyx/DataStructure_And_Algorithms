#include "rbtree.h"

RB_TREE* rbt_findMin(RBT_Root * T, RB_TREE* t){
    if(t == T->nil){
    return T->nil;
    }
    while(t->left != T->nil){
    t = t->left;
    }
    return t;
}

RBT_Root* rbTree_init(void){
    RBT_Root* T;
    T = (RBT_Root*)malloc(sizeof(RBT_Root));
    T->nil = (RB_TREE*)malloc(sizeof(RB_TREE));
    T->nil->color = BLACK;
    T->nil->left = T->nil->right = NULL;
    T->nil->p = NULL;
    T->root = T->nil;
    return T;
}

void RB_Insert_Fixup(RBT_Root* T, RB_TREE* x)
{
    //首先判断其父结点颜色为红色时才需要调整；为黑色时直接插入即可，不需要调整
    while (x->p->color == RED) 
    {
        //由于还涉及到其叔叔结点，所以此处需分开讨论，确定父结点是祖父结点的左孩子还是右孩子
        if (x->p == x->p->p->left) 
        {
            RB_TREE * y = x->p->p->right;//找到其叔叔结点
            //如果叔叔结点颜色为红色，此为第1 种情况，处理方法为：父结点颜色改为黑色；叔叔结点颜色改为黑色；祖父结点颜色改为红色，将祖父结点赋值为当前结点，继续判断；
            if (y->color == RED) 
            {
                x->p->color = BLACK;
                y->color = BLACK;
                x->p->p->color = RED;
                x = x->p->p;
            }
            else
            {
                //反之，如果叔叔结点颜色为黑色，此处需分为两种情况：
                //1、当前结点时父结点的右孩子；
                //2、当前结点是父结点的左孩子
                if (x == x->p->right) 
                {
                    //第2 种情况：当前结点时父结点的右孩子。解决方案：将父结点作为当前结点做左旋操作。
                    x = x->p;
                    rbTree_left_rotate(T, x);
                }
                else
                {
                    //第3 种情况：当前结点是父结点的左孩子。解决方案：
                    //将父结点颜色改为黑色，祖父结点颜色改为红色，从祖父结点处进行右旋处理。
                    x->p->color = BLACK;
                    x->p->p->color = RED;
                    rbTree_right_rotate(T, x->p->p);
                }
            }
        }
        else
        {//如果父结点时祖父结点的右孩子，换汤不换药，只需将以上代码部分中的left 改为right 即可，道理是一样的。
            RB_TREE * y = x->p->p->left;
            if (y->color == RED) 
            {
                x->p->color = BLACK;
                y->color = BLACK;
                x->p->p->color = RED;
                x = x->p->p;
            }
            else
            {
                if (x == x->p->left) 
                {
                    x = x->p;
                    rbTree_right_rotate(T, x);
                }
                else
                {
                    x->p->color = BLACK;
                    x->p->p->color = RED;
                    rbTree_left_rotate(T, x->p->p);
                }
            }
        }
    }
    T->root->color = BLACK;
}

//插入操作分为3 步：1、将红黑树当二叉查找树，找到其插入位置；
//2、初始化插入结点，将新结点的颜色设为红色；
//3、通过调用调整函数，将二叉查找树重新改为红黑树
void rbTree_insert(RBT_Root**T, int k)
{
    //1、找到其要插入的位置。解决思路为：从树的根结点开始，通过不断的同新结点的值进行比较，最终找到插入位置
    RB_TREE * x, *p;
    x = (*T)->root;
    p = x;
    while(x != (*T)->nil)
    {
        p = x;
        if(k<x->key)
        {
            x = x->left;
        }else if(k>x->key)
        {
            x = x->right;
        }else
        {
            printf("\n%d 已存在\n",k);
            return;
        }
    }
    //初始化结点，将新结点的颜色设为红色
    x = (RB_TREE *)malloc(sizeof(RB_TREE));
    x->key = k;
    x->color = RED;
    x->left = x->right =(*T)->nil;
    x->p = p;
    //对新插入的结点，建立与其父结点之间的联系
    if((*T)->root == (*T)->nil)
    {
        (*T)->root = x;
    }else if(k < p->key)
    {
        p->left = x;
    }else
    {
        p->right = x;
    }
    //3、对二叉查找树进行调整
    RB_Insert_Fixup((*T),x);
}

void rbTree_transplant(RBT_Root* T, RB_TREE* u, RB_TREE* v)
{
    if(u->p == T->nil)
    {
        T->root = v;
    }else if(u == u->p->left)
    {
        u->p->left=v;
    }
    else
    {
        u->p->right=v;
    }
    v->p = u->p;
}

void RB_Delete_Fixup(RBT_Root**T,RB_TREE*x)
{
    while(x != (*T)->root && x->color == BLACK)
    {
        if(x == x->p->left)
        {
            RB_TREE* w = x->p->right;
            //第1 种情况：兄弟结点是红色的
            if(RED == w->color)
            {
                w->color = BLACK;
                w->p->color = RED;
                rbTree_left_rotate((*T),x->p);
                w = x->p->right;
            }
            //第2 种情况：兄弟是黑色的，并且兄弟的两个儿子都是黑色的。
            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            //第3 种情况
            if(w->left->color == RED && w->right->color == BLACK)
            {
                w->left->color = BLACK;
                w->color = RED;
                rbTree_right_rotate((*T),w);
                w = x->p->right;
            }
            //第4 种情况
            if (w->right->color == RED)
            {
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                rbTree_left_rotate((*T),x->p);
                x = (*T)->root;
            }
        }
        else
        {
            RB_TREE* w = x->p->left;
            //第1 种情况
            if(w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                rbTree_right_rotate((*T),x->p);
                w = x->p->left;
            }
            //第2 种情况
            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            //第3 种情况
            if(w->left->color == BLACK && w->right->color == RED)
            {
                w->color = RED;
                w->right->color = BLACK;
                w = x->p->left;
            }
            //第4 种情况
            if (w->right->color == BLACK)
            {
                w->color=w->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rbTree_right_rotate((*T),x->p);
                x = (*T)->root;
            }
        }
    }
    x->color = BLACK;//最终将根结点的颜色设为黑色
}

void rbTree_delete(RBT_Root* *T, int k)
{
    if(NULL == (*T)->root)
    {
        return ;
    }
    //找到要被删除的结点
    RB_TREE * toDelete = (*T)->root;
    RB_TREE * x = NULL;
    //找到值为k 的结点
    while(toDelete != (*T)->nil && toDelete->key != k)
    {
        if(k<toDelete->key)
        {
            toDelete = toDelete->left;
        }else if(k>toDelete->key)
        {
            toDelete = toDelete->right;
        }
    }
    if(toDelete == (*T)->nil)
    {
        printf("\n%d 不存在\n",k);
        return;
    }
    //如果两个孩子，就找到右子树中最小的结点，将之代替，然后直接删除该结点即可
    if(toDelete->left != (*T)->nil && toDelete->right != (*T)->nil)
    {
        RB_TREE* alternative = rbt_findMin((*T), toDelete->right);
        k = toDelete->key = alternative->key;//这里只对值进行复制，并不复制颜色，以免破坏红黑树的性质
        toDelete = alternative;
    }
    //如果只有一个孩子结点（只有左孩子或只有右孩子），直接用孩子结点顶替该结点位置即可（没有孩子结点的也走此判断语句）。
    if(toDelete->left == (*T)->nil)
    {
        x = toDelete->right;
        rbTree_transplant((*T),toDelete,toDelete->right);
    }else if(toDelete->right == (*T)->nil)
    {
        x = toDelete->left;
        rbTree_transplant((*T),toDelete,toDelete->left);
    }
    //在删除该结点之前，需判断此结点的颜色：如果是红色，直接删除，不会破坏红黑树；若是黑色，删除后会破坏红黑树的第5 条性质，需要对树做调整。
    if(toDelete->color == BLACK)
    {
        RB_Delete_Fixup(T,x);
    }
    //最终可以彻底删除要删除的结点，释放其占用的空间
    free(toDelete);
}

//T 表示为树根，x 表示需要进行左旋的子树的根结点
void rbTree_left_rotate( RBT_Root* T, RB_TREE* x)
{
    RB_TREE* y = x->right;//找到根结点的右子树
    x->right = y->left;//将右子树的左孩子移动至结点x 的右孩子处
    if(x->right != T->nil)
    {//如果x 的右子树不是nil，需重新连接右子树的双亲结点为x
        x->right->p = x;
    }
    y->p = x->p;//设置y 的双亲结点为x 的双亲结点
    //重新设置y 的双亲结点同y 的连接，分为2 种情况：
    //1、原x 结点本身就是整棵树的数根结点，此时只需要将T 指针指向y；
    //2、根据y 中关键字同其父结点关键字的值的大小，判断y 是父结点的左孩子还是右孩子
    if(y->p == T->nil)
    {
        T->root = y;
    }else if(y->key < y->p->key)
    {
        y->p->left = y;
    }else
    {
        y->p->right = y;
    }
    y->left = x;//将x 连接给y 结点的左孩子处
    x->p = y;//设置x 的双亲结点为y。
}

void rbTree_right_rotate( RBT_Root* T, RB_TREE* x)
{
    RB_TREE * y = x->left;
    x->left = y->right;
    if(T->nil != x->left)
    {
        x->left->p = x;
    }
    y->p = x->p;
    if(y->p == T->nil)
    {
        T->root = y;
    }else if(y->key < y->p->key)
    {
        y->p->left= y;
    }else
    {
        y->p->right = y;
    }
    y->right = x;
    x->p = y;
}

void rbTree_prePrint(RBT_Root* T, RB_TREE* t)
{
    if(T->nil == t)
    {
        return;
    }
    if(t->color == RED)
    {
        printf("%dR ",t->key);
    }else
    {
        printf("%dB ",t->key);
    }
    rbTree_prePrint(T,t->left);
    rbTree_prePrint(T,t->right);
}

void rbTree_inPrint(RBT_Root* T, RB_TREE* t)
{
    if(T->nil == t)
    {
        return ;
    }
    rbTree_inPrint(T,t->left);
    if(t->color == RED)
    {
        printf("%dR ",t->key);
    }else
    {
        printf("%dB ",t->key);
    }
    rbTree_inPrint(T,t->right);
}

//输出红黑树的前序遍历和中序遍历的结果
void rbTree_print(RBT_Root* T)
{
    printf("前序遍历：");
    rbTree_prePrint(T,T->root);
    printf("\n");
    printf("中序遍历：");
    rbTree_inPrint(T,T->root);
    printf("\n");
}