#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void SeqList;
typedef void SeqListNode;

typedef struct _tag_SeqList  //ͷ��㣬��¼�����Ϣ
{
	int capacity;  //������
	int length;    //����
	int * node;    //node[capacity]��Ϊָ������
}TSeqList;

//����˳���
SeqList* SeqList_Create(int capacity) //����ֵΪSeqList*���ͣ���˳���ĵ�ַ
{
	int ret;
	TSeqList *temp = NULL;
	temp = (TSeqList*)malloc(sizeof(TSeqList));  //Ϊͷ������ռ�
	if (temp == NULL)
	{
		ret = 1;
		printf("func SeqList_Create() error:%d\n", ret);
		return NULL;
	}
	memset(temp, 0, sizeof(TSeqList));
	temp->capacity = capacity;
	temp->length = 0;
	temp->node = (int*)malloc(sizeof(void*)*capacity); //����һ��ָ������
	if (temp->node == NULL)
	{
		ret = 2;
		printf("func SeqList_Create() error:%d\n", ret);
		return NULL;
	}
	return temp;  //������õ�˳���ĵ�ַ�ӳ�ȥ
}

//��˳�������
int SeqList_Capacity(SeqList* list) //����Ϊ˳����ַ
{
	TSeqList *temp = NULL;
	if (list == NULL) //����׳���ж�
	{
		return;
	}
	temp = (TSeqList *)list;
	return temp->capacity;
}

//��ȡ˳�����
int SeqList_Length(SeqList* list)
{
	TSeqList *temp = NULL;
	if (list == NULL)
	{
		return;
	}
	temp = (TSeqList *)list;
	return temp->length;
}

//����Ԫ��
int SeqList_Insert(SeqList* list, SeqListNode* node, int pos)
{                     //����Ϊ˳����ַ��Ҫ�����Ԫ�ص�ַ������λ��
	int i;
	TSeqList *temp = NULL;
	//������׳���ж�
	if (list == NULL || node == NULL) //���˳���Ϊ�գ����߽��Ϊ��
	{
		return -1;
	}
	temp = (TSeqList *)list;
	//���˳�������
	if (temp->length >= temp->capacity)
	{
		return -2;
	}

	//�ݴ�
	if (pos > temp->length) //���������pos�ڳ��Ⱥ󣬼��м��п��࣬
		pos = temp->length; //�����������һ��Ԫ�غ���

	for (i = temp->length; i > pos; i--)  //������λ�õ�Ԫ�����κ��ƶ�
	{
		temp->node[i] = temp->node[i - 1];
	}
	temp->node[i] = (int)node; //Ȼ���ڿճ���λ�ò�����Ԫ�ؽ��
	temp->length++; //����ɹ��󣬳��ȼ�1
	return 0;
}

//ɾ��Ԫ��
SeqList* SeqList_Delete(SeqList* list, int pos)
{
	int i;
	//������׳���ж�
	TSeqList * tlist = NULL;
	SeqListNode * temp = NULL;
	tlist = (TSeqList *)list;
	if (list == NULL || pos < 0 || pos >= tlist->capacity)
	{
		printf("SeqList_Delete() error\n");
		return NULL;
	}
	temp = (SeqListNode *)tlist->node[pos]; //Ҫɾ����Ԫ��

	for (i = pos + 1; i < tlist->length; i++) //��ɾ��Ԫ��λ�ú������Ԫ����ǰ�ƶ�
	{
		tlist->node[i - 1] = tlist->node[i];
	}

	tlist->length--; //ɾ��Ԫ�غ󣬳���Ҫ��
	return temp;
}

SeqList* SeqList_Get(SeqList* list, int pos)
{
	//������׳���ж�
	TSeqList * tlist = NULL;
	SeqListNode * temp = NULL;
	tlist = (TSeqList *)list;
	if (list == NULL || pos < 0 || pos >= tlist->capacity)
	{
		printf("SeqList_Get() error\n");
		return NULL;
	}
	temp = (SeqListNode *)tlist->node[pos]; //������posλ�õĽ��ָ�븳��temp
	return temp;
}

//���˳���
void SeqList_Clear(SeqList* list)
{
	TSeqList *temp = NULL;
	if (list == NULL)
	{
		return;
	}
	temp = (TSeqList *)list;
	temp->length = 0;
	memset(temp->node, 0, (temp->capacity * sizeof(void*))); //��˳���ȫ����0
	return;
}
//����˳���
void SeqList_Destory(SeqList* list)
{
	TSeqList* temp = NULL;
	if (list == NULL)  //�������˳���Ϊ��
	{
		return;
	}
	temp = (TSeqList *)list;
	if (temp->node != NULL)
	{
		free(temp->node); //���ͷ�ͷ����е�ָ������
	}
	free(temp); //���ͷ�ͷ���
	return;
}
