#include "var.h"
#include "rules.h"
#include "screen.h"
#include "AI.h"
#include "selectMode.h"

int main() {

    srand((unsigned int)time(NULL)); // ���� �ʱ�ȭ
    int mode = selectMode(); // ���� ��� ����



    while (1) {
        printBoardWithHighlight(board, highlightPos, turn, mode);

        if (mode == 1 && turn == 1) { // AI�� ��
            int row, col;
            aiTurn(board, &row, &col, aiFirstMove, lastPlayerRow, lastPlayerCol);
            aiFirstMove = 0;
            board[row][col] = 2; // AI�� ��
            int winner = checkWin(board, row, col);
            if (winner) {
                printBoardWithHighlight(board, highlightPos, turn, mode);
                printf("AI�� �¸��߽��ϴ�!\n");
                printf("�ٽ� �����Ϸ��� �����̽��ٸ� ��������.\n");
                while (1) {
                    if (_kbhit() && _getch() == 32) {
                        resetGame(board, highlightPos, &turn);
                        break;
                    }
                }
                continue;
            }
            if (checkDraw(board)) {
                printBoardWithHighlight(board, highlightPos, turn, mode);
                printf("���º��Դϴ�!\n");
                printf("�ٽ� �����Ϸ��� �����̽��ٸ� ��������.\n");
                while (1) {
                    if (_kbhit() && _getch() == 32) {
                        resetGame(board, highlightPos, &turn);
                        break;
                    }
                }
                continue;
            }
            turn = 0; // �÷��̾��� ��
        }
        else { // �÷��̾��� ��
            if (_kbhit()) {
                int key = _getch();

                if (key == 224) {
                    key = _getch();
                    switch (key) {
                    case 75: // ����
                        if (highlightPos[1] > 0) highlightPos[1]--;
                        break;
                    case 77: // ������
                        if (highlightPos[1] < SIZE - 1) highlightPos[1]++;
                        break;
                    case 72: // ����
                        if (highlightPos[0] > 0) highlightPos[0]--;
                        break;
                    case 80: // �Ʒ���
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
                            board[row][col] = turn == 0 ? 1 : 2;
                            lastPlayerRow = row;
                            lastPlayerCol = col;
                            int winner = checkWin(board, row, col);
                            if (winner) {
                                printBoardWithHighlight(board, highlightPos, turn, mode);
                                printf("�÷��̾� %d�� �¸��߽��ϴ�!\n", turn == 0 ? 1 : 2);
                                printf("�ٽ� �����Ϸ��� �����̽��ٸ� ��������.\n");
                                while (1) {
                                    if (_kbhit() && _getch() == 32) {
                                        resetGame(board, highlightPos, &turn);
                                        break;
                                    }
                                }
                                continue;
                            }
                            if (checkDraw(board)) {
                                printBoardWithHighlight(board, highlightPos, turn, mode);
                                printf("���º��Դϴ�!\n");
                                printf("�ٽ� �����Ϸ��� �����̽��ٸ� ��������.\n");
                                while (1) {
                                    if (_kbhit() && _getch() == 32) {
                                        resetGame(board, highlightPos, &turn);
                                        break;
                                    }
                                }
                                continue;
                            }
                            turn = 1 - turn; // �� ��ȯ
                        }
                        break;
                    }
                    }
                }
            }
        }
    }
}