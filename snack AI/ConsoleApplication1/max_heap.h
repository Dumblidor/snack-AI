#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <stdio.h>
#include <stdlib.h>

#define MAXHEAP_MAX_LENGTH 30

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

#define PARENT(a) ( ( (a)-1 ) /2 )
#define LEFT_CHILD(a) ( (a) * 2 + 1 )
#define RIGHT_CHILD(a) ( (a) * 2 + 2 )

// 返回data在二叉堆中的索引
int maxheap_get_index(int data);

//得到最大值并将其删除
int maxheap_get_max_num();

//初始化
void maxheap_init();

//向下调整最大堆,start:被下调节点的起始位置(一般为0，表示从第1个开始) ,end: 截至范围(一般为数组中最后一个元素的索引)
static void maxheap_filterdown(int start, int end);

// 删除最大堆中的data,0成功1失败
int maxheap_remove(int data);

//最大堆的向上调整算法(从start开始向上直到0，调整堆)
static void maxheap_filterup(int start);

//将data插入到二叉堆中,0成功1失败
int maxheap_insert(int data);

//打印二叉堆
void maxheap_print();

#endif