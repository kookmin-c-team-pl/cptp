#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "ncurses.h"
#include <iostream>
#include "Snake.h"
#include <time.h>
#include <cstring>
#include <random>
#include "Item.h"
#include <fcntl.h>

#define MAPSIZEH 21
#define MAPSIZEW 21 * 2
#define SCOREB 7
#define SCOREP 5
#define SCOREM 5
#define SCOREG 5
#define MENU 4

class SnakeGame {
public:
	SnakeGame() : run(1), menu(1), gameStart(1), headX(MAPSIZEW / 2), headY(MAPSIZEH / 2), dir(1), dirGate(0), score(0), scoreP(0), scoreM(0), scoreG(0), player(headX, headY), gates(0), item(nullptr), isitem(0) {
		for (int h=0; h<MAPSIZEH; h++) {
			for (int w=0; w<MAPSIZEW; w++) {
				map[h][w] = ' ';
			}
		}
	}
	int getRun() const {
		return run;
	}
	void setRun(int r) {
		run = r;
	}
	int getMenu() const {
		return menu;
	}
	void reduceMenu() {
		if (menu > 1)
			menu = 1;
		else if (menu == 0)
			menu = 1;
	}
	void increaseMenu() {
		if (menu < 4)
			menu = 4;
		else if (menu == 0)
			menu = 1;
	}
	void closeMenu() {
		menu = 0;
	}
	int getGameStart() {
		return gameStart;
	}
	void setGameStart(int g) {
		gameStart = g;
	}
	void setDir(int _dir) {
		dir = _dir;
	}
	void earnScore() {
		score += player.getBody().size();
	}

	void updateGame();
	void updateBodyMap();
	void drawGame(WINDOW *win);
	int checkGame();
	void checkGate();
	void checkItem();
	void midGate(int x, int y);
	void initGame();

	void getKeyInMenu();
	void drawMenu(WINDOW *win);
	void setItem();
	void setGate();

	WINDOW *win;

private:
	int run;
	int menu;
	int gameStart;
	int headX;
	int headY;
	int dir;
	int dirGate;
	int score;
	int scoreP;
	int scoreM;
	int scoreG;
	Snake player;
	int gates;
	Item *item;
	int isitem;

	int map[MAPSIZEH][MAPSIZEW];
};

void SnakeGame::setItem() {
	static time_t lastGateTime = time(nullptr);
    time_t currentTime = time(nullptr);

    if (currentTime - lastGateTime >= 10 || isitem == 0) {
		if (item != nullptr) {
			map[item->getPosition().getY()][item->getPosition().getX()] = ' '; // remove item
			delete item;
			item = nullptr;
			isitem = 0;
		}
		srand(static_cast<unsigned>(time(nullptr)));
		int x = rand() % MAPSIZEW;
		int y = rand() % MAPSIZEH;
		if (x % 2 == 1) {
			x++;
		}
		int type = rand() % 2 == 1 ? '+' : '-';
		// while (map[y][x] != ' ') {
		// 	x = rand() % MAPSIZEW;
		// 	y = rand() % MAPSIZEH;
		// 	if (x % 2 == 1) {
		// 		x++;
		// 	}
		// 	type = rand() % 2 + '0';
		// }
		if (map[y][x] == ' ') {
			item = new Item(x, y, type);
			map[y][x] = type;
			isitem = 1;
		}
		lastGateTime = currentTime;
	}
	if (item != nullptr) {
		// map[item->getPosition().getY()][item->getPosition().getX()] = item->getType() + '0';
	}
}

void SnakeGame::setGate() {
	static time_t lastGateTime = time(nullptr);
    time_t currentTime = time(nullptr);

    if (currentTime - lastGateTime >= 5) {
        srand(static_cast<unsigned>(time(nullptr)));

        gates = 0; // 게이트 생성 전에 gates 변수를 초기화합니다.

        // 게이트 삭제 로직 추가
        for (int i = 0; i < MAPSIZEH; i++) {
            for (int j = 0; j < MAPSIZEW * 2; j++) {
                if (map[i][j] >= 'A' && map[i][j] <= 'B') {
                    map[i][j] = '?';
                }
            }
        }

        while (gates < 2) {
            for (int i = 0; i < MAPSIZEH && gates < 2; i++) {
                for (int j = 0; j < MAPSIZEW * 2 && gates < 2; j += 2) {
                    if (map[i][j] == '?') {
                        if (rand() % 13 == 0) {
                            map[i][j] = 'A' + gates;
                            gates++;
                        }
                    }
                }
            }
        }
        lastGateTime = currentTime;
    }
}

