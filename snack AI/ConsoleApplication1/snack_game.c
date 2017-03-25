#include "snack_game.h"

typedef struct SNACK
{
	int icon_id;
    int x;
    int y;
    Snack* next;
    Snack* prev;
}Snack;
typedef struct BEAN
{
	int icon_id;
    int x;
    int y;
}Bean;


int Snack_map[LINE_NUM][ROW_NUM]={0};

Snack* Snack_head=NULL;
Snack* Snack_tail=NULL;
Bean* bean=NULL;
int FX=KEY_RIGHT;
int score=0;
int snack_length=0;
//Snack->id从0到snack_length-1
//其对应的地图中的数是id+1，即1到snack_leng

void InitALL()
{
	int i,j;
	srand((unsigned int)time(NULL));
	Snack_head=NULL;
	Snack_tail=NULL;
	FX=6;
	score=0;
	snack_length=0;
	if(NULL == bean)
	{
		bean = (Bean*)malloc(sizeof(Bean));
	}
	for(i=0;i<LINE_NUM;++i)
	{
		for(j=0;j<ROW_NUM;++j)
		{
			Snack_map[i][j]=0;
		}
	}
	Creat_snack();
	Creat_bean();
	system("cls");
	//printf("8上5下4左6右\n");
	//printf("press any key to start\n");
	printf("init over\n");
	//getch();
}

static int Creat_snack()
{
    int i;
    for(i=0;i<BABY_SNACK_LENGTH;++i)
    {
        Snack* New_snack = (Snack*)malloc(sizeof(Snack));
		New_snack->icon_id=snack_length;
		New_snack->x =0;
		New_snack->y =i;
        New_snack->next = NULL;
        New_snack->prev = NULL;
		Snack_map[0][i]=++snack_length;
        if(NULL == Snack_tail)
        {
            Snack_tail=New_snack;
            Snack_head=New_snack;
        }
        else
        {
            Snack_head->next=New_snack;
            New_snack->prev=Snack_head;
            Snack_head=New_snack;
        }
    }
	return 0;
}

static void Creat_bean()
{
	int num = LINE_NUM*(ROW_NUM+5);
	bean->x = rand()%LINE_NUM;
	bean->y = rand()%ROW_NUM;
	while(num--)
	{
		
		if(0 == Snack_map[bean->x][bean->y])
		{
			/*int block_num=0;
			int all_block[8][2]={1,1,1,0,1,-1,-1,1,-1,0,-1,-1,0,1,0,-1};
			int block[4][2]={1,0,-1,0,0,1,0,-1};
			int i;
			for(i=0;i<4;++i)
			{
				if(bean->x + block[i][0] < 0 || bean->x + block[i][0] >= LINE_NUM || bean->y + block[i][1] < 0 || bean->y + block[i][1] >=ROW_NUM || Snack_map[bean->x + block[i][0] ][bean->y + block[i][1] ] != 0)
					continue;
				if(Snack_map[bean->x + block[i][0] ][bean->y + block[i][1] ] == 0)
					block_num++;
			}
			if(block_num >= 1)
			{
				Snack_map[bean->x][bean->y]=1;		
				return;
			}*/
			Snack_map[bean->x][bean->y]=1;
			return ;
		}
		bean->y++;
		if(bean->y >= ROW_NUM)
		{
			bean->y=0;
			bean->x++;
		}
		if(bean->x >= LINE_NUM)
		{
			bean->x = 0;

		}
	}
	if(num <= 0)
	{
		bean->x = -1;
		bean->y = -1;
	}
	else
		Snack_map[bean->x][bean->y]=1;
}

void Show()
{
	int i=1000,j;
	//system("cls");
	printf("score:%3d",score);
	//printf("|");
	for(j=4;j<ROW_NUM;++j)
	{
		printf("--");
	}
	printf("|\n");
	for(i=0;i<LINE_NUM;++i)
	{
		
		printf("|");
		for(j=0;j<ROW_NUM;++j)
		{
			if(i==bean->x && j==bean->y)
				printf("@ ");
			else if(i == Snack_head->x && j == Snack_head->y)
				printf("# ");
			else if(i == Snack_tail->x && j == Snack_tail->y)
				printf("+ ");
			else
				printf(Snack_map[i][j]?"* ":"  ");
			/*else if(Snack_map[i][j]==0)
				printf("    ");
			else
				printf("%3d ",(Snack_map[i][j]-1-1-Snack_head->icon_id + snack_length)%snack_length);*/
		}
		printf("|\n");
		

	}
	printf("|");
	for(j=0;j<ROW_NUM;++j)
	{
		printf("--");
	}
	printf("|\n");
		
	//Sleep(400);
}

