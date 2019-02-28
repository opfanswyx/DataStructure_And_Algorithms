#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 10  //哈希表长度

typedef struct
{
	int* elem;  //数组，动态分配
	int count;  //当前元素个数
}HashTable;

int m = 0;    //哈希表长，全局变量


//哈希表初始化
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

//构造哈希函数
int Hash(int key)
{
	return key%m; //除留余数法
}

//插入操作
void InsertHash(HashTable* h, int key)
{
	int addr = Hash(key); //求哈希地址
	while (h->elem[addr] != NULL)
		addr = (addr + 1) % m; //线性探测法处理冲突
	h->elem[addr] = key;
}

//查找
int SearchHash(HashTable h, int key, int *addr)
{
	*addr = Hash(key);  //求哈希地址
	while (h.elem[*addr] != key)
	{
		*addr = (*addr + 1) % m; //开放定址的线性探测
		if (h.elem[*addr] == NULL || *addr == Hash(key)) //如果循环回到原点
			return 0;   //说明关键字不存在
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
	
	int num;  //要查找的数据
	printf("请输入要查找的数据：\n");
	scanf("%d", &num);

	int addr = Hash(num);
	int ret = SearchHash(ht, num, &addr);
	if (ret)
		printf("查找成功！\n");
	else
		printf("查找失败！\n");

	system("pause");
	return 0;
}
