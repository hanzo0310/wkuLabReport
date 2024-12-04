#include "var.h"
#include "rules.c"
#include "screen.c"

void main() {
	printBoardWithHighlight(board, highlightPos, turn);

	while (1) {
        if (_kbhit()) { // 키보드 입력 감지
            int key = _getch(); // 키 입력 받기

            switch (key) {
            case 'a': // 왼쪽 이동
                if (highlightPos[1] > 0) highlightPos[1]--;
                break;
            case 'd': // 오른쪽 이동
                if (highlightPos[1] < SIZE - 1) highlightPos[1]++;
                break;
            case 'w': // 위로 이동
                if (highlightPos[0] > 0) highlightPos[0]--;
                break;
            case 's': // 아래로 이동
                if (highlightPos[0] < SIZE - 1) highlightPos[0]++;
                break;
            case 32: { // 스페이스바 입력
                int row = highlightPos[0];
                int col = highlightPos[1];
                if (board[row][col] == 0) { // 빈칸일 경우만 수정
                    board[row][col] = (turn == 0) ? 1 : 2; // 블루턴: 1, 레드턴: 2
                    int winner = checkWin(board, row, col); // 승리 조건 확인
                    if (winner) {
                        printGameOverScreen(winner);
                        while (1) {
                            if (_kbhit() && _getch() == 32) { // 스페이스바 입력 시 재시작
                                resetGame(board, highlightPos, &turn);
                                printBoardWithHighlight(board, highlightPos, turn);
                                break;
                            }
                        }
                        continue;
                    }

                    if (checkDraw(board)) { // 무승부 확인
                        printGameOverScreen(0); // 무승부 처리
                        while (1) {
                            if (_kbhit() && _getch() == 32) { // 스페이스바 입력 시 재시작
                                resetGame(board, highlightPos, &turn);
                                printBoardWithHighlight(board, highlightPos, turn);
                                break;
                            }
                        }
                        continue;
                    }

                    turn = 1 - turn; // 턴 전환
                }
                break;
            }
            case 27: // ESC 키로 종료
                return 0;
            }
            printBoardWithHighlight(board, highlightPos, turn);
        }
	}
}