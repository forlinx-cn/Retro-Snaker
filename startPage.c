#include "startPage.h"

const int line = 4;
char menu[][100] = {
	"��ӭ����̰����С��Ϸ",
	"�鿴����",
	"�˳���Ϸ",
	"ѡ��������"
};

Player* loadStartPage() {
	setWindowSize(map_size * 2, map_size);
	hideCur();
	printMenu();				//��ӡ�˵���Ϣ
	showCur();
	int n = line + player_num;
	gotoXY(map_size, (map_size - line - player_num) / 2 + n);
	char ch;
	char username[20] = { '\0' };
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
			if (strcmp(cmd, "add") == 0) {		//addָ��
				scanf("%s", username);
				getchar();
			}
			else if (strcmp(cmd, "delete") == 0) {			//deteleָ��
				scanf("%s", username);
			}
			else {			//ֱ������username
				strcat(username, cmd);
				getchar();
			}
			ch = '\r';
			break;
		}
		gotoXY(map_size, (map_size - line - player_num) / 2 + n);
	} while (ch != '\r');

	if (n == line + player_num) {
		if (username[0] == '\0') {			//��Ĭ����ݵ���
			strcat(username, "default");
		}
		if (haveUser(username)) {			//��username��ݵ���
			for (int i = 0; i < player_num; ++i) {
				if (strcmp(username, players[i].name) == 0)
					return players + i;
			}
		}
		else {								//����username������
			printf("\n���һ����%s����ݵ�����Ϸ���Ƿ񴴽�����ݣ�(Y/N) > ", username);
			Player* newPlayer;
			switch (getchar()) {
			case 'Y':
			case 'y':
				newPlayer = (Player*)malloc(sizeof(Player));
				initPlayer(newPlayer, username);
				return newPlayer;
			case 'N':
			case 'n':
			default:
				return NULL;
			}
			
		}
	}
	else if (n == line - 2) {		//�˳���Ϸ
		exit(0);
	}
	else if (n == line - 3) {		//�鿴����
		showHelpInfo();
		system("pause");
		return NULL;
	}
	else if (n >= line && n < line + player_num) {		//��ѡ����ݵ���
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



void showHelpInfo() {
	system("cls");
	system("pause");
}
