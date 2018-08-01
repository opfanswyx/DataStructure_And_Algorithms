#include "SeqList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Teacher
{
	char name[32];
	int age;
}Teacher;

int main()
{
	int ret = 0;
	SeqList * list = NULL;
	Teacher t1, t2, t3, t4, t5; //���Ԫ��
	t1.age = 31;
	t2.age = 32;
	t3.age = 33;
	t4.age = 34;
	t5.age = 35;
	//�������
	list = SeqList_Create(10);  //����˳���
	
	//������
	ret = SeqList_Insert(list, (SeqListNode*)&t1, 0); //λ��0��ʾʼ����ͷ������
	ret = SeqList_Insert(list, (SeqListNode*)&t2, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t3, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t4, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t5, 0);

	printf("˳���������%d\n", SeqList_Capacity(list));
	printf("˳����ȣ�%d\n", SeqList_Length(list));
	
	//����˳���
	printf("����˳���\n");
	for (int i = 0; i < SeqList_Length(list); i++)
	{
		Teacher* temp = (Teacher*)SeqList_Get(list, i); //��ȡ������
		if (temp == NULL)
		{
			printf("func SeqList_Get() error\n", ret);
			return;
		}
		
		printf("age: %d\n", temp->age);
	}


	//��������
	printf("����˳���ʱ��\n");
	while (SeqList_Length(list) > 0)
	{
		Teacher* temp = (Teacher *)SeqList_Delete(list, 0); //ɾ��ͷ��Ԫ��
		if (temp == NULL)
		{
			printf("func SeqList_Get() error\n", ret);
			return;
		}
		
		printf("age: %d\n", temp->age);
	}
	SeqList_Destory(list);

	system("pause");
	return 0;
}
