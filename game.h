#include "startPage.h"
#include <math.h>

#ifndef __GAME_H__
#define __GAME_H__

Player* player;

int loadGamePage(Player* _player);		//������Ϸ����
void initMap(Player* _player);			//��ʼ����ͼ
void printSnake(Player* _player);		//��ӡ��
int snake_move(Player* _player);						//���ƶ�
void direction_change(char new_direction, Player* _player);	//��ת��
void creat_food(int weight, Player* _player);			//����ʳ��
void snake_growth(int weight, Player* _player, SnakeNode tail);			//������
int isDeath(SnakeNode head);

#endif