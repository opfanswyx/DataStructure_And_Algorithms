#include "gList.h"

//�����ĵݹ鴴��
void LSCreate(LSNode** ls)
{
	char ch;
	ch = getchar();
	if (ch == ')')
		*ls = NULL;
	else if (ch == '(')							//��ǰ�ַ�Ϊ������ʱ
	{
		*ls = (LSNode*)malloc(sizeof(LSNode));	//����һ���½��
		(*ls)->tag = 1;						//�½����Ϊ��ͷ���
		LSCreate(&((*ls)->value.Lists));	//�ݹ鹹���ӱ����ӵ���ͷ���
	}
	else
	{
		*ls = (LSNode*)malloc(sizeof(LSNode));	//����һ���½��
		(*ls)->tag = 0;						//�ǵ�Ԫ��
		(*ls)->value.atom = ch;				//�½����Ϊ��Ԫ�ؽ��
	}
	ch = getchar();								//ȡ��һ���ַ�	
	if ((*ls) == NULL);							//��δ���������������ֵܽ��
	else if (ch == ',')							//��ǰ�ַ�Ϊ","
		LSCreate(&((*ls)->link));			//�ݹ鹹���ֵܽ��	
	else									//û���ֵ��ˣ����ֵ�ָ����ΪNULL
		(*ls)->link = NULL;
	return;									//����
}

//�ݹ�����������
int LSDepth(LSNode *ls)
{
	if (ls->tag == 0)					//Ϊ��Ԫ��ʱ����0
		return 0;
	int max = 0, dep;
	LSNode *gls = ls->value.Lists;		//glsָ���һ��Ԫ�� 
	if (gls == NULL)					//�ձ���1
		return 1;
	while (gls != NULL)				 //��Ϊ�ձ������е�ÿһ��Ԫ��
	{
		if (gls->tag == 1)			 //Ԫ��Ϊ�ӱ�����
		{
			dep = LSDepth(gls);		 //�ݹ��������ӱ�����
			if (dep > max)			 //maxΪͬһ����������ӱ�������ֵ
				max = dep;
		}
		gls = gls->link;			//ʹglsָ����һ��Ԫ��
	}
	return (max + 1);				//���ر�����
}
//��������ls
void LSDis(LSNode *ls)
{
	if (ls->tag == 0)
		printf("%c", ls->value.atom);	//�����Ԫ��ֵ
	else
	{
		printf("(");
		if (ls->value.Lists == NULL)
			printf("");					//�ձ�ʲôҲ�����
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

//������ĳ���
int LSLength(LSNode *ls)
{
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