void SnakeGame::updateGame() {
	player.moveBody(dir); // update

	for (int h=0; h < MAPSIZEH; h++) { // 사각형 틀
		for (int w=0; w < MAPSIZEW; w++) {
			if (h == 0 || w == 0 || h + 1 == MAPSIZEH || w + 1 == MAPSIZEW) {
				if (map[h][w] != 'A' && map[h][w] != 'B')
					map[h][w] = L'?';
			} else {
				if (map[h][w] == '*' || map[h][w] == 'O') // remove body
					map[h][w] = ' ';
			}
			map[0][0] = '@';
			map[0][MAPSIZEW - 1] = '@';
			map[MAPSIZEH - 1][0] = '@';
			map[MAPSIZEH - 1][MAPSIZEW - 1] = '@';
		}
	}
	for (int i=1; i<MAPSIZEW / 3; i++) { // wall
		if (gates > 1)
			break;
		map[i][MAPSIZEW / 3] = '?';
	}
	for (int i=1; i<MAPSIZEH / 3; i++) { // wall
		if (gates > 1)
			break;
		map[MAPSIZEH / 3][i] = '?';
	}
	this->setGate();
	this->setItem();
}

void SnakeGame::midGate(int g_x, int g_y) {
	switch (dir)
	{
	case 1:
		if (map[g_y - 1][g_x] != '?' && map[g_y - 1][g_x] != '@') {
			player.headGate(g_x, g_y, 1);
			dir = 1;
		} else if (map[g_y][g_x + 2] != '?' && map[g_y][g_x + 2] != '@') {
			player.headGate(g_x, g_y, 2);
			dir = 2;
		} else if (map[g_y + 1][g_x] != '?' && map[g_y + 1][g_x] != '@') {
			player.headGate(g_x, g_y, 3);
			dir = 3;
		} else if (map[g_y][g_x - 2] != '?' && map[g_y + 1][g_x] != '@') {
			player.headGate(g_x, g_y, 4);
			dir = 4;
		}
		break;
	case 2:
		if (map[g_y][g_x + 2] == ' ') {
			player.headGate(g_x, g_y, 2);
			dir = 2;
		} else if (map[g_y + 1][g_x] == ' ') {
			player.headGate(g_x, g_y, 3);
			dir = 3;
		} else if (map[g_y][g_x - 2] == ' ') {
			player.headGate(g_x, g_y, 4);
			dir = 4;
		} else if (map[g_y - 1][g_x] == ' ') {
			player.headGate(g_x, g_y, 1);
			dir = 1;
		}
		break;
	case 3:
		if (map[g_y + 1][g_x] == ' ') {
			player.headGate(g_x, g_y, 3);
			dir = 3;
		} else if (map[g_y][g_x - 2] == ' ') {
			player.headGate(g_x, g_y, 4);
			dir = 4;
		} else if (map[g_y - 1][g_x] == ' ') {
			player.headGate(g_x, g_y, 1);
			dir = 1;
		} else if (map[g_y][g_x + 2] == ' ') {
			player.headGate(g_x, g_y, 2);
			dir = 2;
		}
		break;
	case 4:
		if (map[g_y][g_x - 2] == ' ') {
			player.headGate(g_x, g_y, 4);
			dir = 4;
		} else if (map[g_y - 1][g_x] == ' ') {
			player.headGate(g_x, g_y, 1);
			dir = 1;
		} else if (map[g_y][g_x + 2] == ' ') {
			player.headGate(g_x, g_y, 2);
			dir = 2;
		} else if (map[g_y + 1][g_x] == ' ') {
			player.headGate(g_x, g_y, 3);
			dir = 3;
		}
		break;
	default:
		break;
	}
}

void SnakeGame::checkGate() {
	Position head = player.getBody().front();
	int g_x=0, g_y=0;
	if (map[head.getY()][head.getX()] == 'A') { // A
		for (int i=0; i<MAPSIZEH; i++) { // find B
			for (int j=0; j<MAPSIZEW; j++) {
				if (map[i][j] == 'B') {
					g_y = i;
					g_x = j;
				}
			}
		}
		if (g_x == 0) {
			player.headGate(g_x, g_y, 2);
			dir = 2;
		} else if (g_y == 0) {
			player.headGate(g_x, g_y, 3);
			dir = 3;
		} else if (g_x * 2 == MAPSIZEW) {
			player.headGate(g_x, g_y, 4);
			dir = 4;
		} else if (g_y - 1 == MAPSIZEH) {
			player.headGate(g_x, g_y, 1);
			dir = 1;
		} else {
			midGate(g_x, g_y);
		}
		scoreG++;
	} else if (map[head.getY()][head.getX()] == 'B') { // B
		for (int i=0; i<MAPSIZEH; i++) { // find A
			for (int j=0; j<MAPSIZEW; j++) {
				if (map[i][j] == 'A') {
					g_y = i;
					g_x = j;
				}
			}
		}
		if (g_x == 0) {
			player.headGate(g_x, g_y, 2);
			dir = 2;
		} else if (g_y == 0) {
			player.headGate(g_x, g_y, 3);
			dir = 3;
		} else if (g_x * 2 == MAPSIZEW) {
			player.headGate(g_x, g_y, 4);
			dir = 4;
		} else if (g_y - 1 == MAPSIZEH) {
			player.headGate(g_x, g_y, 1);
			dir = 1;
		} else {
			midGate(g_x, g_y);
		}
		scoreG++;
	}
}

void SnakeGame::updateBodyMap() {
	std::vector<Position> body = player.getBody(); // update body
	std::vector<Position>::iterator it;
	for (it = body.begin(); it != body.end(); it++) {
		int x = it->getX();
		int y = it->getY();
		if (checkGame() == 0) {
			if (it == body.begin()) {
				map[y][x] = L'O';
			} else {
				map[y][x] = '*';
			}
		}
	}
}

