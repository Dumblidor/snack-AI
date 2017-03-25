#include "A_star.h" 


typedef struct opennode
{
	int is_closed;
	int x;
	int y;
	int g;
	int h;
	Open_node *father;

}Open_node;


int A_star_move[][2]={0,1,0,-1,1,0,-1,0};
Open_node* A_star_map[LINE_NUM][ROW_NUM]={0};
Open_node* Open_node_list[LIST_LEN]={0};
//������С�ѣ�����Open list��
Binaryheap_head* max_head=NULL;
Binaryheap_head* min_head=NULL;

int step_x;
int step_y;
int step_x_list[STEP_MAX_NUM];
int step_y_list[STEP_MAX_NUM];

int step_num=0;
//0�գ�1����
int step_null=0;

//int Open_list_num;



//��ʼ�����������ݽṹ����ʵ�֣�
void A_star_init()
{
	int i;
	int j;
	step_x=-1;
	step_y=-1;
	//Open_list_num=0;
	step_num=0;
	step_null=0;

	init_step_list();
	for(i=0;i<LINE_NUM ;++i)
	{
		for(j=0;j<ROW_NUM;++j)
		{
			if(A_star_map[i][j]!=NULL)
			{
				free(A_star_map[i][j]);
			}
			A_star_map[i][j]=NULL;
		}
	}
	//��ʼ��list����ʹ���������ݽṹӦ�ö�Ӧ��ʼ������
	/*for(i=0;i<LIST_LEN;++i)
	{
		Open_node_list[i] = NULL;
	}*/
	if(max_head != NULL)
	//if(0)
	{
		binaryheap_reset(max_head);
		binaryheap_reset(min_head);
	}
	else
	{
		max_head=binaryheap_init(LIST_LEN);
		min_head=binaryheap_init(LIST_LEN);
	}

}

//����Hֵ��A*Ȩֵ֮һ��
int A_star_funH(int now_x ,int now_y ,int to_x, int to_y)
{
	int x=abs(now_x - to_x);
	int y=abs(now_y - to_y);
	return (int)((double)(x+y) * 1.4);
}

//���ڶ���ѵıȽϺ���
int cmp_max(const void* a,const void* b)
{
	return (*((Open_node**)a))->g + (*((Open_node**)a))->h - (*((Open_node**)b))->g - (*((Open_node**)b))->h;
}
int cmp_min(const void* a,const void* b)
{
	return -((*((Open_node**)a))->g + (*((Open_node**)a))->h - (*((Open_node**)b))->g - (*((Open_node**)b))->h);
}

//����open�ڵ����У��������ݽṹʵ�֣�
int A_star_put_openlist(int x,int y, Open_node* node)
{
	/*int i;
	for (i = 0; i < LIST_LEN; i++)
	{
		if(Open_node_list[i] == NULL || Open_node_list[i]->is_closed == 1)
		{
			Open_node_list[i] = node;
			return 0;
		}
	}
	return 1;
	*/
	binaryheap_insrt(max_head,node,cmp_max);
	binaryheap_insrt(min_head,node,cmp_min);
	return 0;
}

//�ĸ�������ά������step list����*1����*2����ʼ��*1
void add_step_list(int x,int y)
{
	if(step_num == STEP_MAX_NUM-1)
		return;
	step_null=1;
	step_x_list[step_num] = x;
	step_y_list[step_num++] = y;
}

int get_step_list_x(int i)
{
	return step_x_list[i];
}

int get_step_list_y(int i)
{
	return step_y_list[i];
}

void init_step_list()
{
	int i;
	for(i=0;i<STEP_MAX_NUM;++i)
	{
		step_x_list[i]=0;
		step_y_list[i]=0;
	}
}

