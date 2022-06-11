#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

#ifndef __CONTROL_H__
#define __CONTROL_H__


#define map_size 40
#define default_color white
#define max_lengt 40
enum COLOR {
	black = 0, blue = 1, green = 2, red = 4,
	purple = 5, yellow = 6, white = 7, grey = 8
};
enum TYPE { EMPTY, WALL, HEAD, BODY, FOOD, BARRIER };


typedef struct {
	int x, y;
	int weight;
} Food;
typedef struct SnakeNode {
	int x, y;
} SnakeNode;
typedef struct {
	char name[100];
	int length;
	SnakeNode snake[100];
	char direction;
	int score, hScore;
	int hGameTime;
	int food_num;
	int map[map_size][map_size];
} Player;

Player* players;
int player_num;

void gotoXY(int x, int y);				//光标移动
void hideCur();							//隐藏光标
void showCur();                         //显示光标
void setColor(int color);				//设置打印字体的颜色
void resetColor();
void setWindowSize(int x, int y);		//设置窗口大小
void readRecord();						//读取记录
void saveRecord(Player* _player);						//保存记录
void initPlayer(Player* _player, const char* username);
int haveUser(const char* username);		//判断是否存在该用户

#endif