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
	saveRecord();
	freePlayer(player);

	return 0;
}

void freePlayer(Player* _player) {
	int flag = 0;
	for (int i = 0; i < player_num; ++i) {
		if (players + i == _player) flag = 1;
		/*****释放蛇****/
		SnakeNode* node = players[i].snake;
		SnakeNode* temp = node;
		for (int i = 0; i < players[i].length && node; ++i) {
			temp = temp->next;
			free(node);
			node = temp;
		}
		free(&(players[i].snake));
	}
	/*****释放玩家****/
	free(players);
	/***释放新玩家****/
	if (!flag) {
		SnakeNode* node = _player->snake;
		SnakeNode* temp = node;
		for (int i = 0; i < _player->length && node; ++i) {
			temp = temp->next;
			free(node);
			node = temp;
		}
		free(_player);
	}

}