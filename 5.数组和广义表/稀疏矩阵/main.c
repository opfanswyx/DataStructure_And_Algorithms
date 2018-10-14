#include "Matrix.h"
int main()
{
	//��������
	TSMatrix M = NewMatrix(6, 7);
	TSMatrix N;
	//������в�������
	InsertElem(&M, 1, 2, 11);
	InsertElem(&M, 1, 3, 21);
	InsertElem(&M, 2, 4, 2);
	InsertElem(&M, 3, 1, 92);
	InsertElem(&M, 3, 6, 85);
	InsertElem(&M, 4, 3, 12);
	InsertElem(&M, 5, 2, 26);
	InsertElem(&M, 6, 5, 10);
	//��ӡ����
	printf("\nM:");
	sMatrixPrint(&M);
	//��ӡʹ�÷���aת�õľ���
	sMatrixTranspose(&M, &N);
	printf("\nN(Transpose of M)����a:");
	sMatrixPrint(&N);
	//��ӡʹ�÷���bת�õľ���
	sMatrixFastTranspose(&M, &N);
	printf("\nN(Transpose of M)����b:");
	sMatrixPrint(&N);
	return 0;
}
