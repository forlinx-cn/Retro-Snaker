#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void freePlayer(Player* _player);

int main() {
	system("title 贪吃蛇小游戏");
	resetColor();
	Player* player = loadStartPage();
	if (!player) return -1;
	loadGamePage(player);
	hideCur();
	//游戏开始
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
		/*****释放蛇****/
		free(players + i);
	}
	/***释放新玩家****/
	if (!flag) {
		free(_player);
	}

}