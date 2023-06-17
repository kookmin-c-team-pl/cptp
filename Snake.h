#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "ncurses.h"
#include "Position.h"

class Snake {
public:
	Snake(int x, int y): head(Position(x, y)) {
		body.push_back(Position(x, y));
		body.push_back(Position(x - 2, y));
		body.push_back(Position(x - 4, y));
	}
	const std::vector<Position> &getBody() {
		return body;
	}
	void moveBody(int dir) {
		// head insert
		if (dir == 1) { // up
			body.insert(body.begin(), Position(head.getX(), head.getY() - 1));
		} else if (dir == 2) { // right
			body.insert(body.begin(), Position(head.getX() + 2, head.getY()));
		} else if (dir == 3) { // down
			body.insert(body.begin(), Position(head.getX(), head.getY() + 1));
		} else if (dir == 4) { // left
			body.insert(body.begin(), Position(head.getX() - 2, head.getY()));
		}
		head = body.front();
	}
	void removeTail(int i) {
		// tail remove
		switch (i)
		{
		case 0:
			body.pop_back(); // remove tail (normal)
			break;
		case '+':
			break; // body + 1
		case '-':
			body.pop_back();
			body.pop_back(); // body - 1
			break;
		
		default:
			body.pop_back(); // remove tail (normal)
			break;
		}
	}
	void headGate(int x, int y, int d) {
		if (d == 1) {
			body.front().setX(x);
			body.front().setY(y - 1);
			head = body.front();
		} else if (d == 2) {
			body.front().setX(x + 2);
			body.front().setY(y);
			head = body.front();
		} else if (d == 3) {
			body.front().setX(x);
			body.front().setY(y + 1);
			head = body.front();
		} else if (d == 4) {
			body.front().setX(x - 2);
			body.front().setY(y);
			head = body.front();
		}
	}

private:
	std::vector<Position> body;
	Position head;
};

#endif