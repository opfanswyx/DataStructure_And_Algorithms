#include <stdio.h>
#include <stdlib.h>

#define ROW 3
#define COL 4
#define Max ((ROW)>(COL)?(ROW):(COL))
typedef int ElemType;
typedef struct MatrixPointer
{
	int row;
	int col;
	struct MatrixPointer *right, *down;
	union
	{
		ElemType value;
		struct MatrixPointer *link;
	}tag;
}MatNode;		//ʮ���������Ͷ���
//����һ��ʮ��������ʹ������a��ʼ��
void cmatCreate(MatNode *&hm, ElemType a[ROW][COL]);
//���
void cmatPrint(MatNode *hm);