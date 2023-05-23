
#include "SnakeGame.h"

int main() {
	SnakeGame game;
	initscr();
	start_color();
	box(stdscr, 0, 0);
	printw("mainWin");

	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	WINDOW *win = subwin(stdscr, 5, 60, 5, 10)
	refresh();

	while (game.getRun()) {
		if (game.getMenu()) {
			game.drawMenu(win);
		}
		if (game.getGameStart()) {
			game.drawGame(stdscr);
		}
		refresh();
		char ch = wgetch(win);
		switch (ch) {
			case ('a'):
				game.reduceMenu();
				break;
			case ('d'):
				game.increaseMenu();
				break;
			case ('q'):
				game.setRun(0);
			case ('z'):
				switch (game.getMenu()) {
					case 1:
						game.setGameStart(1);
						game.closeMenu();
						werase(win);
						// wclear(win);
				}
			default:
				break;
		}
		// std::cout << "your input: " << ch << std::endl; //
	}
	
	endwin();
	return 0;
}