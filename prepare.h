#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>

#ifndef __CONTROL_H__
#define __CONTROL_H__

void gotoXY(int x, int y);				//����ƶ�
void hideCur();							//���ع��
void setColor(int color);				//���ô�ӡ�������ɫ
void resetColor();
void setWindowSize(int x, int y);		//���ô��ڴ�С
void readRecord();						//��ȡ��¼
void saveRecord();						//�����¼




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