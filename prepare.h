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




typedef struct {
    int x, y;
} Node;
typedef struct {
    Node pos;
    int weight;
} Food;
typedef struct SnakeNode {
    Node pos;
    struct SnakeNode* next;
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
int player_num;
#define map_size 40


#endif