int SnakeGame::checkGame() {
	Position head = player.getBody().front();
	if (map[head.getY()][head.getX()] == '@' || map[head.getY()][head.getX()] == '?' || map[head.getY()][head.getX()] == '*') {
		// this->updateGame();
		return 1;
	} else if (player.getBody().size() < 3) {
		return 1;
	}
	return 0;
}

void SnakeGame::checkItem() {
	Position head = player.getBody().front();
	int check = map[head.getY()][head.getX()];
	if (check == '-' || check == '+') { // item
		isitem = 0;
		if (check == '+')
			scoreP++;
		else if (check == '-')
			scoreM++;
	}
	player.removeTail(check);
}

void SnakeGame::drawGame(WINDOW *win) {
	wclear(win);
	// box(win, 0, 0);
	for (int h=0; h < MAPSIZEH; h++) {
		for (int w=0; w < MAPSIZEW; w++) {
			// wprintw(win, " ");
			int c = map[h][w];
			mvwprintw(win, h, w, "%c", c);
		}
	}
	std::vector<Position> body = player.getBody();
	// mvwprintw(win, 0, 15, "x:%d, y:%d", head.getX(), head.getY());
	mvwprintw(win, 0, MAPSIZEW + 1, "**SCORE BOARD**");
	mvwprintw(win, 2, MAPSIZEW + 2, std::to_string(score).c_str());
	if (body.size() >= SCOREB)
		mvwprintw(win, 4, MAPSIZEW + 2, "B: %d / %d (v)", body.size(), SCOREB);
	else
		mvwprintw(win, 4, MAPSIZEW + 2, "B: %d / %d ( )", body.size(), SCOREB);
	if (scoreP >= SCOREP)
		mvwprintw(win, 6, MAPSIZEW + 2, "P: %d / %d (v)", scoreP, SCOREP);
	else
		mvwprintw(win, 6, MAPSIZEW + 2, "P: %d / %d ( )", scoreP, SCOREP);
	if (scoreM >= SCOREM)
		mvwprintw(win, 8, MAPSIZEW + 2, "M: %d / %d (v)", scoreM, SCOREM);
	else
		mvwprintw(win, 8, MAPSIZEW + 2, "M: %d / %d ( )", scoreM, SCOREM);
	if (scoreG >= SCOREG)
		mvwprintw(win, 10, MAPSIZEW + 2, "G: %d / %d (v)", scoreG, SCOREG);
	else
		mvwprintw(win, 10, MAPSIZEW + 2, "G: %d / %d ( )", scoreG, SCOREG);
	// wrefresh(win);
}

void SnakeGame::initGame() {
	run = (1);
	menu = (0);
	gameStart = (1);
	headX = (MAPSIZEW / 2);
	headY = (MAPSIZEH / 2);
	dir = (1);
	dirGate = (0);
	score = (0);
	scoreP = 0;
	scoreM = 0;
	scoreG = 0;
	player = Snake(headX, headY);
	gates = (0);
}

void SnakeGame::getKeyInMenu() {
	int ch = getch();
	WINDOW *score_win;
	switch (ch) {
		case (KEY_UP):
			
			break;
		case (KEY_RIGHT):
			this->increaseMenu();
			break;
		case (KEY_DOWN):
			
			break;
		case (KEY_LEFT):
			this->reduceMenu();
			break;
		case ('z'):
			switch (this->getMenu()) {
				case (1):
					this->closeMenu();
					this->setGameStart(1);
					initGame();
					break;
				case (4):
					wclear(stdscr);
					werase(stdscr);
					exit(0);
					break;
			}
			break;
		default:
			break;
	}
}

void SnakeGame::drawMenu(WINDOW *win) {
	// wclear(win);
	init_pair(2,COLOR_RED,COLOR_BLUE);
	attron(COLOR_PAIR(2));
	wbkgd(win,COLOR_PAIR(2));
	attroff(COLOR_PAIR(2));
	box(win, 0, 0);
	int maxSubX, maxSubY;
	getmaxyx(win, maxSubY, maxSubX);
	mvwprintw(win, 0, (maxSubX - strlen("Menu")) / 2, "Menu");
	mvwprintw(win, 1, 1, "Press Z.  Latest Score:%d       ", score);

	if (this->getMenu() == 1) {
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 10, "Start");
		wattroff(win, A_STANDOUT);
		// mvwprintw(win, maxSubY / 2, 15, "Score");
		// mvwprintw(win, maxSubY / 2, 25, "Option");
		mvwprintw(win, maxSubY / 2, 30, "Out");
	}
	else if (this->getMenu() == 4) {
		mvwprintw(win, maxSubY / 2, 10, "Start");
		// mvwprintw(win, maxSubY / 2, 15, "Score");
		// mvwprintw(win, maxSubY / 2, 25, "Option");
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 30, "Out");
		wattroff(win, A_STANDOUT);
	}
	wrefresh(win);

	getKeyInMenu();
}

#endif
