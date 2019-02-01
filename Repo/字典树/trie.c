#include "trie.h"
#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define TRIE_NODE_MAX 26

typedef struct trie_node_t trie_node_t;

struct trie_node_t
{
    int count;      //用来计算前缀数
    bool is_str;    //用来标识到此的字符串
    trie_node_t *word[TRIE_NODE_MAX];
};

trie_node_t* trie_node_create()
{
    trie_node_t* node=(trie_node_t*)malloc(sizeof(trie_node_t));
    memset(node, 0, sizeof(trie_node_t));       //node->is_str = 0;
    return node;
}

void trie_node_destroy(trie_node_t *node)
{
    free(node);
}

typedef struct private_word_trie_t private_word_trie_t;
struct private_word_trie_t
{
    word_trie_t public;
    trie_node_t *root;
};

bool insert(private_word_trie_t *this, char *str)
{
    printf("comming insert function...\n");
    trie_node_t *current=this->root;
    int word_pos;
    while(*str)
    {
        word_pos = *str-'a';
        if(current->word[word_pos] == NULL)
        {
            current->word[word_pos]=trie_node_create();
        }
        current=current->word[word_pos];
        
        str++;
    }
    current->count++;
    current->is_str = true;
    return true;
}

bool find_word(private_word_trie_t *this, char *str)
{
    printf("comming find_word function...\n");
    trie_node_t *current = this->root;
    int word_pos;
    while(*str)
    {
        word_pos = *str-'a';
        if((current = current->word[word_pos]) == NULL)
        {
            return false;
        }
        str++;
    }
    return current->is_str;
}

int find_prefix(private_word_trie_t *this, char *str)
{
    trie_node_t *current = this->root;
    int word_pos;
    while(*str)
    {
        word_pos=*str-'a';
        if((current = current->word[word_pos]) == NULL)
        {
            return 0;
        }
        str++;
    }
    return current->count;
}

bool delete(private_word_trie_t *this, char *str)
{
    trie_node_t *current = this->root;
    int word_pos;
    trie_node_t *del = NULL;
    if(find_word(this,str))
    {
        while(*str)
        {
            word_pos = *str-'a';
            if(((current->word[word_pos])->count--) == 0)
            {
                del=current->word[word_pos];
                current->word[word_pos] = NULL;
                str++;
                break;
            }
            str++;
        }

        if(del!=NULL)
        {
            while(*str)
            {
                word_pos = *str-'a';
                current = del;
                del=current->word[word_pos];
                trie_node_destroy(current);
                str++;
            }
            trie_node_destroy(del);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void trie_destroy(trie_node_t *node)
{
    int i;
    for(i=0; i<TRIE_NODE_MAX; i++)
    {
        if(node->word[i]!=NULL)
        {
            trie_destroy(node->word[i]);
        }
    }
    trie_node_destroy(node);
}

void destroy(private_word_trie_t *this)
{
    trie_destroy(this->root);
    free(this);
}

word_trie_t *word_trie_create()
{
    private_word_trie_t *this = (private_word_trie_t *)malloc(sizeof(private_word_trie_t));
    this->public.insert = (bool (*)(word_trie_t *, char *))insert;
    this->public.find_word = (bool (*)(word_trie_t *, char *))find_word;
    this->public.find_prefix = (int (*)(word_trie_t *, char *))find_prefix;
    this->public.delete = (bool (*)(word_trie_t *, char *))delete;
    this->public.destroy=(void (*)(word_trie_t *))destroy;
    this->root = trie_node_create();
    return &this->public;
}

int main()
{
    word_trie_t *tree=word_trie_create();
    char str[100];
    while(gets(str)&&str[0])
    {
        printf("input str: [%s]\n",str);
        tree->insert(tree,str);
    }

    while(gets(str)&&str[0])
    {
        printf("前缀：%d\n",tree->find_prefix(tree,str));
        if(tree->find_word(tree,str))
        {
            printf("%s是插入的一个字符串\n",str);
        }
        else
        {
            printf("%s不是一个插入的字符串\n",str);
        }
    }
    tree->destroy(tree);
    return 1;
}
