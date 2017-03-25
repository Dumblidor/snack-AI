#ifndef SNACK_AI_H
#define SNACK_AI_H

#include "A_star.h"
#include "snack_game.h"
#include <math.h>

//从 where_to_go返回值中得到FX
#define GET_FX(__NEWFX) (  (__NEWFX) & 0x00FF  )
//从 where_to_go返回值中得到info
#define GET_INFO(__NEWFX) (  ( (__NEWFX) >> 8 ) & 0x0FFF  )
//从 where_to_go返回值中得到to_bean_tail
#define GET_TO_BEAN_TAIL(__NEWFX) (  ( (__NEWFX) >> 16 ) & 0x000F  )
//从 where_to_go返回值中得到to_tail
#define GET_TO_TAIL(__NEWFX) (  ( (__NEWFX) >> 12 ) & 0x000F  )
//从 where_to_go返回值中得到to_bean
#define GET_TO_BEAN(__NEWFX) (  ( (__NEWFX) >> 8 ) & 0x000F  )


//根据下一步和当前步的位置计算方向
int get_dir(int nextx,int nexty,int nowx,int nowy);

//获得一个当前步不死的FX（然而并不随机，优先级：下左上右，蛇会顺时针跑）
int get_rand_FX(int map[][ROW_NUM],int FX);

//计算一个FX值并返回一些信息，返回的值有四部分，低20位前8位为一部分（FX），后12位每4位为一部分（info）
//信息分别为：19~16：是否能吃到豆子并回到蛇尾（to_bean_tail，0真）; 15~12:是否能直接走到蛇尾（to_tail，0真）; 11~8：是否能直接吃到豆子（to_bean，0真）; 7~0：FX值
int where_to_go(int Snack_map[][ROW_NUM],int FX,int score);

//看是否必死
int is_must_die(int Snack_map[][ROW_NUM],int FX,int head_x,int head_y);

#endif