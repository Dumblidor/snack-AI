#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdlib.h>
#include "A_star.h"



//�õ�����
#define PARENT(a) ( ( (a)-1 ) /2 )
#define LEFT_CHILD(a) ( (a) * 2 + 1 )
#define RIGHT_CHILD(a) ( (a) * 2 + 2 )
//����Ԫ�����;�����0����NULL����Ȼ��һ����������д�ϰɣ�
#define NOTHING NULL

//ָ��������д�ŵ�Ԫ�����ͣ�ʹ��ʱ����Ϊ��Ҫ�����ͣ�
extern struct opennode;
typedef struct opennode Open_node;
typedef Open_node* BINARYHEAP_ELEMENT;

//ͷ
typedef struct _binaryheap_head Binaryheap_head;

//��ʼ��һ�������ͷ������󳤶�Ϊmax_element_num
Binaryheap_head* binaryheap_init(int max_element_num);

//���ݱȽϺ��������Ѳ���һ��ֵ��compare��������ֵ�ο�qsort��compare��������a����bǰ��ͷ���1������ͷ���0��
int binaryheap_insrt(Binaryheap_head* head, BINARYHEAP_ELEMENT element, int (*compare)(const void* element_a,const void* element_b));

//�õ��Ѷ�Ԫ�ص�ֵ�����ı�ѣ�
BINARYHEAP_ELEMENT binaryheap_get_top(Binaryheap_head* head);

//ɾ���Ѷ�Ԫ�أ�������compare����������
int binaryheap_delete_top(Binaryheap_head* head, int (*compare)(const void* element_a,const void* element_b));

//���Ƿ�Ϊ��
int binaryheap_isnull(Binaryheap_head* head);

//ɾ����������Ԫ�أ��൱�ڻص�init���״̬��
int binaryheap_reset(Binaryheap_head* head);

//free�����ѣ�����ͷ��㱾��
int binaryheap_free(Binaryheap_head* head);

#endif