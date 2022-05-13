#include "prepare.h"




const RecordPATH = "data\\";
player_num = 0;



void gotoXY(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}

void hideCur() {
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize = 1;
	cursor_info.bVisible = FALSE;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor_info);
}

void showCur() {
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize = 1;
	cursor_info.bVisible = TRUE;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor_info);
}

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
	setColor(default_color);
}

void setWindowSize(int x, int y) {
	char cmd[32] = { '\0' };
	sprintf(cmd, "mode con cols=%d lines=%d", x, y);
	system(cmd);
}

void readRecord() {
	FILE* record = fopen("Record.txt", "r");

	if (!record) return;

	if (fscanf(record, "%d", &player_num)) {
		players = (Player*)malloc(sizeof(Player) * player_num);
		if (!players) exit(-1);
		for (int i = 0; i < player_num && !feof(record); ++i) {
			fscanf(record, "%s%d", players[i].name, &(players[i].length));
			//读取蛇
			for (int j = 0; j < players[i].length; ++j) {
				fscanf(record, "(%d,%d)", &players[i].snake[j].x, &players[i].snake[j].y);
			}
			//读取食物
			int foodnum = 0;
			fscanf(record, "%d%d%d%d", &(players[i].score), &(players[i].hGameTime),
				&(players[i].tGameTime), &foodnum);
			for (int j = 0; j < foodnum; ++j) {
				int x, y;
				fscanf(record, "(%d,%d)", &x, &y);
				players[i].map[x][y] = FOOD;
			}
		}
	}

	fclose(record);
}

void saveRecord() {
	if (player_num == 0) return;

}