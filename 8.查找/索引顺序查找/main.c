#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//索引顺序查找（分块查找）
struct indexBlock   //定义块的结构
{
	int max;
	int start;
	int end;
} indexBlock[4];   //定义索引表，里面有4个struct对象

int blockSearch(int key, int a[])
{
	int i = 0;
	int j;

	while (i<3 && key>indexBlock[i].max) //确定在哪个子表中 
		i++;

	if (i >= 3)  //大于分的块数，则返回-1,找不到该数     
		return -1;

	j = indexBlock[i].start;    //j等于块范围的起始值

	while (j <= indexBlock[i].end && a[j] != key) //在确定的块内进行查找  
		j++;

	if (j > indexBlock[i].end) //如果大于块范围的结束值，则说明没有要查找的数，j置为-1     
		j = -1;

	return j;
}

int main()
{
	int j = -1;
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }; //查找表
	printf("已知查找表:\n");
	for (int i = 0; i < 15; i++) 
		printf("%d ", a[i]);

	printf("\n");

	for (int i = 0; i < 3; i++) 
	{
		indexBlock[i].start = j + 1; //确定每个块范围的起始值
		j = j + 1;

		indexBlock[i].end = j + 3;   //确定每个块范围的结束值
		j = j + 3;

		indexBlock[i].max = a[j];    //确定每个块范围中元素的最大值
	}

	printf("请输入你要查找的数：\n");
	int key;
	scanf("%d", &key);
	int index = blockSearch(key, a);

	if (index >= 0) {
		printf("查找成功！你要查找的数查找表中的位置是：%d\n", index);
	}
	else{

		printf("查找失败！你要查找的数不在查找表中。\n");
	}

	system("pause");
	return 0;
}
