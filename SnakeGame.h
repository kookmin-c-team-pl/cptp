#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "ncurses.h"
#include <iostream>
#include "Snake.h"

#define MAPSIZEW 21
#define MAPSIZEH 21

class SnakeGame {
public:
	SnakeGame() : run(1), menu(1), gameStart(1), headX(MAPSIZEW / 2), headY(MAPSIZEH / 2), dir(1), snake(headX, headY) {
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

	void drawMenu(WINDOW *win);
	void drawGame(WINDOW *win);

private:
	int run;
	int menu;
	int gameStart;
	int headX;
	int headY;
	int dir;
	Snake snake;

	WINDOW *win;
};

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

void SnakeGame::drawGame(WINDOW *win) {
	snake.moveBody(dir);
	wbkgd(win, COLOR_RED);
}

#endif
