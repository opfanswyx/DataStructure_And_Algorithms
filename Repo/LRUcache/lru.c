#include "uthash.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct _list {
    int key;
    int value;
    struct _list *next;
    struct _list *prev;
}d_list;
typedef struct my_struct {
    int key;            /* we'll use this field as the key */
    d_list *target;             
    UT_hash_handle hh; /* makes this structure hashable */
}h_table;
typedef struct {
    int _capacity;
    int size;
    d_list *head;
    d_list *tail;
    h_table *table;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *root;
    root = (LRUCache*)malloc(sizeof(LRUCache));
    root->_capacity = capacity;
    root->size = 0;
    root->head = NULL;
    root->tail = NULL;
    root->table = NULL;
    return root;
}

int lRUCacheGet(LRUCache* obj, int key) {
    h_table *s;
    d_list *p;
    
    if (obj->table == NULL)
        return -1;
    HASH_FIND_INT(obj->table, &key, s);
    if (s == NULL)
        return -1;
    p = s->target;
    if (p->prev == NULL) {
        return p->value;
    }
    
    p->prev->next = p->next;
    if (p->next == NULL) {
        obj->tail = p->prev;
    } else {
        p->next->prev = p->prev;
    }
    p->next = NULL;
    p->prev = NULL;
    p->next = obj->head;
    obj->head->prev = p;
    obj->head = p;
    
    return p->value;
}

void Display(LRUCache* obj) {
    d_list *p;
    p = obj->head;
    printf("list:");
    while (p != NULL) {
        printf("(%d,%d)", p->key, p->value);
        p = p->next;
    }
    printf("\n");
}

void MoveNode(LRUCache* obj, d_list* node) {
    if (node->prev == NULL) {
        return;
    }
    if (node->next == NULL) {
        obj->tail = node->prev;
        node->prev->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    
    node->next = obj->head;
    obj->head->prev = node;
    obj->head = node;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    d_list *d_node, *p;
    h_table *s, *ss = NULL;
    
    HASH_FIND_INT(obj->table, &key, s);
    if (s != NULL) {
        s->target->value = value;
        MoveNode(obj, s->target);
        return;
    } else {
        int f;
        d_node = (d_list*)malloc(sizeof(d_list));
        s = (h_table*)malloc(sizeof(h_table));
        d_node->key = key;
        d_node->value = value;
        s->key = key;
        s->target = d_node;
        HASH_ADD_INT(obj->table, key, s);
        
        if (obj->head == NULL || obj->head == NULL) {
            obj->head = d_node;
            obj->tail = d_node;
            d_node->prev = NULL;
            d_node->next = NULL;
            obj->size++;
            return;
        }
        if (obj->size < obj->_capacity) {
            obj->size++;
        } else {
            ss = (h_table*)malloc(sizeof(h_table));
            f = obj->tail->key;
            ss->key = f;
            HASH_FIND_INT(obj->table, &f, ss);
            HASH_DEL(obj->table, ss);
            p = ss->target;
            printf("(%d,   %d)\n", obj->tail->key,obj->tail->value);
            if (p->prev == NULL) {
                obj->tail = NULL;
                obj->head = NULL;
            } else {
                obj->tail = p->prev;
                p->prev->next = NULL;
            }
            p->prev = NULL;
            p->next = NULL;
            free(p);
        }
        if (obj->head == NULL) {
            obj->head = d_node;
            obj->tail = d_node;
            d_node->next = NULL;
            d_node->prev = NULL;
        } else {
            d_node->next = obj->head;
            obj->head->prev = d_node;
            obj->head = d_node;
            d_node->prev = NULL;
        }
    }
    return;
}

void lRUCacheFree(LRUCache* obj) {
    h_table *current_user, *tmp;
    d_list *p;
    if (obj->table != NULL) {
        HASH_ITER(hh, obj->table, current_user, tmp) {
            HASH_DEL(obj->table,current_user);  /* delete; users advances to next */
            free(current_user);            /* optional- if you want to free  */
        }
    }
    if (obj->head != NULL || obj->tail != NULL) {
        p = obj->head;
        while (p != NULL) {
            free(p);
            p = p->next;
        }
    }
}

int main()
{
    LRUCache *lrucache;
    int capacity = 3;
    int i;

    lrucache = lRUCacheCreate(capacity);

    for(i = 0; i < capacity; i++)
    {   
        printf("i=[%d]\n",i);
        lRUCachePut(lrucache,i,i);
    }

    for(i = 0; i < capacity; i++)
        printf("key=[%d]value=[%d]\n", i ,lRUCacheGet(lrucache,i));

    i = 100;
    printf("i=[%d]\n",i);
    lRUCachePut(lrucache,i,i);

    for(i = 0; i < capacity; i++)
        printf("key=[%d]value=[%d]\n", i ,lRUCacheGet(lrucache,i));

    lRUCacheFree(lrucache);

    return 0;
}