#include<stdio.h>
#include<stdlib.h>
#define N 100000000
#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define COUNT 1+N/BITSPERWORD
unsigned long long int a[COUNT];
void set(unsigned long long int a[],unsigned long long int i)
{
	a[i>>SHIFT] |= (1<<(i&MASK));
}
void clr(unsigned long long int a[],unsigned long long int i)
{
	a[i>>SHIFT] &= ~(1<<(i&MASK));
}
unsigned long long int test(unsigned long long int a[],unsigned long long int i)
{
	return a[i>>SHIFT] & (1<<(i&MASK));
}
int main(int argc, char *argv[])
{
	unsigned long long int i,j;
	for(i=0; i<COUNT;i++)
		a[i] = -1;
	for(i=2;i<N;i++)
		if(test(a,i))
			for(j=i+i;j<N;j+=i)
				clr(a,j);
	for(i=N-1;i>2;i--)
		if(test(a,i))
		{
			printf("%llu ",i);
			break;
		}
	return 0;
}