//�½�һ��Open_node�ڵ㲢�ӽ�Open_list
void A_star_add_open_node(int x,int y,int g_num, int h_num, Open_node* fa)
{
	Open_node* temp=(Open_node*)malloc(sizeof(Open_node));
	temp->is_closed=0;
	temp->x=x;
	temp->y=y;
	temp->g=g_num;
	temp->h=h_num;
	temp->father=fa;
	A_star_map[x][y]=temp;
	A_star_put_openlist(x,y,temp);
	//Open_list_num++;
}

//���OPEN��������СȨֵ�ڵ㣨�������ݽṹʵ�֣�,������Ӷ���ɾ��
Open_node* A_star_get_min_node()
{
	/*int i;
	int min_local;
	int min_num=0;
	Open_node* min_node=NULL;
	for(i=0;i<LIST_LEN;++i)
	{
		if(Open_node_list[i]!=NULL)
		{
			if(min_node == NULL)
			{
				min_local=i;
				min_node = Open_node_list[i];
				min_num = min_node->g + min_node->h;
			}
			else
			{
				if(Open_node_list[i]->g + Open_node_list[i]->h < min_num)
				{
					min_local=i;
					min_node = Open_node_list[i];
					min_num = min_node->g + min_node->h;
				}
			}
		}
	}
	if(min_node != NULL)
	{
		A_star_map[min_node->x][min_node->y]->is_closed = 1;
		Open_node_list[min_local]=NULL;
	}
	Open_list_num--;
	return min_node;*/
	Open_node* min=binaryheap_get_top(min_head);
	binaryheap_delete_top(min_head,cmp_min);
	return min;
}

//���OPEN���������Ȩֵ�ڵ㣨�������ݽṹʵ�֣�,������Ӷ���ɾ��
Open_node* A_star_get_max_node()
{
	/*int i;
	int max_local;
	int max_num=0;
	Open_node* max_node=NULL;
	for(i=0;i<LIST_LEN;++i)
	{
		if(Open_node_list[i]!=NULL && Open_node_list[i]->is_closed == 0)
		{
			if(max_node == NULL)
			{
				max_local=i;
				max_node = Open_node_list[i];
				max_num = max_node->g + max_node->h;
			}
			else
			{
				if(Open_node_list[i]->g + Open_node_list[i]->h > max_num)
				{
					max_local=i;
					max_node = Open_node_list[i];
					max_num = max_node->g + max_node->h;
				}
			}
		}
	}
	if(max_node != NULL)
	{
		A_star_map[max_node->x][max_node->y]->is_closed = 1;
		Open_node_list[max_local]=NULL;
	}
	Open_list_num--;
	return max_node;
	*/
	Open_node* max=binaryheap_get_top(max_head);
	binaryheap_delete_top(max_head,cmp_max);
	return max;
}

