#ifndef DFS_H
#define DFS_H
#include "snack_game.h"
#include <stdio.h>

#define MAX_LIST_LEN 20

int dfs_max(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y, int deep);
int dfs_min(int map[LINE_NUM][ROW_NUM],int now_x ,int now_y ,int to_x, int to_y, int deep);

#endif