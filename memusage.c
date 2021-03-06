#include <stdio.h>
#include <stdlib.h>
#include "memusage.h"

node_t *hash_table[MAX_LEN] = { NULL };
static unsigned long mem_size = 0;
static unsigned long max_mem_size = 0;
//void *malloc(size_t size)
void *m_malloc(unsigned int size)
{
    node_t *insert = NULL;
    void *p = malloc(size);
    if (p == NULL)
        goto END;

    node_t *cur = (node_t *)malloc(sizeof(node_t));
    if (cur == NULL) {
        free(p);
        p = NULL;
        goto END;
    } 
    cur->p = p;
    cur->size = size;    
    cur->pre  = NULL;
    cur->next = NULL;

    printf("hash key is %ld\n", ((unsigned long)p >> 4)&HASH_MASK);   
    if (hash_table[((unsigned long)p >> 4)&HASH_MASK] == NULL) {
        hash_table[((unsigned long)p >> 4)&HASH_MASK] = cur;    
    } else {
        insert = hash_table[((unsigned long)p >> 4)&HASH_MASK];
        while(insert->next != NULL)
            insert = insert->next;
        insert->next = cur;
        cur->pre = insert;
    }
    mem_size += size;
    if (mem_size > max_mem_size) {
        max_mem_size = mem_size;
    }
    printf("[%s] size is %d bytes, mem_size is %ld bytes, max_mem_size is %ld bytes\n", __func__, size, mem_size, max_mem_size);

END:
    return p;
}


void m_free(void* p)
{
    node_t *t = hash_table[((unsigned long)p >> 4)&HASH_MASK];
    if (t != NULL) {
        while(t->p != p)
        {
            if (t->next != NULL)
                t = t->next;
        }
        
        if(t->p == p) {
            mem_size = mem_size - t->size;
            if (t->pre != NULL)
                t->pre->next = t->next;
            else
                hash_table[((unsigned long)p >> 4)&HASH_MASK] = t->next;

            if (t->next != NULL)
                t->next->pre = t->pre;
            free(t);
        }
        printf("[%s] mem_size is %ld bytes, max_mem_size is %ld bytes\n", __func__, mem_size, max_mem_size);
    }
    free(p);
}


void m_info()
{
    printf("mem_size is %ld bytes, max_mem_size is %ld bytes\n", mem_size, max_mem_size);
}


unsigned long get_mem_size()
{
    return mem_size;
}


unsigned long get_max_mem_size()
{
    return max_mem_size;
}
