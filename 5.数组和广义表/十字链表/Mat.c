#include "Mat.h"
//����һ��ʮ��������ʹ������a��ʼ��
void cmatCreate(MatNode *&hm, ElemType a[ROW][COL])
{
	int i, j;
	//ͷ���ָ��
	MatNode *h[Max], *p, *q, *r;
	hm = (MatNode*)malloc(sizeof(MatNode));			//����ָ��hm
	hm->row = ROW;									//��ʼ����
	hm->col = COL;									//��ʼ����
	r = hm;
	for (i = 0; i < Max; i++)
	{
		h[i] = (MatNode*)malloc(sizeof(MatNode));
		h[i]->right = h[i];							//����ѭ��
		h[i]->down = h[i];
		r->tag.link = h[i];							//��ͷָ����������
		r = h[i];
	}
	r->tag.link = hm;								//��ָ������ָ�����ͷ���
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (a[i][j] != 0)						//��ֵ��ʼ��
			{
				p = (MatNode*)malloc(sizeof(MatNode));
				p->row = i;
				p->col = j;
				p->tag.value = a[i][j];
				q = h[i];
				//����������
				while (q->right != h[i] && q->right->col < j)
					q = q->right;
				p->right = q->right;
				q->right = p;
				q = h[j];
				//����������
				while (q->down != h[j] && q->down->row < i)
					q = q->down;
				p->down = q->down;
				q->down = p;
			}
		}
	}
}

void cmatPrint(MatNode *hm)
{
	MatNode *p, *q;
	printf("�� = %d���� = %d\n", hm->row, hm->col);
	p = hm->tag.link;
	while (p != hm)
	{
		q = p->right;
		while (p != q)
		{
			printf("(%d,%d,%d)\n", q->row + 1, q->col + 1, q->tag.value);
			q = q->right;
		}
		p = p->tag.link;
	}
}