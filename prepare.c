#include "prepare.h"


const RecordPATH = "";
int player_num = 0;



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
	char ch = '\0';
	if (fscanf(record, "%d", &player_num) && !feof(record)) {
		players = (Player*)malloc(sizeof(Player) * player_num);
		if (!players) exit(-1);
		
		for (int i = 0; i < player_num && !feof(record); ++i) {
			initPlayer(players + i, "");
			fscanf(record, "%s%d", players[i].name, &(players[i].length));
			//读取蛇
			for (int j = 0; j < players[i].length; ++j) {
				fscanf(record, " (%d,%d)", &players[i].snake[j].x, &players[i].snake[j].y);
				players[i].map[players[i].snake[j].x][players[i].snake[j].y] = BODY;
				if (fgetc(record) == '\n') break;
			}
			players[i].map[players[i].snake[0].x][players[i].snake[0].y] = 
				players[i].map[players[i].snake[0].x][players[i].snake[0].y] == WALL ? WALL : HEAD;
			//读取前进方向
			players[i].direction = fgetc(record);
			if (players[i].direction != 'a' && players[i].direction != 'w' &&
				players[i].direction != 's' && players[i].direction != 'd') {
				printf("第%3d位玩家：方向记录数据有误。程序即将退出！\a\n", i);
				system("pause");
				exit(-1);
			}
			//读取食物
			fscanf(record, "%d%d%d%d", &(players[i].score), &(players[i].hScore),
				&(players[i].hGameTime), &players[i].food_num);
			for (int j = 0; j < players[i].food_num; ++j) {
				int x, y;
				fscanf(record, " (%d,%d)", &x, &y);
				if (x <= 0 || x >= map_size || y <= 0 || y >= map_size) {
					printf("第%3d位玩家：食物记录数据有误。程序即将退出！\a\n", i);
					system("pause");
					exit(-1);
				}
				players[i].map[x][y] = FOOD;
				if (fgetc(record) == '\n') break;
			}
		}
	}

	fclose(record);
}

void saveRecord(Player* _player) {
	FILE* record = fopen("Record.txt", "w");
	if (!record) return;

	fprintf(record, "%d\n", player_num + !haveUser(_player));
	for (int i = 0; i < player_num; ++i) {
		fprintf(record, "%s %d", players[i].name, players[i].length);
		for (int j = 0; j < players[i].length; ++j) {
			fprintf(record, " (%d,%d)", players[i].snake[j].x, players[i].snake[j].y);
		}
		fprintf(record, "\n");
		fprintf(record, "%c ", players[i].direction);

		if (players[i].score > players[i].hScore) players[i].hScore = players[i].score;

		
		fprintf(record, "%d %d %d ", players[i].score, players[i].hScore, players[i].hGameTime);
		fprintf(record, "%d", players[i].food_num);
		int temp = players[i].food_num;
		for (int y = 1; y < map_size - 1; ++y) {
			for (int x = 1; x < map_size - 1; ++x) {
				if (players[i].map[x][y] == FOOD) {
					fprintf(record, " (%d,%d)", x, y);
					temp--;
					if (!temp) { x = map_size; y = map_size; }
				}
			}
		}
		if (temp) {
			printf("食物数据有误");
		}
		fprintf(record, "\n");
	}
	//新玩家的保存
	if (!haveUser(_player)) {
		fprintf(record, "%s %d", _player->name, _player->length);
		for (int j = 0; j < _player->length; ++j) {
			fprintf(record, " (%d,%d)", _player->snake[j].x, _player->snake[j].y);
		}
		fprintf(record, "\n");
		fprintf(record, "%c ", _player->direction);
		if (_player->score > _player->hScore) _player->hScore = _player->score;
		fprintf(record, "%d %d %d ", _player->score, _player->hScore, _player->hGameTime);
		fprintf(record, "%d", _player->food_num);
		int temp = _player->food_num;
		for (int y = 1; y < map_size - 1; ++y) {
			for (int x = 1; x < map_size - 1; ++x) {
				if (_player->map[x][y] == FOOD) {
					fprintf(record, " (%d,%d)", x, y);
					temp--;
					if (!temp) { x = map_size; y = map_size; }
				}
			}
		}
		fprintf(record, "\n");
	}
	fclose(record);
}

void initPlayer(Player* _player, const char* username) {
	if (!_player) exit(-1);
	if (_player->name != username) {			//新玩家
		_player->name[0] = '\0';
		strcat(_player->name, username);
		_player->hScore = 0;		//初始化最长纪录
	}
	else {					//重开
		_player->length = 0;
		_player->direction = 'd';
		_player->score = 0;			//初始化得分
		_player->hGameTime = 0;		//初始化游玩时间
		_player->food_num = 0;
	}
	
	//初始化地图
	for (int x = 0; x < map_size; ++x) {
		for (int y = 0; y < map_size; ++y) {
			_player->map[x][y] = EMPTY;
			if (x == 0 || x == map_size - 1 || y == 0 || y == map_size -1) _player->map[x][y] = WALL;
		}
	}
}

int haveUser(const char* username) {
	for (int i = 0; i < player_num; ++i) {
		if (strcmp(username, players[i].name) == 0) {
			return i + 1;
		}
	}
	return 0;
}