#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <stdio.h>
#include <stdlib.h>

#define MAXHEAP_MAX_LENGTH 30

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

#define PARENT(a) ( ( (a)-1 ) /2 )
#define LEFT_CHILD(a) ( (a) * 2 + 1 )
#define RIGHT_CHILD(a) ( (a) * 2 + 2 )

// ����data�ڶ�����е�����
int maxheap_get_index(int data);

//�õ����ֵ������ɾ��
int maxheap_get_max_num();

//��ʼ��
void maxheap_init();

//���µ�������,start:���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ) ,end: ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
static void maxheap_filterdown(int start, int end);

// ɾ�������е�data,0�ɹ�1ʧ��
int maxheap_remove(int data);

//���ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
static void maxheap_filterup(int start);

//��data���뵽�������,0�ɹ�1ʧ��
int maxheap_insert(int data);

//��ӡ�����
void maxheap_print();

#endif