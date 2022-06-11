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

void gotoXY(int x, int y);				//����ƶ�
void hideCur();							//���ع��
void showCur();                         //��ʾ���
void setColor(int color);				//���ô�ӡ�������ɫ
void resetColor();
void setWindowSize(int x, int y);		//���ô��ڴ�С
void readRecord();						//��ȡ��¼
void saveRecord(Player* _player);						//�����¼
void initPlayer(Player* _player, const char* username);
int haveUser(const char* username);		//�ж��Ƿ���ڸ��û�

#endif