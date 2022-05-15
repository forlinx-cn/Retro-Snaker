#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void freePlayer(Player* _player);
void game_pause(Player* _player);

int main() {
	system("title 贪吃蛇小游戏");
	resetColor();
	Player* player;
	while (!(player = loadStartPage())) system("cls");
	while (!loadGamePage(player)) system("cls");
	hideCur();
	//游戏开始
	gotoXY(map_size * 2 + 1, 0);
	printf("%s: %3d分 （实时得分）", player->name, player->score);
	gotoXY(map_size * 2 + 1, 1);
	printf("%s: %3d分", player->name, player->hScore);
	char dr;
	creat_food(1, player);
	do {
		Sleep(1000 / player->length * 2 + 100);
		player->hGameTime += (1000 / player->length * 2 + 100);
		if (_kbhit()) {
			dr = getch();
			if (dr == ' ') { 
				game_pause(player);				//暂停游戏
				
			}
			direction_change(dr, player);
		}
	} while (!isDeath(player->snake[0]) && snake_move(player));
	player->hGameTime = 0;
	system("title 贪吃蛇小游戏(已结束) 正在保存记录……");

	saveRecord(!haveUser(player->name), player->score > player->hScore, player);			//新玩家或者新纪录
	system("title 贪吃蛇小游戏(已结束)");
	freePlayer(player);
	gotoXY(0, map_size + 2);
	showCur();
	system("pause");
	return 0;
}

void freePlayer(Player* _player) {
	int flag = 0;
	/*****释放蛇****/
	free(players);
	for (int i = 0; i < player_num; ++i) {
		if (players + i == _player) flag = 1;
	}
	/***释放新玩家****/
	if (!flag) {
		free(_player);
	}

}

void game_pause(Player* _player) {
	saveRecord(!haveUser(_player->name), _player->score > _player->hScore, _player);	//保存记录
	gotoXY(0, map_size + 2);
	system("title 贪吃蛇小游戏(已暂停)");
	system("pause");
	gotoXY(0, map_size + 2);
	printf("                             ");
	system("title 贪吃蛇小游戏");
}