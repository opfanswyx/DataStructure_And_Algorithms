#define MAXD 8
typedef struct node
{
    char keys[MAXD];
    struct node* next;
}RecType;

void RadixSort(RecType *&p,int r,int d)
{
    RecType *head[MAXD], *tail[MAXD], *t;
    int i,j,k;
    for(i=d-1;i>=0;i--)
    {
        for(j=0;j<r;j++)
            head[j]=tail[j]=NULL;

        while(p!=NULL)
        {
            k=p->keys[i]-'0';
            if(head[k]==NULL)
            {
                head[k]=p;
                tail[k]=p;
            }
            else
            {
                tail[k]->next=p;
                tail[k]=p;
            }
            p=p->next;
        }
        p=NULL;

        for(j=0;j<r;j++)
        {
            if(head[j]!=NULL)
            {
                if(p==NULL)
                {
                    p=head[j];
                    t=tail[j];
                }
                else
                {
                    t->next=head[j];
                    t=tail[j];
                }
            }
        }
        t->next=NULL;
    }
}