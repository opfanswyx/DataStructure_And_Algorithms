#include<stdio.h>
#define true 1
#define false -1

int Find(int *matrix, int rows, int columns, int number)
{
    int find = false;
    int row = 0;
    int col = columns - 1;
    if(matrix == NULL && rows <= 0 && columns <= 0)
        return false;   /* 注意数组与待查找元素不能与false值相等 */
    while(row < rows && col >= 0)
    {
        printf("data[%d]\n",matrix[row*columns+col]);
        if(matrix[row*columns+col] == number)
            return true;
        else if(matrix[row*columns+col] > number)
            col--;
        else
            row++;
    }
    return false;
}
/* test */
int main(int argc, char **argv)
{
    int num[][4] = {{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
    if(true == Find((int *)num,4,4,7))
        printf("find it\n");
    else
        printf("nothing\n");
    return 0;
}