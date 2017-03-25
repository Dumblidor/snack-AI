#include "dfs.h"

int dfs_move[4][2]={1,0,-1,0,0,1,0,-1};
int max_deep;
int max_x_list[MAX_LIST_LEN]={0} ;
int max_y_list[MAX_LIST_LEN]={0} ;

int dfs_max(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y, int deep)
{

	int i;
	int ok=1;
	int retok=1;

	printf("dfs: %d %d deep:%d\n",now_x,now_y,deep);
	if(deep == 0)
	{
		max_deep=0;
		for(i=0;i<MAX_LIST_LEN;++i)
		{
			max_x_list[i]=0;
			max_y_list[i]=0;
		}
	}

	//达到目标，记录当前深度并返回
	if(now_x == to_x && now_y == to_y && deep > max_deep)
	{
		max_deep=deep;
		return 0;
	}
	else if(now_x == to_x && now_y == to_y && deep <= max_deep)
	{
		return 1;
	}
	else if( deep >= MAX_LIST_LEN || deep <= -map[now_x][now_y])
	{
		printf("out\n");
		return 1;
	}


	for(i=0;i<4;++i)
	{
		
		int corrent_x = now_x + dfs_move[i][0];
		int corrent_y = now_y + dfs_move[i][1];

		ok=1;
		if((corrent_x >= 0 && corrent_x < LINE_NUM && corrent_y >= 0 && corrent_y < ROW_NUM && map[corrent_x][corrent_y] <= 0) || (corrent_x == to_x && corrent_y == to_y))
		{
			map[corrent_x][corrent_y]=-deep;
			ok = dfs_max(map,corrent_x,corrent_y,to_x,to_y,deep+1);
			//map[corrent_x][corrent_y]=0;
		}


		if(ok == 0)
		{
			retok=0;
			max_x_list[deep] = now_x;
			max_y_list[deep] = now_y;
		}
	}
	return retok;
}
int dfs_min(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y, int deep)
{


}



/*
//测试用
int main1()
{
	int i;
	InitALL();
	Snack_map[get_bean_x()][get_bean_y()]=0;
	i=dfs_max(Snack_map,get_snack_head_x(),get_snack_head_y(),get_bean_x(),get_bean_y(),0);
	Snack_map[get_bean_x()][get_bean_y()]=1;
	printf("ok,i=%d\n",i);
	for(i=1;i<max_deep;++i)
	{
		printf("%d,%d\n",max_x_list[i],max_y_list[i]);
	}
	printf("maxdeep:%d",max_deep);
}
*/