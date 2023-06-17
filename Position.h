#ifndef POSITION_H
#define POSITION_H

#include <vector>

class Position {
private:
	int x;
	int y;
public:
	Position(int _x, int _y): x(_x), y(_y) {}
	Position getUpPosition() {
		return (Position(x, y - 1));
	}
	Position getDownPosition() {
		return (Position(x, y + 1));
	}
	Position getLeftPosition() {
		return (Position(x - 1, y));
	}
	Position getRightPosition() {
		return (Position(x + 1, y));
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void setX(int _x) {
		x = _x;
	}
	void setY(int _y) {
		y = _y;
	}
};

#endif