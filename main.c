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
	player->score = 0;
	gotoXY(map_size * 2 + 1, 0);
	printf("%s: %3d分", player->name, player->score);
	char dr;
	creat_food(1, player);
	do {
		Sleep(1000 / player->length * 2);
		if (_kbhit()) {
			dr = getch();
			if (dr == ' ') { 
				gotoXY(0, map_size + 2);
				system("title 贪吃蛇小游戏(已暂停)");
				system("pause");
				gotoXY(0, map_size + 2);
				printf("                             ");
				system("title 贪吃蛇小游戏");
			}
			direction_change(dr, player);
		}
	} while (snake_move(player));
	system("title 贪吃蛇小游戏(已结束)");

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