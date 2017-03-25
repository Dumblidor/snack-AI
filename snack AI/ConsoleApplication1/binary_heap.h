#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdlib.h>
#include "A_star.h"



//得到索引
#define PARENT(a) ( ( (a)-1 ) /2 )
#define LEFT_CHILD(a) ( (a) * 2 + 1 )
#define RIGHT_CHILD(a) ( (a) * 2 + 2 )
//根据元素类型决定是0还是NULL（虽然都一样，但还是写上吧）
#define NOTHING NULL

//指定二叉堆中存放的元素类型（使用时更改为需要的类型）
extern struct opennode;
typedef struct opennode Open_node;
typedef Open_node* BINARYHEAP_ELEMENT;

//头
typedef struct _binaryheap_head Binaryheap_head;

//初始化一个二叉堆头，其最大长度为max_element_num
Binaryheap_head* binaryheap_init(int max_element_num);

//根据比较函数向二叉堆插入一个值。compare函数返回值参考qsort的compare（你想让a排在b前面就返回1，否则就返回0）
int binaryheap_insrt(Binaryheap_head* head, BINARYHEAP_ELEMENT element, int (*compare)(const void* element_a,const void* element_b));

//得到堆顶元素的值（不改变堆）
BINARYHEAP_ELEMENT binaryheap_get_top(Binaryheap_head* head);

//删除堆顶元素，并按照compare函数重整堆
int binaryheap_delete_top(Binaryheap_head* head, int (*compare)(const void* element_a,const void* element_b));

//看是否为空
int binaryheap_isnull(Binaryheap_head* head);

//删除堆内所有元素（相当于回到init后的状态）
int binaryheap_reset(Binaryheap_head* head);

//free整个堆（包括头结点本身）
int binaryheap_free(Binaryheap_head* head);

#endif