#ifndef SNACK_AI_H
#define SNACK_AI_H

#include "A_star.h"
#include "snack_game.h"
#include <math.h>

//�� where_to_go����ֵ�еõ�FX
#define GET_FX(__NEWFX) (  (__NEWFX) & 0x00FF  )
//�� where_to_go����ֵ�еõ�info
#define GET_INFO(__NEWFX) (  ( (__NEWFX) >> 8 ) & 0x0FFF  )
//�� where_to_go����ֵ�еõ�to_bean_tail
#define GET_TO_BEAN_TAIL(__NEWFX) (  ( (__NEWFX) >> 16 ) & 0x000F  )
//�� where_to_go����ֵ�еõ�to_tail
#define GET_TO_TAIL(__NEWFX) (  ( (__NEWFX) >> 12 ) & 0x000F  )
//�� where_to_go����ֵ�еõ�to_bean
#define GET_TO_BEAN(__NEWFX) (  ( (__NEWFX) >> 8 ) & 0x000F  )


//������һ���͵�ǰ����λ�ü��㷽��
int get_dir(int nextx,int nexty,int nowx,int nowy);

//���һ����ǰ��������FX��Ȼ��������������ȼ����������ң��߻�˳ʱ���ܣ�
int get_rand_FX(int map[][ROW_NUM],int FX);

//����һ��FXֵ������һЩ��Ϣ�����ص�ֵ���Ĳ��֣���20λǰ8λΪһ���֣�FX������12λÿ4λΪһ���֣�info��
//��Ϣ�ֱ�Ϊ��19~16���Ƿ��ܳԵ����Ӳ��ص���β��to_bean_tail��0�棩; 15~12:�Ƿ���ֱ���ߵ���β��to_tail��0�棩; 11~8���Ƿ���ֱ�ӳԵ����ӣ�to_bean��0�棩; 7~0��FXֵ
int where_to_go(int Snack_map[][ROW_NUM],int FX,int score);

//���Ƿ����
int is_must_die(int Snack_map[][ROW_NUM],int FX,int head_x,int head_y);

#endif