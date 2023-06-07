#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "ncurses.h"
#include <iostream>
#include "Snake.h"
#include <time.h>
#include <cstring>
#include <random>

#define MAPSIZEW 18 * 2
#define MAPSIZEH 18
#define MENU 4

class SnakeGame {
public:
	SnakeGame() : run(1), menu(1), gameStart(1), headX(MAPSIZEW / 2), headY(MAPSIZEH / 2), dir(1), score(0), player(headX, headY) {
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
			menu--;
		else if (menu == 0)
			menu = 1;
	}
	void increaseMenu() {
		if (menu < 4)
			menu++;
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
	void drawGame(WINDOW *win);
	int checkGame();

	void getKeyInMenu();
	void drawMenu(WINDOW *win);
	void setGate();

private:
	int run;
	int menu;
	int gameStart;
	int headX;
	int headY;
	int dir;
	int score;
	Snake player;
	int gates;

	int map[MAPSIZEH][MAPSIZEW];

	WINDOW *win;
};

void SnakeGame::setGate() {
	srand(time(NULL));
	while (gates < 2) {
		for (int i=0; i<MAPSIZEH; i++) {
			for (int j=0; j<MAPSIZEW; j++) {
				if (map[i][j] == '?') {
					if (rand() % 13 == 0) {
						map[i][j] = 'G';
						gates++;
					}
				}
			}
		}
	}
}

void SnakeGame::updateGame() {
	this->setGate();

	player.moveBody(dir, 0); // update

	for (int h=0; h < MAPSIZEH; h++) { // 사각형 틀
		for (int w=0; w < MAPSIZEW; w++) {
			if (h == 0 || w == 0 || h + 1 == MAPSIZEH || w + 1 == MAPSIZEW) {
				if (map[h][w] != 'G')
					map[h][w] = '?';
			} else {
				map[h][w] = ' ';
			}
			map[0][0] = '@';
			map[0][MAPSIZEW - 1] = '@';
			map[MAPSIZEH - 1][0] = '@';
			map[MAPSIZEH - 1][MAPSIZEW - 1] = '@';
		}
	}
	for (int i=1; i<MAPSIZEH / 3; i++) { // wall
		if (map[i][MAPSIZEW / 3] != 'G')
			map[i][MAPSIZEW / 3] = '?';
	}
	std::vector<Position> body = player.getBody();
	std::vector<Position>::iterator it;
	for (it = body.begin(); it != body.end(); it++) {
		int x = it->getX();
		int y = it->getY();
		if (map[y][x] == ' ') {
			if (it == body.begin()) {
				map[y][x] = 'o';
			} else {
				map[y][x] = '*';
			}
		}
	}
}

int SnakeGame::checkGame() {
	Position head = player.getBody().front();
	if (map[head.getY()][head.getX()] == '@') {
		this->gameStart = 0;
		this->menu = 1;
		return 1;
	}
	return 0;
}

void SnakeGame::drawGame(WINDOW *win) {
	wclear(win);
	// box(win, 0, 0);
	for (int h=0; h < MAPSIZEH; h++) {
		for (int w=0; w < MAPSIZEW; w++) {
			// wprintw(win, " ");
			char c = map[h][w];
			mvwprintw(win, h, w, &c);
		}
	}
	mvwprintw(win, 0, 3, std::to_string(score).c_str());
	// wrefresh(win);
}

void SnakeGame::getKeyInMenu() {
	int ch = getch();
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
	init_pair(2,COLOR_RED,COLOR_BLUE);
	attron(COLOR_PAIR(2));
	wbkgd(win,COLOR_PAIR(2));
	attroff(COLOR_PAIR(2));
	box(win, 0, 0);
	int maxSubX, maxSubY;
	getmaxyx(win, maxSubY, maxSubX);
	mvwprintw(win, 0, (maxSubX - strlen("subWin")) / 2, "subWin");
	mvwprintw(win, 1, 1, "press Q, A, D, Z");

	if (this->getMenu() == 1) {
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 5, "Start");
		wattroff(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 15, "Score");
		mvwprintw(win, maxSubY / 2, 25, "Option");
		mvwprintw(win, maxSubY / 2, 35, "Out\r");
	} else if (this->getMenu() == 2) {
		mvwprintw(win, maxSubY / 2, 5, "Start");
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 15, "Score");
		wattroff(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 25, "Option");
		mvwprintw(win, maxSubY / 2, 35, "Out\r");
	} else if (this->getMenu() == 3) {
		mvwprintw(win, maxSubY / 2, 5, "Start");
		mvwprintw(win, maxSubY / 2, 15, "Score");
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 25, "Option");
		wattroff(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 35, "Out\r");
	} else if (this->getMenu() == 4) {
		mvwprintw(win, maxSubY / 2, 5, "Start");
		mvwprintw(win, maxSubY / 2, 15, "Score");
		mvwprintw(win, maxSubY / 2, 25, "Option");
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 35, "Out\r");
		wattroff(win, A_STANDOUT);
	}
	wrefresh(win);

	getKeyInMenu();
}

#endif
