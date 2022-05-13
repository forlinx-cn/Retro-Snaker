#include "game.h"

void loadGamePage(Player* _player) {
	setWindowSize(map_size * 3, map_size);
	hideCur();


	initMap(_player);
}



void initMap(Player* _player) {
	setColor(red);
	if (_player->hGameTime == 0) {		//新玩家
		for (int i = 0; i < map_size; ++i) {
			for (int j = 0; j < map_size * 2; ++j) {
				if (i == 0 || i == map_size - 1 || j == 0 || j == map_size * 2 - 1) {		//打印墙体
					_player->map[i][j / 2] = WALL;
					gotoXY(j, i);
					if (i == 0 && j == 0) printf("┌");
					else if (i == 0 && j == map_size * 2 - 1) printf("┐");
					else if (i == map_size - 1 && j == 0) printf("└");
					else if (i == map_size - 1 && j == map_size * 2 - 1) printf("┘");
					else if (j == 0 || j == map_size * 2 - 1) printf("│");
					else printf("─");
				}
				else {
					_player->map[i][j / 2] = EMPTY;
				}
			}
		}
	}

	resetColor();
}