#include <stdio.h>
#include <stdlib.h>

typedef struct LinkListsNode
{
	int tag;							//��־λ
	union
	{
		int data;					//��Ԫ��
		struct LinkListsNode *Lists;	//ָ���ӱ��ָ��
	}value;
	struct LinkListsNode *link;			//ָ����һ��Ԫ��
}LSNode;								//����������Ͷ���
//������ĳ���
int LSLength(LSNode *ls);
//����������
int LSDepth(LSNode *ls);
//��������ls
void LSDis(LSNode *ls);
//�������
void LSCreate(LSNode** ls, int flag);