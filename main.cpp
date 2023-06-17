
#include "SnakeGame.h"
#include "unistd.h"

int main() {
	SnakeGame game;
	initscr();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	start_color();
	box(stdscr, 0, 0);
	// printw("mainWin");

	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);

	game.win = subwin(stdscr, 10, 45, 5, 20);
	// refresh();

	while (game.getRun()) {
		if (game.getMenu() > 0) {
			game.drawMenu(game.win);
			continue;
		} else if (game.getGameStart())
		{
			int ch = wgetch(stdscr);
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
			game.updateGame();
			game.checkGate();
			game.checkItem();
			game.updateBodyMap();
			game.drawGame(stdscr);
			if (game.checkGame()) {
				game.setGameStart(0);
				game.reduceMenu();
				wclear(stdscr);
				continue;
			}
			getch(); // clear buffer
			flushinp(); // clear buffer stack
			usleep(500000); // <-
			game.earnScore();
		}
		// int ch = wgetch(stdscr); // same
	}
	
	endwin();
	return 0;
}