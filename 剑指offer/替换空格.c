#include<stdio.h>
#define true 1
#define false 0

void ReplaceBlank(char string[], int length)
{
    if(string == NULL || length <= 0)
        return;
    int orignalLength = 0;
    int numberOfBlank = 0;
    int i = 0;
    while(string[i] != '\0')
    {
        orignalLength++;
        if(string[i] == ' ')
            numberOfBlank++;
        i++;
    }
    int newLength = orignalLength + numberOfBlank * 2;
    if(newLength > length)
        return;
    
    int indexOfOriginal = orignalLength;
    int indexOfNew = newLength;
    while(indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)
    {
        if(string[indexOfOriginal] == ' ')
        {
            string[indexOfNew--] = '0';
            string[indexOfNew--] = '2';
            string[indexOfNew--] = '%';
        }
        else
            string[indexOfNew--] = string[indexOfOriginal];
        
        --indexOfOriginal;
    } 
}
/* test */
int main(int argc, char **argv)
{
    int capacity = 18;
    char str[18] = "we are happy.";
    printf("before replace str [%s]\n",str);
    ReplaceBlank(str,capacity);
    printf("after replace str [%s]\n",str);
    return 0;
}