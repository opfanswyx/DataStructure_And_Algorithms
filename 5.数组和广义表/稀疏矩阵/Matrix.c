#include "Matrix.h"

TSMatrix NewMatrix(int m, int n){
	//�½�һ����Ԫ���ʾ��ϡ�����   
	TSMatrix M;
	M.rows = m;
	M.cols = n;
	M.nums = 0;
	return M;
}
Status InsertElem(TSMatrix *M, int row, int col, ElemType value){
	//����Ԫ���ʾ��ϡ�����M���� row �У��� col ��λ�ò���Ԫ��value   
	//����ɹ�������0�����򷵻�-1   
	int i, t, p;
	if (M->nums >= MAXSIZE){//��ǰ��Ԫ�������   
		printf("\nError:There is no space in the matrix;\n");
		return 0;
	}
	//����Խ��
	if (row>M->rows || col>M->cols || row<1 || col<1){
		printf("\nError:Insert position is beyond the arrange.\n");
		return -1;
	}
	p = 1;//��־��Ԫ��Ӧ�ò����λ��   
	if (M->nums == 0){//����ǰ����Mû�з���Ԫ��   
		M->data[p].row = row;
		M->data[p].col = col;
		M->data[p].value = value;
		M->nums++;
		return 0;
	}
	for (t = 1; t <= M->nums; t++)//Ѱ�Һ��ʵĲ���λ��  
	{
		//�бȵ�ǰ�д�p++
		if (row > M->data[t].row)
			p++;
		//����ȵ����бȵ�ǰ�д�,p++
		if ((row == M->data[t].row) && (col > M->data[t].col))
			p++;
	}
	//����ǰ����λ���������ݣ��������ֵ
	if (row == M->data[t - 1].row && col == M->data[t - 1].col){
		M->data[t - 1].value = value;
		return 0;
	}
	for (i = M->nums; i >= p; i--){//�ƶ�p֮���Ԫ��   
		M->data[i + 1].row = M->data[i].row;
		M->data[i + 1].col = M->data[i].col;
		M->data[i + 1].value = M->data[i].value;
	}
	//������Ԫ��   
	M->data[p].row = row;
	M->data[p].col = col;
	M->data[p].value = value;
	M->nums++;
	return 0;
}


Status sMatrixTranspose(const TSMatrix *M, TSMatrix *N){
	//������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T   
	int col, p, q;
	N->rows = M->cols;
	N->cols = M->rows;
	N->nums = M->nums;
	if (N->nums){
		q = 1;
		for (col = 1; col <= M->rows; col++)
		for (p = 1; p <= M->nums; p++)
		if (M->data[p].col == col){
			N->data[q].row = M->data[p].col;
			N->data[q].col = M->data[p].row;
			N->data[q].value = M->data[p].value;
			q++;
		}
	}
	return OK;
}

Status sMatrixFastTranspose(const TSMatrix *M, TSMatrix *N)
{
	//����N�ĳ�Ա��ʼ��
	N->rows = M->cols;
	N->cols = M->rows;
	N->nums = M->nums;
	if (N->nums)	//����������з���Ԫ��
	{
		int col;		//����������±�
		int num[COLS + 1] = { 0 }, cpot[COLS + 2] = { 0 };
		int t;
		for (t = 1; t <= M->cols; t++)
			num[M->data[t].col]++;		//��M��ÿһ���з���Ԫ�ظ���
		cpot[1] = 1;	//��һ�еĵ�һ������Ԫ�ص�λ�ÿ϶���1
		for (col = 2; col <= M->nums; col++)
			//��col�еĵ�һ������Ԫ�ص�λ�ã�
			//������ǰһ�еĵ�һ������Ԫ�ص�λ�ã����ϸ��з���Ԫ�صĸ���
			cpot[col] = cpot[col - 1] + num[col - 1];
		int p, q;
		for (p = 1; p <= M->nums; p++)
		{
			col = M->data[p].col;
			q = cpot[col];
			N->data[q].row = M->data[p].col;
			N->data[q].col = M->data[p].row;
			N->data[q].value = M->data[p].value;
			cpot[col]++;
		}
	}
	return 0;
}

void sMatrixPrint(const TSMatrix *M){
	//��ӡϡ���������Ԫ��   
	int i, j, p = 1;
	printf("\nsize:%d �� %d\n", M->rows, M->cols);
	if (!M->nums){//0����   
		printf("%d\n", 0.0);
		return;
	}
	for (i = 1; i <= M->rows; i++){
		for (j = 1; j <= M->cols; j++){
			if (i == M->data[p].row && j == M->data[p].col){
				printf("%d\t", M->data[p].value);
				p++;
			}
			else{
				printf("%d\t", 0.0);
			}
		}
		printf("\n");
	}
	printf("\n");
}
