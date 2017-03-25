#ifndef A_STAR_H
#define A_STAR_H

//#include<stdlib.h>
//#include<math.h>
#include"binary_heap.h"
//#include <stdio.h>


//Open list最大长度
#define LIST_LEN 500
//step list最大长度
#define STEP_MAX_NUM 800
//二维数组行数
#define LINE_NUM 14
//二维数组列数
#define ROW_NUM 14


typedef struct opennode Open_node;


//初始化（具体数据结构具体实现）
void A_star_init();

//计算H值（A*权值之一）
int A_star_funH(int now_x ,int now_y ,int to_x, int to_y);

//用于二叉堆的比较函数
int cmp_max(const void* a,const void* b);
int cmp_min(const void* a,const void* b);

//将新open节点入列（根据数据结构实现）
int A_star_put_openlist(int x,int y, Open_node* node);

//维护两个step list，增*1，查*2，初始化*1
void add_step_list(int x,int y);
int get_step_list_x(int i);
int get_step_list_y(int i);
void init_step_list();

//新建一个Open_node节点并加进Open_list
void A_star_add_open_node(int x,int y,int g_num, int h_num, Open_node* fa);

//获得OPEN队列中最小权值节点（根据数据结构实现）,并将其从队列删除
Open_node* A_star_get_min_node();

//获得OPEN队列中最大权值节点（根据数据结构实现）,并将其从队列删除
Open_node* A_star_get_max_node();

//寻路算法(寻最短路)
int A_star(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y);

//寻路算法(寻最长路) 
int A_star_max(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y);

//三位置寻路第二步初始化
void A_star_special_init();

//三位置寻路（查看是否有A->B->C的路径）
int A_star_double(int map[][ROW_NUM],int head_x,int head_y,int tail_x,int tail_y,int bean_x,int bean_y);

//三位置寻最长路（查看是否有A->B->C的路径，其中，A->B尽可能长）
int A_star_double_max(int map[][ROW_NUM],int head_x,int head_y,int tail_x,int tail_y,int bean_x,int bean_y);

//获得下一步的坐标
int get_step_x();
int get_step_y();

//获得step_num
int get_step_num();




#endif