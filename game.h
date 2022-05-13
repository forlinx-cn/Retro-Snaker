#include "startPage.h"
#include <math.h>

#ifndef __GAME_H__
#define __GAME_H__

Player* player;

void loadGamePage(Player* _player);		//加载游戏界面
void initMap(Player* _player);			//初始化地图
void printSnake(Player* _player);		//打印蛇
int snake_move(Player* _player);						//蛇移动
void direction_change(char new_direction, Player* _player);	//蛇转向
void creat_food(int weight);			//生成食物

#endif