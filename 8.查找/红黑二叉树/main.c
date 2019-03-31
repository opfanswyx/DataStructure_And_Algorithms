#include"rbtree.h"

int main()
{
    RBT_Root* T = rbTree_init();
    rbTree_insert(&T,3);
    rbTree_insert(&T,5);
    rbTree_insert(&T,1);
    rbTree_insert(&T,2);
    rbTree_insert(&T,4);
    rbTree_print(T);
    printf("\n");
    rbTree_delete(&T,3);
    rbTree_print(T);
    return 0;
}