#include "startPage.h"

const int line = 4;
char menu[][100] = {
	"欢迎游玩贪吃蛇小游戏",
	"查看帮助",
	"退出游戏",
	"选择你的身份"
};

Player* loadStartPage() {
	setWindowSize(map_size * 2, map_size);
	hideCur();
	printMenu();				//打印菜单信息
	showCur();
	int n = line + player_num;
	gotoXY(map_size, (map_size - line - player_num) / 2 + n);
	char ch;
	char username[20] = "";
	do {
		getch();
		ch = getch();
		switch (ch) {
		case 72:
			n = (n - 1 + line + player_num + 1) % (line + player_num + 1);
			break;
		case 80:
			n = (n + 1) % (line + player_num + 1);
			break;
		default:
			if (ch == '\r' || n != line + player_num) break;
			//command operation
			char cmd[20] = { '\0' };
			scanf("%s", cmd);
			if (strcmp(cmd, "add") == 0) {		//add指令
				scanf("%s", username);
				getchar();
			}
			else if (strcmp(cmd, "delete") == 0) {			//detele指令
				scanf("%s", username);
			}
			else {			//直接输入username
				strcat(username, cmd);
				getchar();
			}
			ch = '\r';
			break;
		}
		gotoXY(map_size, (map_size - line - player_num) / 2 + n);
	} while (ch != '\r');

	if (n == line + player_num) {
		if (username[0] == '\0') {			//以默认身份登入
			strcat(username, "default");
		}
		if (haveUser(username)) {			//以username身份登入
			for (int i = 0; i < player_num; ++i) {
				if (strcmp(username, players[i].name) == 0)
					return players + i;
			}
		}
		else {								//创建username并登入
			printf("\n你第一次以%s的身份登入游戏，是否创建该身份？(Y/N) > ", username);
			Player* newPlayer;
			switch (getchar()) {
			case 'Y':
			case 'y':
				newPlayer = (Player*)malloc(sizeof(Player));
				if (!newPlayer) exit(-1);
				newPlayer->name[0] = '\0';
				strcat(newPlayer->name, username);
				newPlayer->hGameTime = 0;		//初始化游玩时间
				newPlayer->score = 0;			//初始化得分
				newPlayer->hScore = 0;		    //初始化最长纪录
				newPlayer->length = 0;
				newPlayer->food_num = 0;
				//初始化地图
				for (int x = 1; x < map_size - 1; ++x) {
					for (int y = 1; y < map_size - 1; ++y) {
						newPlayer->map[x][y] = EMPTY;
					}
				}
				return newPlayer;
			case 'N':
			case 'n':
			default:
				return NULL;
			}
			
		}
	}
	else if (n == line - 2) {		//退出游戏
		exit(0);
	}
	else if (n == line - 3) {		//查看帮助
		showHelpInfo();
		system("pause");
		return NULL;
	}
	else if (n >= line && n < line + player_num) {		//按选中身份登入
		return &players[n - line];
	}
	return NULL;
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
	putchar('\n');
}

int haveUser(const char* username) {
	for (int i = 0; i < player_num; ++i) {
		if (strcmp(username, players[i].name) == 0) {
			return i + 1;
		}
	}
	return 0;
}

void showHelpInfo() {
	system("cls");
	system("pause");
}
