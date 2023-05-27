#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "ncurses.h"

class SnakeBody {
public:
	SnakeBody(int x, int y): x(x), y(y) {
		mvprintw(y, x, "o");
	}
	SnakeBody(const SnakeBody &sb): x(sb.x), y(sb.y) {
		mvprintw(y, x, "o");
	}
	void setPosition(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void moveUp() {
		y--;
	}
	void moveDown() {
		y++;
	}
	void moveLeft() {
		x--;
	}
	void moveRight() {
		x++;
	}
private:
	int x;
	int y;
};

#endif