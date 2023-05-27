#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "ncurses.h"
#include "SnakeBody.h"

class Snake {
public:
	Snake(int x, int y) {
		SnakeBody head(x, y);
		body.push_back(head);
	}
	void addBody(WINDOW *win, int y, int x) {
		SnakeBody sb(x, y);
		body.push_back(sb);
	}
	void removeTail(WINDOW *win, int y, int x) {
		body.pop_back();
	}
	void moveBody(int dir) {
		std::vector<SnakeBody>::iterator it = body.begin();
		SnakeBody past(*it);
		if (dir == 1) { // up
			it->moveUp();
		} else if (dir == 2) { // right
			it->moveRight();
		} else if (dir == 3) { // down
			it->moveDown();
		} else if (dir == 4) { // left
			it->moveLeft();
		} it++;
		for (; it != body.end(); it++) {
			SnakeBody temp = *it;
			*it = past;
			past = temp;
		}
	}

private:
	std::vector<SnakeBody> body;
};

#endif