#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/* 声明变量 */
int array_length, file_length;
int *array_master;
FILE *freader;

/* 用于从文件读取数据 */
int *read_file(char *fname) 
{
	freader = fopen(fname, "rt"); /* 只读方式打开文件 */
	int bufsize = file_length; /* 数组规模 */
	char line[80];
	int integer;
	int index = 0;
	int *input = (int *)malloc(bufsize*sizeof(int)); /* 动态分配内存空间 */

	while (fgets(line, 80, freader) != NULL)
	{
		sscanf(line, "%d", &integer); /*从字符串 line 中获得整数（完成字符串到整数的转换）*/
		input[index] = integer;
		++index;
		++array_length;
	}

	fclose(freader); /* 关闭文件 */
	return input;
}

/* 求文件的行数（也就是数据量）*/
int read_length(char *fname) 
{
	freader = fopen(fname, "rt"); /* 以只读方式打开文件 */
	char line[80];
	int file_length = 0;

	/* fgets 从数据文件中读数据，每读一行的字符串
	（最长为80个字符），读到文件末尾 EOF，返回NULL */
	while (fgets(line, 80, freader) != NULL)
		file_length += 1;
	return file_length;
}

/* 归并函数 */
void merge(int arr[], int left, int middle, int right)
{
	int i, j, k;
	int half1 = middle - left + 1; /* 数组前一半的数据量 */
	int half2 = right - middle;  /* 数组后一半的数据量 */

	int first[half1], second[half2]; /* 声明两个临时数组，
									 保存前半部分数据和后半部分数据 */

	/* 从 arr 数组复制 left 到 right 之间前半部分的数据 */
	for (i = 0; i < half1; i++) 
		first[i] = arr[left + i]; 

	/* 从 arr 数组复制 left 到 right 之间后半部分的数据 */
	for (j = 0; j < half2; j++) 
		second[j] = arr[middle + 1 + j];

	i = 0;
	j = 0;
	k = left;

	/* 比较两个临时数组的数，找出当前最小的数，然后按序存入 arr */
	while (i < half1 && j < half2) 
	{

		if (first[i] <= second[j]) 
		{
			arr[k] = first[i];
			++i; 
		}
		else 
		{
			arr[k] = second[j];
			j++;
		}

		k++; /* arr 数组的索引 */
	}

	/* 将临时数组中剩余的数存入 arr 数组 */
	while (i < half1) 
	{
		arr[k] = first[i];
		i++;
		k++;
	}

	while (j < half2)
	{
		arr[k] = second[j];
		j++;
		k++;
	}
}

/* 归并排序函数 */
void* merge_sort(void* arg) 
{
	/* 变量声明 */
	int *arr = array_master; /* 指向全局变量 array_master 数组 */
	int *argu = (int*)arg;
	int l = argu[0]; /* 由线程传入的参数，获得要排序数据的最小索引值 */
	int r = argu[1]; /* 由线程传入的参数，获得要排序数据的最大索引值 */

	/* 若 l==r 则不必排序 */
	if (l < r) 
	{	
		/* 声明两个线程买描述符 */
		pthread_t tid1;
		pthread_t tid2;

		/* 声明调用线程处理函数的参数 */
		int arg1[2];
		int arg2[2];

		int middle;
		middle = (l + (r - 1)) / 2;
		arg1[0] = l;
		arg1[1] = middle;
		arg2[0] = middle + 1;
		arg2[1] = r;

		/* 由于用二分法对数组分成两部分分别排序，
		所以存在并行的可能，这里采用多线程 */
		pthread_create(&tid1, NULL, merge_sort, arg1);
		pthread_create(&tid2, NULL, merge_sort, arg2);

		/* 这里必须等待两部分数组都已排序完毕，才能进行归并，
		所以这里调用 pthread_join 使得线程同步 */
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);

		/* 此时归并两个已排序子序列 */
		merge(arr, l, middle, r);
		pthread_exit(0);
	}
    
    return NULL;
}

/* 主函数 */
int main(int argc, char *argv[])
{
	char *fname = argv[1];  /* 从命令行中读取数据文件 */

	/* 获取数据的长度 */
	file_length = read_length(fname);

	/* 从数据文件中读取数据 */
	array_master = read_file(fname);

	int arg[2];
	arg[0] = 0;
	arg[1] = file_length - 1;

	/* 创建线程执行归并排序 */
	pthread_t tid;
	pthread_create(&tid, NULL, merge_sort, arg);

	/* 进程同步 */
	pthread_join(tid, NULL);

	/* 打印已排序数组 */
	int j;
	for (j = 0; j < array_length; j++) 
	{
		if (j == array_length - 1) 
			printf("%d\n", array_master[j]); /* 打印已排序数组的最后一个元素 */
		
		else 
			printf("%d, ", array_master[j]); /* 打印已排序数组的非最后一个元素 */
	}

	return 0;
}
