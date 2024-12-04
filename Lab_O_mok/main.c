#include "var.h"
#include "rules.c"
#include "screen.c"

void main() {
	printBoardWithHighlight(board, highlightPos, turn);

	while (1) {
        if (_kbhit()) { // Ű���� �Է� ����
            int key = _getch(); // Ű �Է� �ޱ�

            switch (key) {
            case 'a': // ���� �̵�
                if (highlightPos[1] > 0) highlightPos[1]--;
                break;
            case 'd': // ������ �̵�
                if (highlightPos[1] < SIZE - 1) highlightPos[1]++;
                break;
            case 'w': // ���� �̵�
                if (highlightPos[0] > 0) highlightPos[0]--;
                break;
            case 's': // �Ʒ��� �̵�
                if (highlightPos[0] < SIZE - 1) highlightPos[0]++;
                break;
            case 32: { // �����̽��� �Է�
                int row = highlightPos[0];
                int col = highlightPos[1];
                if (board[row][col] == 0) { // ��ĭ�� ��츸 ����
                    board[row][col] = (turn == 0) ? 1 : 2; // �����: 1, ������: 2
                    int winner = checkWin(board, row, col); // �¸� ���� Ȯ��
                    if (winner) {
                        printGameOverScreen(winner);
                        while (1) {
                            if (_kbhit() && _getch() == 32) { // �����̽��� �Է� �� �����
                                resetGame(board, highlightPos, &turn);
                                printBoardWithHighlight(board, highlightPos, turn);
                                break;
                            }
                        }
                        continue;
                    }

                    if (checkDraw(board)) { // ���º� Ȯ��
                        printGameOverScreen(0); // ���º� ó��
                        while (1) {
                            if (_kbhit() && _getch() == 32) { // �����̽��� �Է� �� �����
                                resetGame(board, highlightPos, &turn);
                                printBoardWithHighlight(board, highlightPos, turn);
                                break;
                            }
                        }
                        continue;
                    }

                    turn = 1 - turn; // �� ��ȯ
                }
                break;
            }
            case 27: // ESC Ű�� ����
                return 0;
            }
            printBoardWithHighlight(board, highlightPos, turn);
        }
	}
}