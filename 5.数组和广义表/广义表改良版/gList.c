#include "gList.h"

//������ĳ���
int LSLength(LSNode *ls)
{
	if (ls == NULL)
		return 0;
	int n = 0;
	if (ls->tag == 0)			//Ϊ��Ԫ��ʱ����0
		return 1;
	ls = ls->value.Lists;		//glsָ������ĵ�һ��Ԫ��
	while (ls != NULL)
	{
		n++;					//�ۼ�Ԫ�ظ���
		ls = ls->link;
	}
	return n;
}

//����������
int LSDepth(LSNode *ls)
{
	if (ls->tag == 0)					//Ϊ��Ԫ��ʱ����0
		return 0;
	int max = 0, dep;
	LSNode *gls = ls->value.Lists;		//glsָ���һ��Ԫ�� 
	if (gls == NULL)					//�ձ���1
		return 1;
	while (gls != NULL)				   //��Ϊ�ձ������е�ÿһ��Ԫ��
	{
		if (gls->tag == 1)			  //Ԫ��Ϊ�ӱ�����
		{
			dep = LSDepth(gls);		 //�ݹ��������ӱ�����
			if (dep > max)		//maxΪͬһ����������ӱ�����ȵ����ֵ
				max = dep;
		}
		gls = gls->link;		//ʹglsָ����һ��Ԫ��
	}
	return (max + 1);			//���ر�����
}

//��������ls
void LSDis(LSNode *ls)
{
	if (ls->tag == 0)
		printf("%c", ls->value.data);	//���ԭ��ֵ
	else
	{
		printf("(");
		if (ls->value.Lists == NULL)
			printf("");
		else
			LSDis(ls->value.Lists);		//�ݹ�����ӱ�
		printf(")");
	}
	if (ls->link != NULL)
	{
		printf(",");
		LSDis(ls->link);
	}
}
//�������
void LSCreate(LSNode** ls, int flag)
{
	char ch;
	ch = getchar();
	if (ch == ')')
		*ls = NULL;
	else if (ch == '(')							//��ǰ�ַ�Ϊ������ʱ
	{
		*ls = (LSNode*)malloc(sizeof(LSNode));	//����һ���½��
		(*ls)->tag = 1;						//�½����Ϊ��ͷ���
		LSCreate(&((*ls)->value.Lists), flag + 1);	//�ݹ鹹���ӱ����ӵ���ͷ���
	}
	else if (ch == '\n')
	{
		(*ls)->link = NULL;
		return;
	}
	else
	{
		*ls = (LSNode*)malloc(sizeof(LSNode));	//����һ���½��
		(*ls)->tag = 0;						//�ǵ�Ԫ��
		(*ls)->value.data = ch;				//�½����Ϊ��Ԫ�ؽ��
	}
	if (flag == 0)
	{
		(*ls)->link = NULL;
		printf("%d\n", flag);
		return;
	}
	ch = getchar();								//ȡ��һ���ַ�	
	if ((*ls) == NULL);								//��δ���������������ֵܽ��
	else if (ch == ',')							//��ǰ�ַ�Ϊ","
		LSCreate(&((*ls)->link), flag);			//�ݹ鹹���ֵܽ��	
	else									//û���ֵ��ˣ����ֵ�ָ����ΪNULL
		(*ls)->link = NULL;
	printf("%d-", flag);
	return;									//����
}
