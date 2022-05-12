#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>

#ifndef __CONTROL_H__
#define __CONTROL_H__

void gotoXY(int x, int y);				//光标移动
void hideCur();							//隐藏光标
void setColor(int color);				//设置打印字体的颜色
void resetColor();
void setWindowSize(int x, int y);		//设置窗口大小
void readRecord();						//读取记录
void saveRecord();						//保存记录


#define default_color white
enum COLOR {
	black = 0, blue = 1, green = 2, red = 4,
	purple = 5, yellow = 6, white = 7, grey = 8
};
enum TYPE { WALL, HEAD, BODY, FOOD };

const RecordPATH = ".\\data\\";

typedef struct {
    int x, y;
} Node;
typedef struct {
    Node pos;
    int weight;
} Food;
typedef struct {
    Node pos;
    SnakeNode* next;
} SnakeNode;
typedef struct {
    int length;
    SnakeNode* head;
} Snake;
typedef struct {
    char* name;
    Snake* snake;
    int score;
    int hGameTime, tGameTime;
    int** map;
} Player;

Player* players;
int player_num = 0;
const int map_size = 60;
#endif