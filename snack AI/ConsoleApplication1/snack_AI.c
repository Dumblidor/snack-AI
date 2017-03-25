#include "snack_AI.h"

//snack_game�ķ���
extern int FX;

//A_star������step
extern int step_x,step_y;
extern int score;
//A_star�ĵ�ͼ
extern Open_node* A_star_map[LINE_NUM][ROW_NUM];
//A_star��open_list
extern Open_node* Open_node_list[LIST_LEN];


int get_dir(int nextx,int nexty,int nowx,int nowy)
{
	if(nextx > nowx)
		return 5;
	else if(nextx < nowx)
		return 8;
	else if(nexty > nowy)
		return 6;
	else if(nexty < nowy)
		return 4;
	else return -1;
}

int get_rand_FX(int map[][ROW_NUM],int FX)
{
	int where_move[4][2]={1,0,0,-1,-1,0,0,1};
	int where[4]={5,4,8,6};
	int rand_x,rand_y;
	int i,j;
	for(i=0;i<4;++i)
	{
		//�����ҵ���ǰFX��Ӧ����
		if(where[i] == FX)
		{
			rand_x=get_snack_head_x()+where_move[i][0];
			rand_y=get_snack_head_y()+where_move[i][1];		
			//�����ǰFX������
			if(map[rand_x][rand_y] == 0 && rand_x >=0 && rand_x<LINE_NUM && rand_y >=0 && rand_y < ROW_NUM)
			{
				FX=where[i];
				return FX;
			}
			//�����������һ����ǰ�Ϸ���FX�滻֮
			else
			{
				for(j=0;j<4;++j)
				{
					rand_x=get_snack_head_x()+where_move[j][0];
					rand_y=get_snack_head_y()+where_move[j][1];	
					//���һ��������
					if( map[rand_x][rand_y] == 0 && rand_x >=0 && rand_x<LINE_NUM && rand_y >=0 && rand_y < ROW_NUM )
					{
						FX=where[j];
						return FX;
					}
					//����Ƕ���
					else if(map[rand_x][rand_y] != 0 && (rand_x == get_bean_x() && rand_y == get_bean_y()))
					{
						FX = where[j];
						return FX;
					}
					else if(map[rand_x][rand_y] != 0 && (rand_x == get_snack_tail_x() && rand_y == get_snack_tail_y()))
					{
						FX = where[j];
						return FX;
					}
				}
			}
		}
	}
	return FX;
}

