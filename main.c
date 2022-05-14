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
	player->score = 0;
	gotoXY(map_size * 2 + 1, 0);
	printf("%s: %3d��", player->name, player->score);
	char dr;
	creat_food(1, player);
	do {
		Sleep(1000 / player->length * 2);
		if (_kbhit()) {
			dr = getch();
			if (dr == ' ') { 
				gotoXY(0, map_size + 2);
				system("title ̰����С��Ϸ(����ͣ)");
				system("pause");
				gotoXY(0, map_size + 2);
				printf("                             ");
				system("title ̰����С��Ϸ");
			}
			direction_change(dr, player);
		}
	} while (snake_move(player));
	system("title ̰����С��Ϸ(�ѽ���)");

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