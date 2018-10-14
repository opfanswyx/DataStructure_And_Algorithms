#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//����˳����ң��ֿ���ң�
struct indexBlock   //�����Ľṹ
{
	int max;
	int start;
	int end;
} indexBlock[4];   //����������������4��struct����

int blockSearch(int key, int a[])
{
	int i = 0;
	int j;

	while (i<3 && key>indexBlock[i].max) //ȷ�����ĸ��ӱ��� 
		i++;

	if (i >= 3)  //���ڷֵĿ������򷵻�-1,�Ҳ�������     
		return -1;

	j = indexBlock[i].start;    //j���ڿ鷶Χ����ʼֵ

	while (j <= indexBlock[i].end && a[j] != key) //��ȷ���Ŀ��ڽ��в���  
		j++;

	if (j > indexBlock[i].end) //������ڿ鷶Χ�Ľ���ֵ����˵��û��Ҫ���ҵ�����j��Ϊ-1     
		j = -1;

	return j;
}

int main()
{
	int j = -1;
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }; //���ұ�
	printf("��֪���ұ�:\n");
	for (int i = 0; i < 15; i++) 
		printf("%d ", a[i]);

	printf("\n");

	for (int i = 0; i < 3; i++) 
	{
		indexBlock[i].start = j + 1; //ȷ��ÿ���鷶Χ����ʼֵ
		j = j + 1;

		indexBlock[i].end = j + 3;   //ȷ��ÿ���鷶Χ�Ľ���ֵ
		j = j + 3;

		indexBlock[i].max = a[j];    //ȷ��ÿ���鷶Χ��Ԫ�ص����ֵ
	}

	printf("��������Ҫ���ҵ�����\n");
	int key;
	scanf("%d", &key);
	int index = blockSearch(key, a);

	if (index >= 0) {
		printf("���ҳɹ�����Ҫ���ҵ������ұ��е�λ���ǣ�%d\n", index);
	}
	else{

		printf("����ʧ�ܣ���Ҫ���ҵ������ڲ��ұ��С�\n");
	}

	system("pause");
	return 0;
}
