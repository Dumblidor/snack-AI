#ifndef SNACK_GAME_H
#define SNACK_GAME_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define LINE_NUM 14
#define ROW_NUM 14
#define BABY_SNACK_LENGTH 5
#define KEY_UP 8
#define KEY_DOWN 5
#define KEY_LEFT 4
#define KEY_RIGHT 6


typedef struct SNACK Snack;
typedef struct BEAN Bean;

void InitALL();
static int Creat_snack();
static void Creat_bean();
void Show();
int input();
int move();
static int judge(int nx,int ny);
void play();
void snack_running(int newFX);
int get_snack_head_x();
int get_snack_head_y();
int get_snack_tail_x();
int get_snack_tail_y();
int get_bean_x();
int get_bean_y();
//获得从蛇尾数第几个蛇身位置
int get_snack_x(int index);
int get_snack_y(int index);


#endif