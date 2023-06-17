#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include "Position.h"
#include "ncurses.h"

class Item {
public:
    Item(int x, int y, int type) : position(Position(x, y)), type(type) {}

    const Position& getPosition() const {
        return this->position;
    }

    int getType() const {
        return this->type;
    }

private:
    Position position;
    int type;
};

#endif