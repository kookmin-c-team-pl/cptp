#include "ncurses.h"
#include <vector>
#include "unistd.h"

// 게임의 상태 정의
enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

// Snake의 위치 정보 정의
struct SnakeSegment {
    int y, x;
    SnakeSegment(int newY, int newX) : y(newY), x(newX) {}
};

// 게임의 상수 정의
const int GAME_WIDTH = 40;
const int GAME_HEIGHT = 20;
const int START_X = GAME_WIDTH / 2;
const int START_Y = GAME_HEIGHT / 2;
const int INITIAL_LENGTH = 4;
const int DELAY_MS = 100;

int main() {
    // ncurses 초기화
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    // 게임 변수 초기화
    int score = 0;
    int dirY = 0, dirX = 1;
    GameState gameState = GameState::MENU;
    std::vector<SnakeSegment> snake;

    while (true) {
        clear();

        // 메뉴 상태 처리
        if (gameState == GameState::MENU) {
            mvprintw(GAME_HEIGHT / 2 - 1, GAME_WIDTH / 2 - 4, "Snake Game");
            mvprintw(GAME_HEIGHT / 2, GAME_WIDTH / 2 - 9, "Press any key to start");
            refresh();
            getch();
            gameState = GameState::PLAYING;
        }
        // 플레이 중인 상태 처리
        else if (gameState == GameState::PLAYING) {
            // 방향키 입력 처리
            int input = getch();
            switch (input) {
                case KEY_UP:
                    dirY = -1;
                    dirX = 0;
                    break;
                case KEY_DOWN:
                    dirY = 1;
                    dirX = 0;
                    break;
                case KEY_LEFT:
                    dirY = 0;
                    dirX = -1;
                    break;
                case KEY_RIGHT:
                    dirY = 0;
                    dirX = 1;
                    break;
                default:
                    break;
            }

            // Snake 이동 처리
            int nextY = snake[0].y + dirY;
            int nextX = snake[0].x + dirX;

            // 벽과 충돌 검사
            if (nextY < 0 || nextY >= GAME_HEIGHT || nextX < 0 || nextX >= GAME_WIDTH) {
                gameState = GameState::GAME_OVER;
            }
            // 자기 자신과 충돌 검사
            for (size_t i = 1; i < snake.size(); ++i) {
                if (snake[i].y == nextY && snake[i].x == nextX) {
                    gameState = GameState::GAME_OVER;
                    break;
                }
            }

            // Snake 길이 관리
            snake.insert(snake.begin(), SnakeSegment(nextY, nextX));
            if (snake.size() > INITIAL_LENGTH) {
                snake.pop_back();
            }

            // 화면에 Snake 그리기
            for (const auto& segment : snake) {
                mvprintw(segment.y, segment.x, "O");
            }

            // 화면 업데이트
            refresh();
            usleep(DELAY_MS * 1000);
        }
        // 게임 오버 상태 처리
        else if (gameState == GameState::GAME_OVER) {
            mvprintw(GAME_HEIGHT / 2 - 1, GAME_WIDTH / 2 - 5, "Game Over");
            mvprintw(GAME_HEIGHT / 2, GAME_WIDTH / 2 - 7, "Score: %d", score);
            mvprintw(GAME_HEIGHT / 2 + 1, GAME_WIDTH / 2 - 9, "Press any key to restart");
            refresh();
            getch();
            gameState = GameState::MENU;

            // 게임 초기화
            score = 0;
            dirY = 0;
            dirX = 1;
            snake.clear();
            for (int i = 0; i < INITIAL_LENGTH; ++i) {
                snake.push_back(SnakeSegment(START_Y, START_X - i));
            }
        }
    }

    // ncurses 종료
    endwin();
    return 0;
}
