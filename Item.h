class Item {
public:
    Item(int x, int y, const std::string& type) : position(Position(x, y)), type(type) {}

    const Position& getPosition() {
        return position;
    }

    const std::string& getType() {
        return type;
    }

    void SnakeGame::drawGame(WINDOW *win) {
        for (int i = 0; i < 2; i++) {
            if (currentItems[i].type != NONE) {

                if (currentItems[i].type == POISON) {
                    mvwprintw(win, currentItems[i].y, currentItems[i].x, "P");
                } else if (currentItems[i].type == GROWTH) {
                    mvwprintw(win, currentItems[i].y, currentItems[i].x, "G");
                }
            }
        }
    }

    void SnakeGame::generateItem() {
    for (int i = 0; i < 2; i++) {
        currentItems[i].x = getRandomNumber(1, maxX - 2);
        currentItems[i].y = getRandomNumber(1, maxY - 2);
        previousItems[i] = currentItems[i];
    }

    int itemType1 = getRandomNumber(0, 1);
    int itemType2 = getRandomNumber(0, 1);
    currentItems[0].type = (itemType1 == 0) ? POISON : GROWTH;
    currentItems[1].type = (itemType2 == 0) ? POISON : GROWTH;
}

private:
    Position position;
    std::string type;
};

#endif