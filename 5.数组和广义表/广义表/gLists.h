#include <stdio.h>
#include <stdlib.h>

//�ṹ�嶨��
typedef struct LinkListsNode
{
	int tag;							//��־λ
	union
	{
		char atom;						//��Ԫ��
		struct LinkListsNode *Lists;	//ָ���ӱ��ָ��
	}value;
	struct LinkListsNode *link;			//ָ��ͬһ���еĺ��Ԫ��
}LSNode;								//����������Ͷ���
//�����ĵݹ鴴��
void LSCreate(LSNode** ls);
//�ݹ�����������
int LSDepth(LSNode *ls);
//��������ls
void LSDis(LSNode *ls);
//������ĳ���
int LSLength(LSNode *ls);