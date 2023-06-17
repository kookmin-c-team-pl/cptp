#ifndef POSITION_H
#define POSITION_H

class Position {
private:
	int x;
	int y;
public:
	Position(int _x, int _y): x(_x), y(_y) {}
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