#ifndef A_STAR_H
#define A_STAR_H

//#include<stdlib.h>
//#include<math.h>
#include"binary_heap.h"
//#include <stdio.h>


//Open list��󳤶�
#define LIST_LEN 500
//step list��󳤶�
#define STEP_MAX_NUM 800
//��ά��������
#define LINE_NUM 14
//��ά��������
#define ROW_NUM 14


typedef struct opennode Open_node;


//��ʼ�����������ݽṹ����ʵ�֣�
void A_star_init();

//����Hֵ��A*Ȩֵ֮һ��
int A_star_funH(int now_x ,int now_y ,int to_x, int to_y);

//���ڶ���ѵıȽϺ���
int cmp_max(const void* a,const void* b);
int cmp_min(const void* a,const void* b);

//����open�ڵ����У��������ݽṹʵ�֣�
int A_star_put_openlist(int x,int y, Open_node* node);

//ά������step list����*1����*2����ʼ��*1
void add_step_list(int x,int y);
int get_step_list_x(int i);
int get_step_list_y(int i);
void init_step_list();

//�½�һ��Open_node�ڵ㲢�ӽ�Open_list
void A_star_add_open_node(int x,int y,int g_num, int h_num, Open_node* fa);

//���OPEN��������СȨֵ�ڵ㣨�������ݽṹʵ�֣�,������Ӷ���ɾ��
Open_node* A_star_get_min_node();

//���OPEN���������Ȩֵ�ڵ㣨�������ݽṹʵ�֣�,������Ӷ���ɾ��
Open_node* A_star_get_max_node();

//Ѱ·�㷨(Ѱ���·)
int A_star(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y);

//Ѱ·�㷨(Ѱ�·) 
int A_star_max(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y);

//��λ��Ѱ·�ڶ�����ʼ��
void A_star_special_init();

//��λ��Ѱ·���鿴�Ƿ���A->B->C��·����
int A_star_double(int map[][ROW_NUM],int head_x,int head_y,int tail_x,int tail_y,int bean_x,int bean_y);

//��λ��Ѱ�·���鿴�Ƿ���A->B->C��·�������У�A->B�����ܳ���
int A_star_double_max(int map[][ROW_NUM],int head_x,int head_y,int tail_x,int tail_y,int bean_x,int bean_y);

//�����һ��������
int get_step_x();
int get_step_y();

//���step_num
int get_step_num();




#endif