//Ѱ·�㷨(Ѱ���·)
int A_star(int map[][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y)
{

	//��A_star_map[x][y]!=NULL����˵������open��close������
	//��A_star_map[x][y]->is_closed == 1 ,���������close�У�==0����open��

	int i;
	int j;
	int lost_value;
	int corrent_x,corrent_y;
	Open_node* temp=NULL;
	Open_node* grandfather=NULL;
	int find = 0;
	lost_value=map[to_x][to_y];
	map[to_x][to_y]=0;

	//������openlist
	A_star_add_open_node(now_x,now_y,0,0,NULL);
	//ֱ���ҵ��յ�
	while(1)
	{
		//����ҵ�·�������յ���ǰ������·��
		if(find == 1)
		{
			if(grandfather->father == NULL)
			{
				grandfather->is_closed=2;
				add_step_list(grandfather->x,grandfather->y);
				step_x=grandfather->x;
				step_y=grandfather->y;
				map[to_x][to_y]=lost_value;
				return 0;
			}
			while(grandfather->father->father != NULL)
			{
				add_step_list(grandfather->x,grandfather->y);
				grandfather->is_closed=2;
				//printf("%d,%d\n",grandfather->x,grandfather->y);
				grandfather = grandfather->father;
				grandfather->is_closed=2;
			}
			//printf("\n");
			add_step_list(grandfather->x,grandfather->y);
			step_x=grandfather->x;
			step_y=grandfather->y;
			map[to_x][to_y]=lost_value;
			return 0;
		}

		//�ҵ�list����С��
		temp = A_star_get_min_node();
		if(temp == NULL)
		{
			map[to_x][to_y]=lost_value;
			return 1;
		}
		//����close
		temp->is_closed=1;
		//map[temp->x][temp->y]=2;




		//������ڵ��������Ҳ���
		for(i=0;i<4;++i)
		{
			corrent_x=temp->x + A_star_move[i][0];
			corrent_y=temp->y + A_star_move[i][1];
			//����ڵ�Խ�磬����
			if(corrent_x < 0 || corrent_x >= LINE_NUM || corrent_y <0 || corrent_y >= ROW_NUM)
			{
				continue;
			}
			//����ýڵ���close list����õ�����������
			if((A_star_map[corrent_x][corrent_y] != NULL && A_star_map[corrent_x][corrent_y]->is_closed == 1) || map[corrent_x][corrent_y] !=0 )
			{
				continue;
			}
			//�������close list���Ҳ���open list,����open list
			else if(A_star_map[corrent_x][corrent_y] == NULL)
			{
				if(temp->father == NULL)
					A_star_add_open_node(corrent_x,corrent_y,temp->g+1,A_star_funH(corrent_x,corrent_y,to_x,to_y),temp);
				else
				{
					//������
					if( abs(temp->father->x - corrent_x) == 1)
					{
						A_star_add_open_node(corrent_x,corrent_y,temp->g+1,A_star_funH(corrent_x,corrent_y,to_x,to_y)+1,temp);
					}
					//û����
					else
					{
						A_star_add_open_node(corrent_x,corrent_y,temp->g+1,A_star_funH(corrent_x,corrent_y,to_x,to_y),temp);
					}
				}
			}
			//����Ѿ���open���鿴�Ƿ��ܸ���F+H������ܣ�����G��H���ı丸�ڵ�
			if(A_star_map[corrent_x][corrent_y] != NULL)
			{
				if(temp->g+1 < A_star_map[corrent_x][corrent_y]->g)
				{
					A_star_map[corrent_x][corrent_y]->g = temp->g + 1;
					A_star_map[corrent_x][corrent_y]->father = temp;
				}
			}
			//����ҵ��յ㣬���� ��
			if((corrent_x == to_x && corrent_y == to_y))
			{
				//A_star_map[corrent_x][corrent_y]->is_closed=1;
				//A_star_map[corrent_x][corrent_y]->father = temp;
				grandfather=A_star_map[corrent_x][corrent_y];
				find = 1;
				break;
			}
		}
		
	}
	map[to_x][to_y]=lost_value;
	return 1;
}

//Ѱ·�㷨(Ѱ�·) 
int A_star_max(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y)
{
	//��A_star_map[x][y]!=NULL����˵������open��close������
	//��A_star_map[x][y]->is_closed == 1 ,���������close�У�==0����open��

	int i;
	int j;
	int lost_value;
	int corrent_x,corrent_y;
	Open_node* temp=NULL;
	Open_node* grandfather=NULL;
	int find = 0;
	lost_value=map[to_x][to_y];
	map[to_x][to_y]=0;

	/*
	//����
	map[5][10]=-1;
	for(i=0;i<LINE_NUM;++i)
	{
		for(j=0;j<ROW_NUM;++j)
		{
			printf("%d",map[i][j]);
		}
		printf("\n");
	}
	//���Խ���
	*/
	//��ʼ��

	//A_star_init();
	//������openlist
	A_star_add_open_node(now_x,now_y,0,0,NULL);
	//ֱ���ҵ��յ�
	while(1)
	{
		//����ҵ�·�������յ���ǰ������·��
		if(find == 1)
		{
			if(grandfather->father == NULL)
			{
				grandfather->is_closed=2;
				add_step_list(grandfather->x,grandfather->y);
				step_x=grandfather->x;
				step_y=grandfather->y;
				map[to_x][to_y]=lost_value;
				return 0;
			}
			while(grandfather->father->father != NULL)
			{
				//printf("%d,%d\n",grandfather->x,grandfather->y);
				/*step_x <<= 4;
				step_y <<= 4;
				step_x|=grandfather->x;
				step_y|=grandfather->y;*/
				grandfather->is_closed=2;
				add_step_list(grandfather->x,grandfather->y);
				grandfather = grandfather->father;
				grandfather->is_closed=2;	

			}
			//printf("\n");
			/*step_x <<= 4;
			step_y <<= 4;
			step_x|=grandfather->x;
			step_y|=grandfather->y;*/
			add_step_list(grandfather->x,grandfather->y);
			step_x=grandfather->x;
			step_y=grandfather->y;
			map[to_x][to_y]=lost_value;
			return 0;
		}

		//�ҵ�list������
		temp = A_star_get_max_node();
		if(temp == NULL)
		{
			if(find == 2)
			{
				find = 1;
				grandfather=A_star_map[step_x][step_y];
				continue;
			}
			map[to_x][to_y]=lost_value;
			return 1;
		}
		//����close
		temp->is_closed=1;
		//map[temp->x][temp->y]=2;


		//������ڵ��������Ҳ���
		for(i=0;i<4;++i)
		{
			corrent_x=temp->x + A_star_move[i][0];
			corrent_y=temp->y + A_star_move[i][1];
			//����ڵ�Խ�磬����
			if(corrent_x < 0 || corrent_x >= LINE_NUM || corrent_y <0 || corrent_y >= ROW_NUM)
			{
				continue;
			}
			//����ýڵ���close list����õ�����������
			if((A_star_map[corrent_x][corrent_y] != NULL && A_star_map[corrent_x][corrent_y]->is_closed == 1) || map[corrent_x][corrent_y] != 0)
			{
				continue;
			}
			//�������close list���Ҳ���open list,����open list
			else if(A_star_map[corrent_x][corrent_y] == NULL)
			{
				if(temp->father == NULL)
					A_star_add_open_node(corrent_x,corrent_y,temp->g+1,A_star_funH(corrent_x,corrent_y,to_x,to_y),temp);
				else
				{
					//������
					if( abs(temp->father->x - corrent_x) == 1)
					{
						A_star_add_open_node(corrent_x,corrent_y,temp->g+1,A_star_funH(corrent_x,corrent_y,to_x,to_y)-1,temp);
					}
					//û����
					else
					{
						A_star_add_open_node(corrent_x,corrent_y,temp->g+1,A_star_funH(corrent_x,corrent_y,to_x,to_y),temp);
					}
				}
			}
			//����Ѿ���open���鿴�Ƿ��ܸ���F+H������ܣ�����G��H���ı丸�ڵ�
			if(A_star_map[corrent_x][corrent_y] != NULL)
			{
				if(temp->g+1 > A_star_map[corrent_x][corrent_y]->g)
				{
					A_star_map[corrent_x][corrent_y]->g = temp->g + 1;
					A_star_map[corrent_x][corrent_y]->father = temp;
				}
			}

			//����ҵ��յ㣬���� ��
			if((corrent_x == to_x && corrent_y == to_y) && A_star_map[corrent_x][corrent_y]->g <= 1 && 0)
			{
				find=2;
				step_x = corrent_x;
				step_y = corrent_y;
				A_star_map[corrent_x][corrent_y]->is_closed=1;
			}
			else if((corrent_x == to_x && corrent_y == to_y))// && A_star_map[corrent_x][corrent_y]->g > 0)
			{
				//A_star_map[corrent_x][corrent_y]->is_closed=1;
				//A_star_map[corrent_x][corrent_y]->father = temp;
				grandfather=A_star_map[corrent_x][corrent_y];
				find = 1;
				break;
			}
		}
		
		/*if(Open_list_num == 0)
		{
			if(find == 2)
			{
				find = 0;
				grandfather=A_star_map[step_x][step_y];
				continue;
			}
			map[to_x][to_y]=1;
			return 1;
		}*/
	}
	map[to_x][to_y]=lost_value;
	return 1;
}

//��λ��Ѱ·�ڶ�����ʼ��
void A_star_special_init()
{
	int i;
	int j;

	for(i=0;i<LINE_NUM ;++i)
	{
		for(j=0;j<ROW_NUM;++j)
		{
			if(A_star_map[i][j]!=NULL && A_star_map[i][j]->is_closed != 2)
			{
				free(A_star_map[i][j]);
				A_star_map[i][j]=NULL;
			}
		}
	}
	//��ʼ��list����ʹ���������ݽṹӦ�ö�Ӧ��ʼ������
	/*for(i=0;i<LIST_LEN;++i)
	{
		Open_node_list[i]=NULL;
	}*/
	if(max_head != NULL)
	{
		binaryheap_reset(max_head);
		binaryheap_reset(min_head);
	}
	else
	{
		max_head=binaryheap_init(LIST_LEN);
		min_head=binaryheap_init(LIST_LEN);
	}
}

//��λ��Ѱ·���鿴�Ƿ���A->B->C��·����
int A_star_double(int map[][ROW_NUM],int begin_x,int begin_y,int mid_x,int mid_y,int end_x,int end_y)
{
	int to_mid,to_end;
	int firstep_x,firstep_y;
	A_star_init();

	//map[bean_x][bean_y]=0;
	to_mid=A_star(map,begin_x,begin_y,mid_x,mid_y);
	//map[bean_x][bean_y]=1;
	firstep_x=step_x;
	firstep_y=step_y;

	A_star_special_init();
	to_end=A_star(map,mid_x,mid_y,end_x,end_y);

	step_x=firstep_x;
	step_y=firstep_y;

	return to_mid | to_end;
}

//��λ��Ѱ�·���鿴�Ƿ���A->B->C��·�������У�A->B�����ܳ���
int A_star_double_max(int map[][ROW_NUM],int begin_x,int begin_y,int mid_x,int mid_y,int end_x,int end_y)
{
	int to_mid,to_end;
	int firstep_x,firstep_y;
	A_star_init();

	//map[bean_x][bean_y]=0;
	to_mid=A_star_max(map,begin_x,begin_y,mid_x,mid_y);
	//map[bean_x][bean_y]=1;
	firstep_x=step_x;
	firstep_y=step_y;
	if(to_mid == 1)
		return 1;
	A_star_special_init();
	to_end=A_star(map,mid_x,mid_y,end_x,end_y);

	step_x=firstep_x;
	step_y=firstep_y;

	return to_mid | to_end;
}

//�����������������һ��������
int get_step_x()
{
	int ret = step_x;
	//step_x >>= 4;
	return ret;
}
int get_step_y()
{
	int ret = step_y;
	//step_y >>= 4;
	return ret;
}

//���step_num
int get_step_num()
{
	return step_num;
}



//������

/*
int main()
{
	Binaryheap_head* head = binaryheap_init(300);
	int i,num;
	for(i=0;i<300;++i)
	{
		Open_node * a=(Open_node*)malloc(sizeof(Open_node));
		a->g=i;
		a->h=i;
		binaryheap_insrt(head,a,cmp_max);
	}
		
	for(i=0;i<300;++i)
	{
		num = binaryheap_get_top(head)->g +binaryheap_get_top(head)->h ;
		binaryheap_delete_top(head,cmp_max);
		printf("%d ",num);
	}

}*/