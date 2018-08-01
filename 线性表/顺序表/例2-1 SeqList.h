#ifndef _SEQLIST_H_
#define  _SEQLIST_H_

typedef void SeqList;
typedef void SeqListNode;

SeqList* SeqList_Create(int capacity); //����˳���
void SeqList_Destory(SeqList* list);  //����˳���
void SeqList_Clear(SeqList* list);  //������Ա�
int SeqList_Length(SeqList* list);  //��ȡ˳�����
int SeqList_Capacity(SeqList* list); //��ȡ˳�������
int SeqList_Insert(SeqList* list, SeqListNode* node, int pos); //��posλ�ò���Ԫ��
SeqList* SeqList_Get(SeqList* list, int pos); //��ȡposλ���ϵ�Ԫ��
SeqList* SeqList_Delete(SeqList* list, int pos);  //ɾ��posλ�õ�Ԫ��

#endif
