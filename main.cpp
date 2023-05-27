
#include "SnakeGame.h"
#include "unistd.h"

int main() {
	SnakeGame game;
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	start_color();
	box(stdscr, 0, 0);
	printw("mainWin");

	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	WINDOW *win = subwin(stdscr, 5, 20, 5, 10);
	refresh();

	while (game.getRun()) {
		// if (game.getMenu() > 0) {
		// 	game.drawMenu(win);
		// } else if (game.getGameStart())
		{
			game.updateGame();
			game.drawGame(stdscr);
			game.checkGame();
			usleep(500000); // <-
		}
		// int ch = wgetch(stdscr); // same
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
		flushinp(); // clear buffer
	}
	
	endwin();
	return 0;
}