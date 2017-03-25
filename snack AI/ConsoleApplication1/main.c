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
	//��ʼ��̰������Ϸ
	InitALL();
	
	while(1)
	{
		
		//����FX,���info��FX����һ����ô�ߣ�
		newFX=where_to_go(Snack_map,FX,score);
		FX = GET_FX(newFX);
		info = GET_INFO(newFX);

		//����õ���FX�Ǳ����ģ�ǿ�иı�FXʹ������һ�����Բ�����һ��û�ã�
		if(is_must_die(Snack_map,FX,get_snack_head_x(),get_snack_head_y()) == 1)
		{
			FX=get_rand_FX(Snack_map,FX);
		}
		
		//���bean_tail�棬��ֱ�Ӱ���·���н�
		if( GET_TO_BEAN_TAIL(newFX) == 0 ) // ||( info & 0x0FF) == 0x010 ||  (info & 0x0F0) == 0x000 )
		{
			int i;
			int step_num = get_step_num();
			for(i=step_num-1;i>=0;--i)
			{
				/*
				//������
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

