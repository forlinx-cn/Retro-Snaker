#include "startPage.h"

const int line = 4;
char menu[][100] = {
	"��ӭ����̰����С��Ϸ",
	"�鿴����",
	"�˳���Ϸ",
	"ѡ�������ݣ�"
};

void loadStartPage() {
	setWindowSize(map_size * 2, map_size);
	hideCur();
	printMenu();
}

void printMenu() {
	readRecord();
	int lh = line + player_num;
	int i = 0;
	for (; i < line; ++i) {
		gotoXY((map_size * 2 - strlen(menu[i])) >> 1, (map_size - lh) / 2 + i);
		printf("%s", menu[i]);
	}
	for (; i < lh; ++i) {
		gotoXY((map_size * 2 - strlen(players[i - line].name)) >> 1, (map_size - lh) / 2 + i);
		printf("%s", players[i - line].name);
	}
}