#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

#ifndef __CONTROL_H__
#define __CONTROL_H__

void gotoXY(int x, int y);				//光标移动
void hideCur();							//隐藏光标
void showCur();                         //显示光标
void setColor(int color);				//设置打印字体的颜色
void resetColor();
void setWindowSize(int x, int y);		//设置窗口大小
void readRecord();						//读取记录
void saveRecord();						//保存记录

#define map_size 40
#define default_color white
enum COLOR {
	black = 0, blue = 1, green = 2, red = 4,
	purple = 5, yellow = 6, white = 7, grey = 8
};
enum TYPE { EMPTY, WALL, HEAD, BODY, FOOD };


typedef struct {
	int x, y;
	int weight;
} Food;
typedef struct SnakeNode {
	int x, y;
	struct SnakeNode* next;
} SnakeNode;
typedef struct {
	char name[100];
	SnakeNode* snake;
	int length;
	int score;
	int hGameTime, tGameTime;
	int map[map_size][map_size];
} Player;

Player* players;
int player_num;

#endif