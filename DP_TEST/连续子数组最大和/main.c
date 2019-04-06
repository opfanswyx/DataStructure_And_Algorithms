#include<stdio.h>
#define FIRST_DEBUG     1
#define SECOND_DEBUG    2
#define THREE_DEBUG     3

#if (DEBUG & FIRST_DEBUG)
int GetMaxAddOfArray(int *arr, int sz)
{
    int SUM = -100000;   //给定一个足够小的最大值
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            int subOfArr = 0;  //临时最大值
            for (int k = i; k <= j; k++)
            {
                subOfArr += arr[k];
            }

            if (subOfArr > SUM)
            {
                SUM = subOfArr;
            }
        }
    }
    return SUM;
}

#elif (DEBUG & SECOND_DEBUG)
int GetMaxAddOfArray(int *arr, int sz)
{
    int SUM = -100000;   //给定一个足够小的最大值
    for (int i = 0; i < sz; i++)
    {
        int subOfArr = 0;  //临时最大值
        for (int j = i; j < sz; j++)
        {
            subOfArr += arr[j];

            if (subOfArr > SUM)
            {
                SUM = subOfArr;
            }
        }
    }
    return SUM;
}

#elif (DEBUG & THREE_DEBUG)
int GetMaxAddOfArray(int* arr, int sz)
{
    if (arr == NULL || sz <= 1)
        return 0;
    int MAX = arr[0];
    int sum = arr[0];
    for (int i = 1; i < sz; i++)
    {
        if (sum < 0)
            sum = arr[i];
        else
        {
            sum += arr[i];
        }

        if (sum > MAX)
            MAX = sum;
    }
    return MAX;
}

#else
int GetMax(int a, int b)   //得到两个数的最大值
{
    return (a) > (b) ? (a) : (b);
}

int GetMaxAddOfArray(int* arr, int sz)
{
    if (arr == NULL || sz <= 0)
        return 0;

    int Sum = arr[0];   //临时最大值
    int MAX = arr[0];   //比较之后的最大值

    for (int i = 1; i < sz; i++)
    {
        Sum = GetMax(Sum + arr[i], arr[i]);   //状态方程

        if (Sum >= MAX)
            MAX = Sum;
    }
    return MAX;
}
#endif

int main()
{
    int array[] = { 2, 3, -6, 4, 6, 2, -2, 5, -9 };
    int sz = sizeof(array) / sizeof(array[0]);
    int MAX = GetMaxAddOfArray(array, sz);
    printf("MAX = %d\n",MAX);
    return 0;
}
/* gcc -DDEBUG = 1 main.c */
