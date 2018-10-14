#include <stdio.h>   
#include <stdlib.h>

#define OK 1   
#define ERROR 0   
#define TRUE 1   
#define FALSE 0  
#define ROWS 6
#define COLS 7  
#define MAXSIZE 100   

typedef int Status;
typedef int ElemType;
typedef struct{		//��Ԫ��ṹ   
	int row;		//�к�  
	int col;		//�к�
	ElemType value;//����Ԫ��ֵ   
}Triples;
typedef struct{
	Triples data[MAXSIZE + 1];//����Ԫ��Ԫ���data[0]����   
	int rows, cols, nums;//����������������ͷ���Ԫ�ظ���   
}TSMatrix;

//�½�һ����Ԫ���ʾ��ϡ�����   
TSMatrix NewMatrix(int m, int n);
//��ʹ����Ԫ���ʾ��ϡ�����M�в�������
Status InsertElem(TSMatrix *M, int row, int col, ElemType value);
//����ת�ã���ʹ����Ԫ���ʾ��ϡ�����Mת�ã�������N��
Status sMatrixTranspose(const TSMatrix *M, TSMatrix *N);
//����ת�ã���ʹ����Ԫ���ʾ��ϡ�����Mת�ã�������N��
Status sMatrixFastTranspose(const TSMatrix *M, TSMatrix *N);
//�����ӡ����ʹ����Ԫ���ʾ��ϡ�����M��ӡ����Ļ
void sMatrixPrint(const TSMatrix *M);
//����˷�
void mmult(Triples a[], Triples b[], Triples d[]);
