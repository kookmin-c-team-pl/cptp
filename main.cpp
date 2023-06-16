
#include "SnakeGame.h"
#include "unistd.h"

int main() {
	SnakeGame game;
	initscr();
	// cbreak();
	// noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	start_color();
	box(stdscr, 0, 0);
	printw("mainWin");

	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	WINDOW *win = subwin(stdscr, 5, 50, 5, 10);
	// refresh();

	while (game.getRun()) {
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
			case ('z'):
				;
			default:
				break;
		}
		flushinp(); // clear buffer
		if (game.getMenu() > 0) {
			game.drawMenu(win);
			continue;
		} else if (game.getGameStart())
		{
			game.updateGame();
			game.checkGate();
			game.updateBody();
			game.drawGame(stdscr);
			if (game.checkGame()) {
				wclear(stdscr);
			}
			usleep(500000); // <-
			game.earnScore();
		}
		// int ch = wgetch(stdscr); // same
	}
	
	endwin();
	return 0;
}