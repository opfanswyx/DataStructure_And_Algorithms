#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void getNext(char *t, int *next)
{
	int i=0,j=-1;
	next[0]=-1;
	int n=0;
	while(t[i]!='\0')
	{
		if(j==-1||t[i]==t[j])
		{
			i++;
			j++;
			if(t[i]!=t[j])
				next[i]=j;
			else
				next[i]=next[j];
		}
		else
		{
			j=next[j];
		}
	}
	for(n=0;n<i;n++)
	{
		printf("%d ",next[n]);
	}
	printf("\n");
}
int KMP(char *s,char *t,int next[])
{

	int len=0;
	char *temp=t;
	int i=0,j=0;
	int ret=-1;
	if(s==NULL||t==NULL)
	{
		return -1;
	}
	while(*temp++!='\0')
	{
		len++;
	}
	printf("len=%d\n",len);
	while((s[i]!='\0')&&((t[j]!='\0')||(j==-1))     //j=-1的时候t[-1]会异常
	{
		
		if(j==-1||s[i]==t[j])
		{
			i++;
			j++;
			printf("1..i=%d\tj=%d\n",i,j);
		}
		else
		{
			j=next[j];
			printf("2..i=%d\tj=%d\n",i,j);
		}
		
		if(j==len)	//如果j的值等于模式t的大小，则证明t与s的匹配已经匹配到t末尾 
		{
			ret=i-len;
			break;
		}
	}
	if(ret!=-1)
	{
		return ret;
	}
	else
	{
		return -1;
	}
}
int main()
{
	char source[1024],target[100];
	int next[100];
	int ret=0;
	printf("please input source str:\n");
	scanf("%s",source);
	printf("please input target str:\n");
	scanf("%s",target);
	printf("source length:%d\n",strlen(source));
	printf("target length:%d\n",strlen(target));
	
	printf("target nums next:\n");
	getNext(target,next);
	
	ret=KMP(source,target,next);
	if(ret==-1)
	{
		printf("no find target in source %d\n",ret);
	}
	else
	{
		printf("find it!the first is%d\n",ret);
	}
	
	system("pause");
	return 0;
		
} 