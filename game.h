#include "startPage.h"
#include <math.h>

#ifndef __GAME_H__
#define __GAME_H__

Player* player;

int loadGamePage(Player* _player);		//加载游戏界面
void initMap(Player* _player);			//初始化地图
void printSnake(Player* _player);		//打印蛇
int snake_move(Player* _player);						//蛇移动
void direction_change(char new_direction, Player* _player);	//蛇转向
void creat_food(int weight, Player* _player);			//生成食物
void snake_growth(int weight, Player* _player, SnakeNode tail);			//蛇生长
int isDeath(SnakeNode head);

#endif