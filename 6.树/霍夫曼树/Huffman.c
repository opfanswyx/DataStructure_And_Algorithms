#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_CODE_LENGTH 260// 符号表最大只能有256个节点
///////////////////////////////////////////////////////////////////////////////////////////////////
// 全局变量
///////////////////////////////////////////////////////////////////////////////////////////////////
const int BIT_WIDTH_CHAR = 8;
const int END_SYM_FLAG = 200;// 符号的范围是-127~128
int gl_total_node_num = 0;// 符号表的总长度
int gl_source_file_length = 0;// 源文件的总长度

struct node
{
    char code[MAX_CODE_LENGTH];
    long count;
    int checked;
    char sym;
    struct node* next,*left,*right;// left和right只在生成Huffman树的时候有用
};
///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型
///////////////////////////////////////////////////////////////////////////////////////////////////
// 压缩相关
struct node* generate_count(FILE*,struct node*);
struct node* generate_tree(struct node*);
void generate_code(struct node*list);
struct node* free_tree(struct node*list);
void generate_des_file(FILE*,FILE*,struct node*);
// 解压相关
struct node* de_get_sym_list(FILE*);
void de_generate_des_file(FILE*,FILE*,struct node*);
// 辅助函数
struct node* content_char(struct node*,char);
struct node* content_code(struct node* list,const char* ch);
struct node* create_new_node(char ch,int count);
struct node* insert_node(struct node *list,struct node *new_node);
void print_list(struct node *list);
struct node* get_smallest_node(struct node *list_addr);
///////////////////////////////////////////////////////////////////////////////////////////////////
// main函数
///////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char** argv)
{
    // 传的参数一定是三个：可执行程序 源文件 目标文件
    if(argc != 3)
    {
        printf("wrong number of parameters.\n");
        exit(0);
    }
    // 打开源文件
    FILE* source_file=fopen(argv[1],"rb");
    if(!source_file)
    {
        printf("cannot open source file.\n");
        exit(0);
    }
    // 获取文件长度，以实现进度条
    fseek(source_file,0,SEEK_END);
    gl_source_file_length = ftell(source_file);
    fseek(source_file,0,SEEK_SET);
    // 打开目标文件
    FILE* des_file=fopen(argv[2],"wb");
    if(!des_file)
    {
        printf("cannot open des file.\n");
        exit(0);
    }
    
    // 获取操作符
    struct node *list=NULL;
    char op;
    printf("compress(y) or decompress(n) or quit(q)?[y/n/q]");
    do{
        op=getchar();
    }
    while(op!='y' && op!='n' && op!='q');
    
    // quit
    if(op=='q')
    {
        printf("Thanks for using.");
    }
    // 压缩
    else if(op=='y')
    {
        list=generate_count(source_file,list);
        list=generate_tree(list);
        generate_code(list);
        list=free_tree(list);
        generate_des_file(source_file,des_file,list);
    }
    // 解压
    else if(op=='n')
    {
        list=de_get_sym_list(source_file);
        de_generate_des_file(source_file,des_file,list);
    }
    
    // 关闭文件
    if(fclose(source_file))
    {
        printf("cannot close source file!\n");
        exit(0);
    }
    if(fclose(des_file))
    {
        printf("cannot close des file!\n");
        exit(0);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// 压缩的相关函数
///////////////////////////////////////////////////////////////////////////////////////////////////
// 生成符号链表（含频率）
// 参数：源文件
// 参数：目标链表
// 返回值：符号链表
struct node* generate_count(FILE* f,struct node*list)
{
    printf("counting");
    int count=0;
    
    char ch;
    struct node *content_node;
    while(fread(&ch,sizeof(char),1,f)==1)
    {
        // 进度条
        count++;
        if(count%(gl_source_file_length/10+1)==0)
            printf(".");
        
        // 插入符号表
        content_node = content_char(list,ch);
        if(content_node)
            content_node->count++;
        else 
        {
            gl_total_node_num++;
            list=insert_node(list,create_new_node(ch,1));
        }
    }
    printf("\n");
    return list;
}
// 生成Huffman树
// 参数：符号链表
// 返回值：含有Huffman树的链表，非叶节点将插入到链表前面，并有左右孩子属性，叶节点没有左右孩子属性
struct node* generate_tree(struct node* list)
{
    printf("generate_tree");
    // 生成树
    for(int i=1;i<gl_total_node_num;i++)
    {
        // 进度条
        if(i%(gl_total_node_num/10+1)==0)
            printf(".");
        
        // 获取最小出现次数的两个符号，并生成新的节点插入符号表
        struct node *sm_left=get_smallest_node(list);
        struct node *sm_right=get_smallest_node(list);
        struct node *new_node=create_new_node('\0',sm_left->count+sm_right->count);
        new_node->left=sm_left;
        new_node->right=sm_right;

        list = insert_node(list,new_node);
    }
    printf("\n");
    return list;
}
// 递归的生成Huffman编码于符号链表
// 参数：Huffman树
void generate_code(struct node*list)
{
    // 生成Huffman编码
    if(!list)return;
    // 左子树扩展'0'
    if(list->left)
    {
        strcat(list->left->code,list->code);
        strcat(list->left->code,"0");
        generate_code(list->left);
    }
    // 右子树'1'
    if(list->right)
    {
        strcat(list->right->code,list->code);
        strcat(list->right->code,"1");
        generate_code(list->right);
    }
}
// 释放Huffman树的非叶子节点，只留下符号链表
// 参数：Huffman树
// 返回值：不含Huffman树的符号链表
struct node* free_tree(struct node*list)
{
    struct node*free_node=list;
    while(list->left && list->right)// 左右子树不为空的节点都是需要释放的
    {
        free_node=list;
        list=list->next;
        free(free_node);
    }
    return list;
}
// 生成目标文件
// 参数：源文件
// 参数：目标文件
// 参数：符号链表
void generate_des_file(FILE* sf,FILE* df,struct node*list)
{
    printf("generate_des_file");
    // 符号表以文本形式写入到目标文件的前端，解压时需要的信息
    struct node* index=list;
    while(index)
    {
        fprintf(df,"%d %s ",index->sym,index->code);
        index=index->next;
    }
    // 指示结尾，"END"实际上没有用到，只用于和END_SYM_FLAG配对
    fprintf(df,"%d %s\n",END_SYM_FLAG,"END");
    
    // 实际文件内容（二进制形式）
    // 前者是从源文件中读取的字符，后置是对Huffman编码进行二进制形式转换后取8位形成的字符
    char ch,des_ch='\0';
    // 目标字符知否足够8位可以进行写入？
    int des_ch_length=0;
    // 因为之前进行了读取，所以这里回到文件头
    fseek(sf,0,SEEK_SET);
    int count=0;
    while(fread(&ch,sizeof(char),1,sf)==1)
    {
        // 进度条
        count++;
        if(count%(gl_source_file_length/10+1)==0)
            printf(".");
        
        // 在符号表中找这个字符
        // 没有找到一定是出错了
        struct node *content_node = content_char(list,ch);
        if(!content_node)
        {
            printf("error:cannot match with sym list\n");
            exit(0);
        }
        
        // 对这个符号对应的Huffman编码进行二进制转化
        char* current_code=content_node->code;
        for(int i=0;i<strlen(current_code);i++)
        {
            // 每次循环左移一位，长度+1
            des_ch=des_ch<<1;
            des_ch_length++;
            // 末位默认位0，否则置1
            if(current_code[i]=='1')des_ch |= (char)1;
            
            // 已经足够了一个字符，就写入，并清0
            if(des_ch_length==8)
            {
                if(!fwrite(&des_ch,sizeof(char),1,df))
                {
                    printf("error:cannot write to des file.\n");
                    exit(0);
                }
                des_ch_length=0;
                des_ch=0;
            }// 形成了一个字符
        }// Huffman编码
    }// 读源文件
    //printf("gen end:\t%ld\n",ftell(sf));
    // 最后一个字符，没有满足8位
    if(des_ch_length!=0)
    {
        des_ch=des_ch<<BIT_WIDTH_CHAR-des_ch_length;
        if(!fwrite(&des_ch,sizeof(char),1,df))
        {
            printf("error:cannot write to des file.\n");
            exit(0);
        }
    }
    // 最后这个一定是一个字符（1-8），表示最后一个有效字符的长度
    fprintf(df,"%d",des_ch_length);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// 解压相关的函数
///////////////////////////////////////////////////////////////////////////////////////////////////
// 获取文件头的符号表
// 参数：源文件
// 返回值：符号表
struct node* de_get_sym_list(FILE* f)
{
    printf("getting sym list...\n");
    
    char code[MAX_CODE_LENGTH];
    int ch_int;
    struct node* list=NULL;
    
    fscanf(f,"%d %s",&ch_int,code);
    // 如果没有读到结束标志
    while(ch_int!=END_SYM_FLAG)
    {
        // 创建新节点并插入符号表
        struct node* new_node=create_new_node((char)ch_int,0);
        strcpy(new_node->code,code);
        list=insert_node(list,new_node);
        fscanf(f,"%d %s",&ch_int,code);
    }
    fgetc(f);// 将换行符读掉，按照生成的规则，最后是一个换行符
    return list;
}

// 生成解压后的文件
// 参数：源文件
// 参数：目标文件
// 参数：符号链表
void de_generate_des_file(FILE* sf,FILE* df,struct node* list)
{
    printf("generating des file");
    
    char ch;
    // 存储未形成一个有效的Huffman编码的字符串
    char temp_code[MAX_CODE_LENGTH] = {'\0'};
    int last_length;// 最后一个字符的长度
    // 分别指向实际的压缩内容（去除头部的符号表）的头和尾
    long current_file_index,file_length;
    // 记录此时符号表读取结束的位置
    current_file_index = ftell(sf);
    // 从文件尾获取最后一个字符的长度，以及文件的长度
    fseek(sf,-(sizeof(char)),SEEK_END);
    file_length = ftell(sf);
    last_length = fgetc(sf)-'0';
    // 回复当前位置到符号表结束的位置
    fseek(sf,current_file_index,SEEK_SET);
    
    // 位操作的掩码，首位为1其余为0
    char mask=((char)1)<<BIT_WIDTH_CHAR-1;
    char append[]={'0','\0'};// 用于扩展Huffman编码的字符串
    struct node *the_node;
    // 读取除最后一个字符的所有内容
    for(int i=current_file_index;i<file_length-1;i++)
    {
        // 进度条
        if(i%((file_length-current_file_index)/10+1)==0)
            printf(".");
        // 读取是否成功
        if(fread(&ch,sizeof(char),1,sf)!=1)
        {
            if(ferror(sf))
                printf("error:cannot read file.\n");
            if(feof(sf))
                printf("end of reading file.\n");
            exit(0);
        }
        
        // 将这一个字符的每一位扩展到未竟的Huffman编码上
        for(int j=0;j<BIT_WIDTH_CHAR;j++)
        {
            append[0]='0' + ((ch & mask)==0?0:1);
            strcat(temp_code,append);
            ch=ch<<1;
            // 尝试在符号表中寻找
            the_node = content_code(list,temp_code);
            if(the_node)
            {
                // 如果找到了就把其代表的符号写入文件
                if(fwrite(&(the_node->sym),sizeof(char),1,df)!=1)
                {
                    printf("error:failed to write file.\n");
                    exit(0);
                }
                // 清零临时字符串
                temp_code[0]='\0';
            }// 如果在符号表中找到
        }// 对一个字符的每一位
    }// 除最后一个的所有字符
    // 最后一个字符
    if(fread(&ch,sizeof(char),1,sf)!=1)
    {
        printf("error:cannot read file.\n");
        exit(0);
    }
    for(int i=0;i<last_length;i++)
    {
        append[0]='0' + ((ch & mask)==0?0:1);
        strcat(temp_code,append);
        ch=ch<<1;
        // 尝试在符号表中寻找
        the_node = content_code(list,temp_code);
        if(the_node)
        {
            // 如果找到了就把其代表的符号写入文件
            if(fwrite(&(the_node->sym),sizeof(char),1,df)!=1)
            {
                printf("error:failed to write file.\n");
                exit(0);
            }
            // 清零临时字符串
            temp_code[0]='\0';
        }// 如果在符号表中找到
    }
    //结束之后一定是都清零了
    if(strlen(temp_code)!=0)
    {
        printf("error:code error.\n");
        exit(0);
    }
    printf("\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// 辅助函数
///////////////////////////////////////////////////////////////////////////////////////////////////
// 在链表中查找指定的字符
// 参数：符号表
// 参数：字符
// 返回值：找到的节点的指针
struct node* content_char(struct node* list,char ch)
{
    while(list)
    {
        if(list->sym == ch)
        {
            return list;
        }
        list=list->next;
    }
    return NULL;
}
// 在链表中查找指定编码
// 参数：符号表
// 参数：编码
// 返回值：找到的节点的指针
struct node* content_code(struct node* list,const char* code)
{
    while(list)
    {
        if(!strcmp(list->code,code))
        {
            return list;
        }
        list=list->next;
    }
    return NULL;
}
// 根据字符创建一个新的节点
// 参数：字符
// 参数：计数
// 返回值：新节点指针
struct node* create_new_node(char ch,int count)
{
    struct node *new_node = (struct node*)malloc(sizeof *new_node);
    if(!new_node)
    {
        printf("error:failed to malloc.\n");
        exit(0);
    }
    new_node->code[0]='\0';
    new_node->sym=ch;
    new_node->count=count;
    new_node->next=NULL;
    new_node->checked=0;
    new_node->left=NULL;
    new_node->right=NULL;
    return new_node;
}

// 插入新节点
// 参数list：目标链表
// 参数new_node：新节点
// 返回值：插入后的链表
struct node* insert_node(struct node *list,struct node *new_node)
{
    if(list)
        new_node->next=list;
    return new_node;
}

// 输出链表
// 参数list：目标链表
void print_list(struct node *list)
{
    printf("All nodes...\n");
    int count=0;
    while(list)
    {
        count++;
        printf("count:\t%d \tsym:\t%d\t checked:\t%d\t %s\n"
                ,list->count,list->sym,list->checked,list->code);
        list=list->next;
    }
    printf("print node count: %d\n",count);
}
// 获取到最小的未被检查的count的节点，返回它的指针，并将其设置为检查过的
// 参数list_addr：链表头
// 返回值：第一个未检查的最少出现次数的结点指针
struct node* get_smallest_node(struct node *list)
{
    while(list && list->checked)list=list->next;// 获取到首个未检查的节点
    struct node *smallest=list;
    // 获取到最小的count的节点
    while(list)
    {
        if(!list->checked && (list->count < smallest->count))
            smallest=list;
        list=list->next;
    }
    if(smallest)smallest->checked++;
    return smallest;
}

/* https://blog.csdn.net/qq_40711741/article/details/82855054 */