int move()
{
	int snack_nextx,snack_nexty;
	int judge_result;
	switch (FX)
	{
	case KEY_RIGHT :
		snack_nextx=Snack_head->x ;
		snack_nexty=Snack_head->y + 1;
		break;
	case KEY_LEFT:
		snack_nextx=Snack_head->x ;
		snack_nexty=Snack_head->y - 1;
		break;
	case KEY_UP:
		snack_nextx=Snack_head->x - 1;
		snack_nexty=Snack_head->y;
		break;
	case KEY_DOWN:
		snack_nextx=Snack_head->x + 1;
		snack_nexty=Snack_head->y;
		break;
	};

	judge_result = judge(snack_nextx,snack_nexty);
	//死了
	if(judge_result == -1)
	{
		return -1;
	}
	//没吃到,没死
	else if(judge_result == 0)
	{
		//蛇尾弹出
		Snack_map[Snack_tail->x][Snack_tail->y]=0;
		Snack_tail=Snack_tail-> next;
		free(Snack_tail->prev);
		Snack_tail->prev=NULL;
	}
	//无合法豆子可生成
	else if(judge_result == 2)
	{
		return 2;
	}
	//吃到了
	else
	{
		int i;
		Snack* corrent=Snack_tail;
		for(i=0;i<snack_length;++i)
		{
			corrent->icon_id=i;
			Snack_map[corrent->x][corrent->y]=i+1;
			corrent=corrent->next;
		}
		score++;
		snack_length++;
		Snack_map[snack_nextx][snack_nexty]=snack_length+1;
		Creat_bean();
	}
	//蛇头加入
	Snack_head->next = (Snack*)malloc(sizeof(Snack));
	Snack_head->next->icon_id = (Snack_head->icon_id+1)%snack_length;	
	Snack_head->next->x=snack_nextx;
	Snack_head->next->y=snack_nexty;
	Snack_head->next->next=NULL;
	Snack_head->next->prev =Snack_head;
	Snack_head=Snack_head->next;
	Snack_map[snack_nextx][snack_nexty]=Snack_head->icon_id+1;
	return 0;
}

int input()
{
	char a=FX+'0';
	int New_FX=FX;
	int i=10;
	//延时
    while(i--)
    {
		if(kbhit()!=0)
		{
			while(kbhit() != 0)//有多个按键则以最后一个为主
               a = getch();
		}
        Sleep(10);
    }
	New_FX=(int)a-'0';
    if(New_FX==KEY_DOWN || New_FX==KEY_UP || New_FX==KEY_LEFT || New_FX==KEY_RIGHT)
	{
		return New_FX;
	}
	else
	{
		return FX;
	}
}

//吃到返回1,正常返回0，死了返回-1
static int judge(int nx,int ny)
{
	//吃到豆子
	if(nx==bean->x && ny == bean->y)
	{
		return 1;
	}
	//撞到身体
	else if(0 != Snack_map[nx][ny] && (nx!=Snack_tail->x || ny!=Snack_tail->y))
	{
		return -1;
	}
	//越界
	else if( nx<0 || nx>LINE_NUM-1 || ny<0 || ny>ROW_NUM-1 )
	{
		return -1;
	}
	//无合法豆子可生成
	else if(bean->x == -1 && bean->y == -1)
	{
		return 2;
	}
	else
	{
		return 0;
	}

}

void play()
{
	char in;
	InitALL();
	while(1)
	{
		FX=input();
		if(move()==0)
		{

			Show();
		}
		else
		{
			system("cls");
			printf("YOU DIE \nscore:%d \n Press 'y'to play again or press other key to leave\n",score);
			in=getch();
			if(in=='y' || in == 'Y')
			{
				InitALL();
			}
			else
				break;
		}
	}
}

void snack_running(int newFX)
{
	char in='y';
	int move_return;
	FX=newFX;
	move_return=move();
	if(move_return==0)
	{
		if((score%20==0 || score > 170 || kbhit() != 0))
		{
			Show();
			printf("beanx:%2d,bean_y:%2d ,FX: %d\n",get_bean_x(),get_bean_y(),FX);
		}

	}
	else if(move_return == 2)
	{
		Show();
		printf("YOU WIN \nscore:%d \n Press 'y'to play again or press other key to leave\n",score);
		printf("beanx:%2d,bean_y:%2d ,FX: %d\n",get_bean_x(),get_bean_y(),FX);
		//Sleep(2000);
		
		in=getch();
		if(in=='y' || in == 'Y')
		{
			InitALL();
		}
		else
			return;		
	}
	else
	{
		Show();
		printf("YOU DIE \nscore:%d \n Press 'y'to play again or press other key to leave\n",score);
		//printf("beanx:%2d,bean_y:%2d,BT,t,b: %03x ,FX: %d\n",get_bean_x(),get_bean_y(),info,FX);
		in=getch();
		if(in=='y' || in == 'Y')
		{
			InitALL();
		}
		else
			return;			
	}

}

int get_snack_head_x()
{
	return Snack_head->x;
}
int get_snack_head_y()
{
	return Snack_head->y;
}
int get_snack_tail_x()
{
	return Snack_tail->x;
}
int get_snack_tail_y()
{
	return Snack_tail->y;
}
int get_bean_x()
{
	return bean->x;
}
int get_bean_y()
{
	return bean->y;
}

int get_snack_x(int index)
{
	int i;
	Snack* corrent=Snack_tail;
	for(i=0;i<index;++i)
	{
		if(corrent != NULL)
			corrent=corrent->next;
	}
	if(corrent != NULL)
	{
		return corrent->x;
	}
	else
	{
		return -1;
	}
}
int get_snack_y(int index)
{
	int i;
	Snack* corrent=Snack_tail;
	for(i=0;i<index;++i)
	{
		if(corrent != NULL)
			corrent=corrent->next;
	}
	if(corrent != NULL)
	{
		return corrent->y;
	}
	else
	{
		return -1;
	}
}