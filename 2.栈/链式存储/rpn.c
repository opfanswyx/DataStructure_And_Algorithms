#include "linkstack.h"
char buffer[256] = {0};

void Put(char ch)
{
    static int index = 0;
    buffer[index++] = ch;
}
/* 优先级比较 */
int Priority(char ch)
{
    int ret = 0;
    switch(ch)
    {
        case '+':
        case '-':
            ret = 1;
            break;
        case '*':
        case '/':
            ret = 2;
            break;
        default:
            break;
    }
    return ret;
}
/* 判断字符是否是数字 */
int isNumber(char ch)
{
    return (ch >= '0' && ch <= '9');
}
/* 判断字符是否是运算符 */
int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}