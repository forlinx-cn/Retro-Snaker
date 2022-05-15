#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void freePlayer(Player* _player);
void game_pause(Player* _player);

int main() {
	system("title ̰����С��Ϸ");
	resetColor();
	Player* player;
	while (!(player = loadStartPage())) system("cls");
	while (!loadGamePage(player)) system("cls");
	hideCur();
	//��Ϸ��ʼ
	gotoXY(map_size * 2 + 1, 0);
	printf("%s: %3d�� ��ʵʱ�÷֣�", player->name, player->score);
	gotoXY(map_size * 2 + 1, 1);
	printf("%s: %3d��", player->name, player->hScore);
	char dr;
	creat_food(1, player);
	do {
		Sleep(1000 / player->length * 2 + 100);
		player->hGameTime += (1000 / player->length * 2 + 100);
		if (_kbhit()) {
			dr = getch();
			if (dr == ' ') { 
				game_pause(player);				//��ͣ��Ϸ
				
			}
			direction_change(dr, player);
		}
	} while (!isDeath(player->snake[0]) && snake_move(player));
	player->hGameTime = 0;
	system("title ̰����С��Ϸ(�ѽ���) ���ڱ����¼����");

	saveRecord(!haveUser(player->name), player->score > player->hScore, player);			//����һ����¼�¼
	system("title ̰����С��Ϸ(�ѽ���)");
	freePlayer(player);
	gotoXY(0, map_size + 2);
	showCur();
	system("pause");
	return 0;
}

void freePlayer(Player* _player) {
	int flag = 0;
	/*****�ͷ���****/
	free(players);
	for (int i = 0; i < player_num; ++i) {
		if (players + i == _player) flag = 1;
	}
	/***�ͷ������****/
	if (!flag) {
		free(_player);
	}

}

void game_pause(Player* _player) {
	saveRecord(!haveUser(_player->name), _player->score > _player->hScore, _player);	//�����¼
	gotoXY(0, map_size + 2);
	system("title ̰����С��Ϸ(����ͣ)");
	system("pause");
	gotoXY(0, map_size + 2);
	printf("                             ");
	system("title ̰����С��Ϸ");
}