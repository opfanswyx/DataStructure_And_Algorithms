#include "gList.h"
//���Դ���������
int main()
{
	LSNode *ls;
	printf("����������");
	LSCreate(&ls);
	LSDis(ls);
	int len = LSLength(ls);
	printf("\nlen = %d\n", len);
	int dep = LSDepth(ls);
	printf("dep = %d\n", dep);
	return 0;
}