int where_to_go(int Snack_map[][ROW_NUM],int FX,int score)
{
	int to_tail=-1;
	int to_bean=-1;
	int to_whatever=-1;
	int to_bean_tail=-1;
	int to_bean_tail_max=-1;

	int go_tail_x,go_tail_y;
	int go_bean_x,go_bean_y;
	int go_bean_tail_x,go_bean_tail_y;
	int go_bean_tail_max_x,go_bean_tail_max_y;

	int bean_tail_distance=0;
	int i;
	int corrent_tail_x;
	int corrent_tail_y;


	//���Ƿ��ܳԵ����ӻص�β��
	bean_tail_distance= abs(get_snack_head_x() - get_bean_x())+ abs(get_snack_head_y() - get_bean_y());
	for(i=0;i<bean_tail_distance;++i)
	{
		corrent_tail_x=get_snack_x(i);
		corrent_tail_y=get_snack_y(i);
		A_star_init();
		if(corrent_tail_x != -1 && corrent_tail_y != -1)
			to_bean_tail=A_star_double(Snack_map,get_snack_head_x(),get_snack_head_y(),get_bean_x(),get_bean_y(),corrent_tail_x,corrent_tail_y);
		if(to_bean_tail == 0)
			break;
	}
	if(to_bean_tail == 0)
	{
		go_bean_tail_x=get_step_x();
		go_bean_tail_y=get_step_y();
		//�����Ƿ����·���Ե����ӻ�β��
		A_star_init();
		to_bean_tail_max=A_star_double_max(Snack_map,get_snack_head_x(),get_snack_head_y(),get_bean_x(),get_bean_y(),corrent_tail_x,corrent_tail_y);
		if(to_bean_tail_max == 0)
		{
			go_bean_tail_max_x=get_step_x();
			go_bean_tail_max_y=get_step_y();
		}
	}

	//�鿴�Ƿ��ܵ�β�ͣ�����ܣ���¼��һ����ô��
	A_star_init();
	Snack_map[get_bean_x()][get_bean_y()]=0;
	to_tail=A_star_max(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_snack_tail_x() ,get_snack_tail_y());
	Snack_map[get_bean_x()][get_bean_y()]=1;
	if(to_tail == 1)
	{
		A_star_init();
		Snack_map[get_bean_x()][get_bean_y()]=0;
		to_tail=A_star(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_snack_tail_x() ,get_snack_tail_y());
		Snack_map[get_bean_x()][get_bean_y()]=1;
	}
	if(to_tail==0)
	{
		go_tail_x=get_step_x();
		go_tail_y=get_step_y();
	}

	//�鿴�Ƿ��ܵ����ӣ�����ܣ���¼����һ����ô��
	A_star_init();
	to_bean=A_star(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_bean_x(), get_bean_y());
	if(to_bean == 0)
	{
		go_bean_x=get_step_x();
		go_bean_y=get_step_y();
	}



////////////////////////  ��·����  ///////////////////////////////////////////////////////////////////////////////////////////////////////////		


	//����Ե�����ͬʱ���ҵ�β�ͣ��Զ���
	if(to_bean_tail == 0)
	{
		//to_bean=A_star(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_bean_x(), get_bean_y());
		//FX=get_dir(get_step_x(),get_step_y(),get_snack_head_x(),get_snack_head_y());
		//FX=get_dir(go_bean_x,go_bean_y,get_snack_head_x(),get_snack_head_y());
		if(to_bean_tail_max == 0 && score >= (ROW_NUM*LINE_NUM)/2 )
		{
			A_star_init();
			A_star_max(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_bean_x(), get_bean_y());
			FX=get_dir(go_bean_tail_max_x,go_bean_tail_max_y,get_snack_head_x(),get_snack_head_y());
		}
		else
		{
			FX=get_dir(go_bean_tail_x,go_bean_tail_y,get_snack_head_x(),get_snack_head_y());
		}

	}
	//����ܵ�β�ͣ���β��
	else if(to_tail == 0  && to_bean == 1)
	{
		//����������ҧβ��
		int move[4][2]={1,0,-1,0,0,1,0,-1};
		int temp_x,temp_y;
		if( abs(get_snack_head_x() - get_snack_tail_x()) + abs(get_snack_head_y() - get_snack_tail_y()) == 1)
		{
			FX=get_dir(go_tail_x,go_tail_y,get_snack_head_x(),get_snack_head_y());
			for(i=0;i<4;++i)
			{
				temp_x=get_snack_head_x()+move[i][0];
				temp_y=get_snack_head_y()+move[i][1];
				if(Snack_map[temp_x][temp_y] != 0 || (get_snack_tail_x() == temp_x && get_snack_tail_y() == temp_y))
					continue;

				A_star_init();
				Snack_map[get_bean_x()][get_bean_y()]=0;
				to_whatever=A_star_max(Snack_map,temp_x ,temp_y,get_snack_tail_x() ,get_snack_tail_y());
				Snack_map[get_bean_x()][get_bean_y()]=1;
				if(to_whatever == 0)
				{
					FX=get_dir(temp_x,temp_y,get_snack_head_x(),get_snack_head_y());
					go_tail_x = temp_x;
					go_tail_y = temp_y;
					break;
				}
				else
				{
					FX=get_dir(go_tail_x,go_tail_y,get_snack_head_x(),get_snack_head_y());
				}

			}
		}
		else
			FX=get_dir(go_tail_x,go_tail_y,get_snack_head_x(),get_snack_head_y());
	}
	//����ܳԶ��ӵ��޷���ȫ���أ���β��
	else if(to_tail == 0 && to_bean == 0)
	{

		//����������ҧβ��
		int move[4][2]={1,0,-1,0,0,1,0,-1};
		int temp_x,temp_y;
		if( abs(get_snack_head_x() - get_snack_tail_x()) + abs(get_snack_head_y() - get_snack_tail_y()) == 1)
		{
			FX=get_dir(go_tail_x,go_tail_y,get_snack_head_x(),get_snack_head_y());
			for(i=0;i<4;++i)
			{
				temp_x=get_snack_head_x()+move[i][0];
				temp_y=get_snack_head_y()+move[i][1];
				if(Snack_map[temp_x][temp_y] != 0 || (get_snack_tail_x() == temp_x && get_snack_tail_y() == temp_y))
					continue;

				A_star_init();
				Snack_map[get_bean_x()][get_bean_y()]=0;
				to_whatever=A_star_max(Snack_map,temp_x ,temp_y,get_snack_tail_x() ,get_snack_tail_y());
				Snack_map[get_bean_x()][get_bean_y()]=1;
				if(to_whatever == 0)
				{
					FX=get_dir(temp_x,temp_y,get_snack_head_x(),get_snack_head_y());
					go_tail_x = temp_x;
					go_tail_y = temp_y;
					break;
				}
				else
				{
					FX=get_dir(go_tail_x,go_tail_y,get_snack_head_x(),get_snack_head_y());
				}

			}
		}
		else
			FX=get_dir(go_tail_x,go_tail_y,get_snack_head_x(),get_snack_head_y());

		//�����γɰѶ��Ӷ���һ�����ӵ����
		if( abs(get_bean_x()-go_tail_x) + abs(get_bean_y() - go_tail_y) == 1)
		{
			int bean_alone=1;			
			FX=get_dir(go_tail_x,go_tail_y,get_snack_head_x(),get_snack_head_y());
			for(i=0;i<4;++i)
			{
				temp_x=get_bean_x()+move[i][0];
				temp_y=get_bean_y()+move[i][1];
				if(Snack_map[temp_x][temp_y] == 0 && temp_x != go_tail_x && temp_y != go_tail_y)
				{
					bean_alone=0;
				}
			}
			if(bean_alone == 1)
			{
				Snack_map[go_tail_x][go_tail_y]=1;
				A_star_init();
				//to_whatever=A_star_max(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_bean_x() ,get_bean_y());
				to_whatever=A_star_max(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_snack_tail_x() ,get_snack_tail_y());
				Snack_map[go_tail_x][go_tail_y]=0;
				if(to_whatever == 0)
					FX=get_dir(get_step_x(),get_step_y(),get_snack_head_x(),get_snack_head_y());
				else
				{
					Snack_map[go_tail_x][go_tail_y]=1;
					A_star_init();
					//to_whatever=A_star_max(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_bean_x() ,get_bean_y());
					to_whatever=A_star(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_snack_tail_x() ,get_snack_tail_y());
					Snack_map[go_tail_x][go_tail_y]=0;
					if(to_whatever == 0)
						FX=get_dir(get_step_x(),get_step_y(),get_snack_head_x(),get_snack_head_y());
				}

			}
			else 
			{
				FX=get_dir(go_tail_x,go_tail_y,get_snack_head_x(),get_snack_head_y());
			}
		}

	}
	//���������β�ͣ���Զ����Զ���
	else if(to_tail == 1 && to_bean == 0)
	{
		A_star_init();
		to_whatever=A_star_max(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_bean_x() ,get_bean_y());
		//if(to_whatever == 0)
			FX=get_dir(get_step_x(),get_step_y(),get_snack_head_x(),get_snack_head_y());
		/*else
		{
			A_star_init();
			to_whatever=A_star(Snack_map,get_snack_head_x() ,get_snack_head_y(),get_bean_x() ,get_bean_y());
			if(to_whatever == 0)
				FX=get_dir(get_step_x(),get_step_y(),get_snack_head_x(),get_snack_head_y());
			else
			{
				FX=get_rand_FX(Snack_map,FX);
			}

		}*/
		//FX=get_dir(go_bean_x,go_bean_y,get_snack_head_x(),get_snack_head_y());
		//Sleep(1000);
	}
	//ֻҪ�߲������Ǿ������
	else
	{
		FX=get_rand_FX(Snack_map,FX);
	}

	FX |=((to_bean_tail << 8) | (to_tail << 4) | to_bean ) << 8 ;
	return FX;
}

int is_must_die(int Snack_map[][ROW_NUM],int FX,int head_x,int head_y)
{
	int next_x,next_y;
	int where_move[4][2]={1,0,0,-1,-1,0,0,1};
	int where[4]={5,4,8,6};
	int i,j;

	for(i=0;i<4;++i)
	{
		//�ҵ���Ӧ����
		if(where[i] == FX)
		{
			next_x=head_x + where_move[i][0];
			next_y=head_y + where_move[i][1];
			//���Խ�磬����
			if(next_x < 0 || next_x >= LINE_NUM || next_y <0 || next_y >= ROW_NUM)
			{
				return 1;
			}
			//����ж������ж��Ƿ�����β���߶���
			else if(Snack_map[next_x][next_y] != 0 )
			{
				//����Ƕ��ӻ���β������  (��������ֱ�ӳ���β)
				if( (next_x == get_bean_x() && next_y == get_bean_y()) || (next_x == get_snack_tail_x() && next_y == get_snack_tail_y()) )
				{
					return 0;
				}
				//ײ����������
				else
				{
					return 1;
				}

			}
			//û��������ûԽ�磬����
			else
			{
				return 0;
			}
		}
	}

	return 1;
}