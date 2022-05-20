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
	if (player->hGameTime == 0 && player->length > 3) {
		gotoXY(0, map_size + 1);
		printf("�����������Ƿ����¿�ʼ��Ϸ��(Y/N) > ");
		showCur();
		char ch = getchar();
		switch (ch)
		{
		case 'Y':
		case 'y':
			initPlayer(player, player->name);
			while (!loadGamePage(player)) system("cls");
			break;
		default:
			exit(0);
			break;
		}
	}
	hideCur();
	//��Ϸ��ʼ
	gotoXY(map_size * 2 + 1, 0);
	printf("%s: %3d�� ��ʵʱ�÷֣�", player->name, player->score);
	gotoXY(map_size * 2 + 1, 1);
	printf("%s: %3d�� ����ʷ��ߵ÷֣�", player->name, player->hScore);
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
	} while (snake_move(player));
	player->hGameTime = 0;
	system("title ̰����С��Ϸ(�ѽ���) ���ڱ����¼����");

	saveRecord(player);			//����һ����¼�¼
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
	saveRecord(_player);	//�����¼
	gotoXY(0, map_size + 2);
	system("title ̰����С��Ϸ(����ͣ)");
	system("pause");
	gotoXY(0, map_size + 2);
	printf("                             ");
	system("title ̰����С��Ϸ");
}