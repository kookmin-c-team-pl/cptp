
#include "SnakeGame.h"
#include "unistd.h"

int main() {
	SnakeGame game;
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	start_color();
	box(stdscr, 0, 0);
	printw("mainWin");

	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	// WINDOW *win = subwin(stdscr, 5, 60, 5, 10);
	refresh();

	while (game.getRun()) {
		if (game.getMenu()) {
			// game.drawMenu(win);
		}
		if (game.getGameStart()) {
			game.updateGame();
			game.drawGame(stdscr);
		}
		int ch = getch();
		switch (ch) {
			case (KEY_UP):
				game.setDir(1);
				break;
			case (KEY_RIGHT):
				game.setDir(2);
				break;
			case (KEY_DOWN):
				game.setDir(3);
				break;
			case (KEY_LEFT):
				game.setDir(4);
				break;
			default:
				break;
		}
		usleep(500000);
	}
	
	endwin();
	return 0;
}