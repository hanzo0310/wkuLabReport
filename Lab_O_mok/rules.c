#include "var.h"

int checkWin(int board[SIZE][SIZE], int row, int col) {
    int directions[4][2] = {
        {0, 1},  // ����
        {1, 0},  // ����
        {1, 1},  // �밢�� (\)
        {1, -1}  // �밢�� (/)
    };

    int player = board[row][col]; // ���� ���� �÷��̾�
    if (player == 0) return 0;    // �� ĭ�̸� �¸� �Ұ�

    for (int d = 0; d < 4; d++) {
        int count = 1; // ���� ĭ ����

        // ���� ���� üũ
        for (int step = 1; step < 5; step++) {
            int newRow = row + step * directions[d][0];
            int newCol = col + step * directions[d][1];
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == player) {
                count++;
            }
            else {
                break;
            }
        }

        // �ݴ��� ���� üũ
        for (int step = 1; step < 5; step++) {
            int newRow = row - step * directions[d][0];
            int newCol = col - step * directions[d][1];
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == player) {
                count++;
            }
            else {
                break;
            }
        }

        if (count >= 5) return player; // �¸� ���� ����
    }

    return 0; // �¸� ���� ������
}

// ���º� Ȯ�� �Լ�
int checkDraw(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return 0; // �� ĭ�� ������ ���º� �ƴ�
        }
    }
    return 1; // ��� ĭ�� �� ������ ���º�
}

// ���� �ʱ�ȭ �Լ�
void resetGame(int board[SIZE][SIZE], int highlightPos[2], int* turn) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
    highlightPos[0] = 0;
    highlightPos[1] = 0;
    *turn = 0;
}
