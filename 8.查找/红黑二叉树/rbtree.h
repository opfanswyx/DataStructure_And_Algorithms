#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_
#include<stdio.h>
#include<stdlib.h>

typedef enum{RED, BLACK}ColorType;

typedef struct RB_TREE{
    int key;
    struct RB_TREE * left;
    struct RB_TREE * right;
    struct RB_TREE * p;
    ColorType color;
}RB_TREE;

typedef struct RBT_Root{
    RB_TREE * root;
    RB_TREE * nil;
}RBT_Root;

RBT_Root* rbTree_init(void);
void rbTree_insert(RBT_Root* *T, int k);
void rbTree_delete(RBT_Root* *T, int k);
void rbTree_transplant(RBT_Root* T, RB_TREE* u, RB_TREE* v);
void rbTree_left_rotate( RBT_Root* T, RB_TREE* x);
void rbTree_right_rotate( RBT_Root* T, RB_TREE* x);
void rbTree_inPrint(RBT_Root* T, RB_TREE* t);
void rbTree_prePrint(RBT_Root * T, RB_TREE* t);
void rbTree_print(RBT_Root* T);
RB_TREE* rbt_findMin(RBT_Root * T, RB_TREE* t);
#endif