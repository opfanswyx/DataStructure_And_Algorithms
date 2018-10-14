#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 10  //��ϣ����

typedef struct
{
	int* elem;  //���飬��̬����
	int count;  //��ǰԪ�ظ���
}HashTable;

int m = 0;    //��ϣ����ȫ�ֱ���


//��ϣ���ʼ��
void InitHashTable(HashTable* h)
{
	int i;
	m = HASHSIZE;
	h->count = m;
	h->elem = (int*)malloc(m*sizeof(int));
	for (i = 0; i < m; i++)
		h->elem[i] = NULL;
	return;
}

//�����ϣ����
int Hash(int key)
{
	return key%m; //����������
}

//�������
void InsertHash(HashTable* h, int key)
{
	int addr = Hash(key); //���ϣ��ַ
	while (h->elem[addr] != NULL)
		addr = (addr + 1) % m; //����̽�ⷨ�����ͻ
	h->elem[addr] = key;
}

//����
int SearchHash(HashTable h, int key, int *addr)
{
	*addr = Hash(key);  //���ϣ��ַ
	while (h.elem[*addr] != key)
	{
		*addr = (*addr + 1) % m; //���Ŷ�ַ������̽��
		if (h.elem[*addr] == NULL || *addr == Hash(key)) //���ѭ���ص�ԭ��
			return 0;   //˵���ؼ��ֲ�����
	}
	return 1;
}

int main()
{
	HashTable ht;
	InitHashTable(&ht);
	int arr[10] = { 107, 8, 13, 22, 16, 30, 103, 76, 220, 94 };
	for (int i = 0; i < 10; i++)
		InsertHash(&ht, arr[i]);
	
	int num;  //Ҫ���ҵ�����
	printf("������Ҫ���ҵ����ݣ�\n");
	scanf("%d", &num);

	int addr = Hash(num);
	int ret = SearchHash(ht, num, &addr);
	if (ret)
		printf("���ҳɹ���\n");
	else
		printf("����ʧ�ܣ�\n");

	system("pause");
	return 0;
}
