#include "snack_game.h"
#include "snack_AI.h"
#include "dfs.h"
//#include "binary_heap.h"

extern int Snack_map[LINE_NUM][ROW_NUM];
extern int FX;
extern int score;
extern int max_x_list[MAX_LIST_LEN];
extern int max_y_list[MAX_LIST_LEN];
extern int max_deep;

int newFX;
int info;

int main()
{
	//初始化贪吃蛇游戏
	InitALL();
	
	while(1)
	{
		
		//计算FX,解出info和FX（下一步怎么走）
		newFX=where_to_go(Snack_map,FX,score);
		FX = GET_FX(newFX);
		info = GET_INFO(newFX);

		//如果得到的FX是必死的，强行改变FX使得在这一步可以不死（一般没用）
		if(is_must_die(Snack_map,FX,get_snack_head_x(),get_snack_head_y()) == 1)
		{
			FX=get_rand_FX(Snack_map,FX);
		}
		
		//如果bean_tail真，则直接按照路径行进
		if( GET_TO_BEAN_TAIL(newFX) == 0 ) // ||( info & 0x0FF) == 0x010 ||  (info & 0x0F0) == 0x000 )
		{
			int i;
			int step_num = get_step_num();
			for(i=step_num-1;i>=0;--i)
			{
				/*
				//测试用
				if(info >> 8 == 0)
					printf("bean_tail");
				else if((info & 0x0FF) == 0x010)
					printf("bean");
				else
					printf("tail");
				printf("\n%d,%d\n",get_step_list_x(i),get_step_list_y(i));
				*/
				FX=get_dir(get_step_list_x(i),get_step_list_y(i),get_snack_head_x(),get_snack_head_y());
				//Sleep(400);
				/*if(is_must_die(Snack_map,FX,get_snack_head_x(),get_snack_head_y()) == 1)
				{
					FX=get_rand_FX(Snack_map,FX);
					break;
				}*/
				snack_running(FX);

				//printf("beanxy:%d  %d,can find tail?%d,can find bean? %d ,FX: %d\n",get_bean_x(),get_bean_y(),to_tail,to_bean,FX);
				Sleep(1);
			}
			//Sleep(900);
		}
		
		else
		{
			snack_running(FX);
			//printf("info: %03x\n",info);
			Sleep(1);
			//Sleep(400);
		}
//		Sleep(400);
	}

	//play();
	return 0;
}

