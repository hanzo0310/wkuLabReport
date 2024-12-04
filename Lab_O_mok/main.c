#include "var.h"
#include "rules.h"
#include "screen.h"
#include "AI.h"

int main() {
    int board[SIZE][SIZE] = { 0 }; // 바둑판 초기화
    int highlightPos[2] = { 0, 0 }; // 커서 초기 위치
    int turn = 0; // 0: 플레이어 1, 1: AI
    int lastPlayerRow = -1, lastPlayerCol = -1; // 플레이어가 마지막으로 둔 위치
    int aiFirstMove = 1; // AI의 첫 번째 수 상태

    srand((unsigned int)time(NULL)); // 난수 초기화

    while (1) {
        printBoardWithHighlight(board, highlightPos, turn);

        if (turn == 0) { // 플레이어의 턴
            if (_kbhit()) {
                int key = _getch();

                if (key == 224) {
                    key = _getch();
                    switch (key) {
                    case 75: // 왼쪽 방향키
                        if (highlightPos[1] > 0) highlightPos[1]--;
                        break;
                    case 77: // 오른쪽 방향키
                        if (highlightPos[1] < SIZE - 1) highlightPos[1]++;
                        break;
                    case 72: // 위쪽 방향키
                        if (highlightPos[0] > 0) highlightPos[0]--;
                        break;
                    case 80: // 아래쪽 방향키
                        if (highlightPos[0] < SIZE - 1) highlightPos[0]++;
                        break;
                    }
                }
                else {
                    switch (key) {
                    case 'a':
                        if (highlightPos[1] > 0) highlightPos[1]--;
                        break;
                    case 'd':
                        if (highlightPos[1] < SIZE - 1) highlightPos[1]++;
                        break;
                    case 'w':
                        if (highlightPos[0] > 0) highlightPos[0]--;
                        break;
                    case 's':
                        if (highlightPos[0] < SIZE - 1) highlightPos[0]++;
                        break;
                    case 32: {
                        int row = highlightPos[0];
                        int col = highlightPos[1];
                        if (board[row][col] == 0) {
                            board[row][col] = 1; // 플레이어의 돌
                            lastPlayerRow = row;
                            lastPlayerCol = col;
                            int winner = checkWin(board, row, col);
                            if (winner) {
                                printBoardWithHighlight(board, highlightPos, turn);
                                printf("플레이어가 승리했습니다!\n");
                                printf("다시 시작하려면 스페이스바를 누르세요.\n");
                                while (1) {
                                    if (_kbhit() && _getch() == 32) {
                                        resetGame(board, highlightPos, &turn);
                                        break;
                                    }
                                }
                                continue;
                            }
                            if (checkDraw(board)) {
                                printBoardWithHighlight(board, highlightPos, turn);
                                printf("무승부입니다!\n");
                                printf("다시 시작하려면 스페이스바를 누르세요.\n");
                                while (1) {
                                    if (_kbhit() && _getch() == 32) {
                                        resetGame(board, highlightPos, &turn);
                                        break;
                                    }
                                }
                                continue;
                            }
                            turn = 1; // AI의 턴
                        }
                        break;
                    }
                    }
                }
            }
        }
        else { // AI의 턴
            int row, col;
            aiTurn(board, &row, &col, aiFirstMove, lastPlayerRow, lastPlayerCol);
            aiFirstMove = 0; // 첫 수 이후 일반 로직
            board[row][col] = 2; // AI의 돌
            int winner = checkWin(board, row, col);
            if (winner) {
                printBoardWithHighlight(board, highlightPos, turn);
                printf("AI가 승리했습니다!\n");
                printf("다시 시작하려면 스페이스바를 누르세요.\n");
                while (1) {
                    if (_kbhit() && _getch() == 32) {
                        resetGame(board, highlightPos, &turn);
                        break;
                    }
                }
                continue;
            }
            if (checkDraw(board)) {
                printBoardWithHighlight(board, highlightPos, turn);
                printf("무승부입니다!\n");
                printf("다시 시작하려면 스페이스바를 누르세요.\n");
                while (1) {
                    if (_kbhit() && _getch() == 32) {
                        resetGame(board, highlightPos, &turn);
                        break;
                    }
                }
                continue;
            }
            turn = 0; // 플레이어의 턴
        }
    }

    return 0;
}