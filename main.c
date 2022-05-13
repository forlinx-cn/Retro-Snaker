#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void freePlayer(Player* _player);

int main() {
	system("title ̰����С��Ϸ");
	resetColor();
	Player* player = loadStartPage();
	if (!player) return -1;
	loadGamePage(player);
	hideCur();
	//��Ϸ��ʼ
	char dr;
	do {
		Sleep(1000 - player->length * 100 % 701);
		if (_kbhit()) {
			dr = getch();
			direction_change(dr, player);
		}
	} while (snake_move(player));


	saveRecord();
	freePlayer(player);


	gotoXY(0, map_size + 2);
	showCur();
	system("pause");
	return 0;
}

void freePlayer(Player* _player) {
	int flag = 0;
	for (int i = 0; i < player_num; ++i) {
		if (players + i == _player) flag = 1;
		/*****�ͷ���****/
		free(players + i);
	}
	/***�ͷ������****/
	if (!flag) {
		free(_player);
	}

}