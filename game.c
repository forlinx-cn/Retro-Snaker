#include "game.h"

int loadGamePage(Player* _player) {
	setWindowSize(map_size * 3, map_size + 6);
	hideCur();
	initMap(_player);

	if (_player->length == 0) {				//如果是新玩家或新游戏就初始化蛇
		_player->length = _player->length ? _player->length : 3;		//初始化蛇长度
		/*---------初始化蛇--------*/
		srand(time(NULL));
		_player->snake[0].x = rand() % (map_size - 10) + 5;
		_player->snake[0].y = rand() % (map_size - 10) + 5;
		_player->map[_player->snake->x][_player->snake->y] = HEAD;

		_player->snake[1].x = _player->snake[0].x - 1;
		_player->snake[1].y = _player->snake[0].y;
		_player->map[_player->snake[1].x][_player->snake[1].y] = BODY;
		_player->snake[2].x = _player->snake[0].x - 2;
		_player->snake[2].y = _player->snake[0].y;
		_player->map[_player->snake[2].x][_player->snake[2].y] = BODY;
	}
	printSnake(_player);
	
	return 1;
}

void printSnake(Player* _player) {
	for (int i = 0; i < _player->length; ++i) {
		gotoXY(_player->snake[i].x * 2, _player->snake[i].y);
		printf("■");
	}
}


void initMap(Player* _player) {
	setColor(red);
	//打印墙
	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size * 2; ++j) {
			if (i == 0 || i == map_size - 1 || j == 0 || j == map_size * 2 - 1) {
				gotoXY(j, i);
				if (i == 0 && j == 0) printf("┌");
				else if (i == 0 && j == map_size * 2 - 1) printf("┐");
				else if (i == map_size - 1 && j == 0) printf("└");
				else if (i == map_size - 1 && j == map_size * 2 - 1) printf("┘");
				else if (j == 0 || j == map_size * 2 - 1) printf("│");
				else printf("─");

			}
			if (i == 0 || i == map_size - 1 || j / 2 == 0 || j / 2 == map_size - 1) {
				_player->map[j / 2][i] = WALL;
			}
		}
	}
	setColor(yellow);
	for (int x = 1; x < map_size - 1; ++x) {			//打印墙内内容
		for (int y = 1; y < map_size - 1; ++y) {
			if (_player->map[x][y] == FOOD) {
				gotoXY(2 * x, y);
				printf("●");
			}
		}
	}
	
	resetColor();
}

int snake_move(Player* _player) {
	resetColor();
	SnakeNode tail = _player->snake[_player->length - 1];
	gotoXY(tail.x * 2, tail.y);
	printf("  ");
	for (int i = _player->length - 1; i > 0; --i) {
		_player->snake[i] = _player->snake[i - 1];
	}
	_player->map[tail.x][tail.y] = EMPTY;
	_player->map[_player->snake[0].x][_player->snake[0].y] = BODY;
	switch (_player->direction) {
	case 'w':
		_player->snake[0].y--;
		break;
	case 'a':
		_player->snake[0].x--;
		break;
	case 's':
		_player->snake[0].y++;
		break;
	case 'd':
		_player->snake[0].x++;
		break;
	}
	switch (_player->map[_player->snake[0].x][_player->snake[0].y])
	{
	case WALL:
	case BODY:
		return 0;
	case FOOD:
		snake_growth(1, _player, tail);
		_player->food_num--;
		creat_food(1, _player);
		break;
	case EMPTY:
		break;
	default:
		break;
	}
	_player->map[_player->snake[0].x][_player->snake[0].y] = HEAD;
	gotoXY(_player->snake[0].x * 2, _player->snake[0].y);
	printf("■");
	return 1;
}

void direction_change(char new_direction, Player* _player) {
	if (new_direction != 'w' && new_direction != 'a' && new_direction != 's' && new_direction != 'd') return;
	if (new_direction == _player->direction) return;
	if (new_direction == 'w' && _player->direction == 's') return;
	if (new_direction == 's' && _player->direction == 'w') return;
	if (new_direction == 'a' && _player->direction == 'd') return;
	if (new_direction == 'd' && _player->direction == 'a') return;
	_player->direction = new_direction;
}

void creat_food(int weight, Player* _player) {
	setColor(yellow);
	for (int i = _player->food_num; i < weight; ++i) {
		int x, y;
		do {
			x = rand() % map_size;
			y = rand() % map_size;
		} while (_player->map[x][y] != EMPTY);
		_player->map[x][y] = FOOD;
		gotoXY(0, map_size + 1);
		gotoXY(2 * x, y);
		printf("●");

		_player->food_num++;
	}
	resetColor();
}

void snake_growth(int weight, Player* _player, SnakeNode tail) {
	_player->length += weight;
	_player->snake[_player->length - 1] = tail;
	_player->map[tail.x][tail.y] = BODY;
	gotoXY(tail.x * 2, tail.y);
	printf("■");
	_player->score++;
	gotoXY(map_size * 2 + 1, 0);
	printf("%s: %3d分", _player->name, _player->score);
}

int isDeath(Player* _player) {
	return _player->hGameTime == 0 && _player->length > 3;
}