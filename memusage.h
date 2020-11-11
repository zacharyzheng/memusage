#ifndef __MEMUSAGE__
#define __MEMUSAGE__

#define MAX_LEN     255
#define HASH_MASK   0xFFUL


typedef struct node node_t;
struct node{
    void* p;
    unsigned int size;
    node_t* pre;
    node_t* next;
};

void *m_malloc(unsigned int size);
void m_free(void *p);
void m_info();

#endif
