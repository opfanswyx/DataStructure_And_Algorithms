# include<stdio.h>
# include<string.h>

# define MAX 9999
# define MIN (-MAX)

# define K 4  //K路归并

FILE *p[K+1];
int b[K+1],ls[K]; //b为数据 ls为败者树

int inputdata(int v)
{
   int s,flag;
   flag=fscanf(p[v],"%d",&s);
      printf("Find %d  %d\n",flag,EOF);
   if (flag!=1) s=MAX;
   return s;
}

void adjust(int v)
{
   int t=(v+K)/2,temp;
   while (t>0)
   {
      if (b[v]>b[ls[t]])
      {
         temp=v;
         v=ls[t];
         ls[t]=temp;
      }
      t=t/2;
  }
  ls[0]=v;
}

void K_Merge()
{
   int i,q;
   for (i=0;i<K;i++) b[i]=inputdata(i);
   b[K]=MIN;
   for (i=0;i<K;i++) ls[i]=K;
   for (i=K-1;i>=0;i--) adjust(i);
   
   while (b[ls[0]]!=MAX)
   {
     q=ls[0];
     fprintf(p[K],"%d ",b[q]);
     b[q]=inputdata(q);
     adjust(q);
   }
}

void main()
{
   char innamespan[5]=".in";
   char outnamespan[5]=".out";
   int i;
   for (i=0;i<K;i++)
   {
      char filename[10]="f";
      char cnum[5];
      
      itoa(i+1,cnum,10);
      strcat(filename,cnum);
      strcat(filename,innamespan);
      
      p[i]=fopen(filename,"r");
   }
   p[K]=fopen("f.out","w");
   
   K_Merge();
   for (i=0;i<=K;i++) fclose(p[i]);
}
 
   