#include "var.h"
#include "rules.h"
#include "screen.h"
#include "AI.h"

int main() {
    int board[SIZE][SIZE] = { 0 }; // �ٵ��� �ʱ�ȭ
    int highlightPos[2] = { 0, 0 }; // Ŀ�� �ʱ� ��ġ
    int turn = 0; // 0: �÷��̾� 1, 1: AI
    int lastPlayerRow = -1, lastPlayerCol = -1; // �÷��̾ ���������� �� ��ġ
    int aiFirstMove = 1; // AI�� ù ��° �� ����

    srand((unsigned int)time(NULL)); // ���� �ʱ�ȭ

    while (1) {
        printBoardWithHighlight(board, highlightPos, turn);

        if (turn == 0) { // �÷��̾��� ��
            if (_kbhit()) {
                int key = _getch();

                if (key == 224) {
                    key = _getch();
                    switch (key) {
                    case 75: // ���� ����Ű
                        if (highlightPos[1] > 0) highlightPos[1]--;
                        break;
                    case 77: // ������ ����Ű
                        if (highlightPos[1] < SIZE - 1) highlightPos[1]++;
                        break;
                    case 72: // ���� ����Ű
                        if (highlightPos[0] > 0) highlightPos[0]--;
                        break;
                    case 80: // �Ʒ��� ����Ű
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
                            board[row][col] = 1; // �÷��̾��� ��
                            lastPlayerRow = row;
                            lastPlayerCol = col;
                            int winner = checkWin(board, row, col);
                            if (winner) {
                                printBoardWithHighlight(board, highlightPos, turn);
                                printf("�÷��̾ �¸��߽��ϴ�!\n");
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
                                printBoardWithHighlight(board, highlightPos, turn);
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
                            turn = 1; // AI�� ��
                        }
                        break;
                    }
                    }
                }
            }
        }
        else { // AI�� ��
            int row, col;
            aiTurn(board, &row, &col, aiFirstMove, lastPlayerRow, lastPlayerCol);
            aiFirstMove = 0; // ù �� ���� �Ϲ� ����
            board[row][col] = 2; // AI�� ��
            int winner = checkWin(board, row, col);
            if (winner) {
                printBoardWithHighlight(board, highlightPos, turn);
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
                printBoardWithHighlight(board, highlightPos, turn);
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
    }

    return 0;
}