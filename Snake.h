#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "ncurses.h"
#include "Position.h"

class Snake {
public:
	Snake(int x, int y): head(Position(x, y)) {
		body.push_back(Position(x, y));
		body.push_back(Position(x - 1, y));
		body.push_back(Position(x - 2, y));
	}
	const std::vector<Position> &getBody() {
		return body;
	}
	void removeTail(WINDOW *win) {
		Position tail = body.back();
		body.pop_back();
		mvwprintw(win, tail.getX(), tail.getY(), " ");
	}
	void moveBody(int dir, int item = 0) {
		if (dir == 1) { // up
			body.insert(body.begin(), head.getUpPosition());
		} else if (dir == 2) { // right
			body.insert(body.begin(), head.getRightPosition());
		} else if (dir == 3) { // down
			body.insert(body.begin(), head.getDownPosition());
		} else if (dir == 4) { // left
			body.insert(body.begin(), head.getLeftPosition());
		}
		head = body.front();
		switch (item)
		{
		case 0:
			body.pop_back(); // remove tail
			break;
		case 1:
			break; // body + 1
		case 2:
			body.pop_back();
			body.pop_back(); // body - 1
		
		default:
			break;
		}
	}

private:
	std::vector<Position> body;
	Position head;
};

#endif