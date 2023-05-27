#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "ncurses.h"
#include <iostream>
#include "Snake.h"

#define MAPSIZEW 21
#define MAPSIZEH 21

class SnakeGame {
public:
	SnakeGame() : run(1), menu(1), gameStart(1), headX(MAPSIZEW / 2), headY(MAPSIZEH / 2), dir(1), player(headX, headY) {
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
		if (menu < 3)
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

	void updateGame();

	void drawMenu(WINDOW *win);
	void drawGame(WINDOW *win);

private:
	int run;
	int menu;
	int gameStart;
	int headX;
	int headY;
	int dir;
	Snake player;

	int map[MAPSIZEH][MAPSIZEW];

	WINDOW *win;
};

void SnakeGame::updateGame() {
	player.moveBody(dir); // update

	for (int h=0; h < MAPSIZEH; h++) {
		for (int w=0; w < MAPSIZEW; w++) {
			map[h][w] = ' ';
		}
	}
	std::vector<Position> body = player.getBody();
	std::vector<Position>::iterator it;
	for (it = body.begin(); it != body.end(); it++) {
		int x = it->getX();
		int y = it->getY();
		map[y][x] = 'O';
	}
}

void SnakeGame::drawGame(WINDOW *win) {
	wclear(win);
	box(win, 0, 0);
	for (int h=1; h < MAPSIZEH; h++) {
		for (int w=1; w < MAPSIZEW; w++) {
			// wprintw(win, " ");
			char c = map[h][w];
			mvwprintw(win, h, w, &c);
		}
	}
	wrefresh(win);
}

void SnakeGame::drawMenu(WINDOW *win) {
	init_pair(2,COLOR_RED,COLOR_BLUE);
	attron(COLOR_PAIR(2));
	wbkgd(win,COLOR_PAIR(2));
	box(win, 0, 0);
	int maxSubX, maxSubY;
	getmaxyx(win, maxSubY, maxSubX);
	mvwprintw(win, 0, (maxSubX - strlen("subWin")) / 2, "subWin");
	mvwprintw(win, 1, 1, "press Q, A, D, Z");

	if (this->getMenu() == 1) {
		mvwprintw(win, maxSubY / 2, 15, "Score");
		mvwprintw(win, maxSubY / 2, 25, "Option");
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 5, "Start\r");
		wattroff(win, A_STANDOUT);
	}
	else if (this->getMenu() == 2) {
		mvwprintw(win, maxSubY / 2, 5, "Start");
		mvwprintw(win, maxSubY / 2, 25, "Option");
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 15, "Score\r");
		wattroff(win, A_STANDOUT);
	}
	else if (this->getMenu() == 3) {
		mvwprintw(win, maxSubY / 2, 5, "Start");
		mvwprintw(win, maxSubY / 2, 15, "Score");
		wattron(win, A_STANDOUT);
		mvwprintw(win, maxSubY / 2, 25, "Option\r");
		wattroff(win, A_STANDOUT);
	}
}

#endif
