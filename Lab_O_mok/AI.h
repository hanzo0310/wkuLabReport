#include "var.h"

int countStones(int board[SIZE][SIZE], int row, int col, int dRow, int dCol, int player) {
    int count = 0;

    for (int i = 1; i < 5; i++) {
        int newRow = row + i * dRow;
        int newCol = col + i * dCol;

        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == player) {
            count++;
        }
        else {
            break;
        }
    }
    return count;
}

// ���� ��ġ�� ������ ��ġ�� Ž��
int findBestMove(int board[SIZE][SIZE], int* bestRow, int* bestCol, int player, int targetCount) {
    int directions[4][2] = {
        {0, 1},  // ����
        {1, 0},  // ����
        {1, 1},  // �밢�� (\)
        {1, -1}  // �밢�� (/)
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) { // �� ĭ�� Ȯ��
                for (int d = 0; d < 4; d++) {
                    int count = countStones(board, i, j, directions[d][0], directions[d][1], player) +
                        countStones(board, i, j, -directions[d][0], -directions[d][1], player);

                    if (count >= targetCount - 1) { // ��ǥ �� ���� �̻� ����
                        *bestRow = i;
                        *bestCol = j;
                        return 1; // ������ ��ġ �߰�
                    }
                }
            }
        }
    }
    return 0;
}

// AI�� ��: �켱������ ���� ����
void placeFirstMoveNearPlayer(int board[SIZE][SIZE], int playerRow, int playerCol, int* aiRow, int* aiCol) {
    int directions[4][2] = {
        {0, 1},  // ������
        {1, 0},  // �Ʒ�
        {0, -1}, // ����
        {-1, 0}  // ��
    };

    for (int d = 0; d < 4; d++) {
        int newRow = playerRow + directions[d][0];
        int newCol = playerCol + directions[d][1];

        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == 0) {
            *aiRow = newRow;
            *aiCol = newCol;
            return;
        }
    }
}

// AI�� ��
void aiTurn(int board[SIZE][SIZE], int* row, int* col, int isFirstMove, int lastPlayerRow, int lastPlayerCol) {
    if (isFirstMove && lastPlayerRow != -1 && lastPlayerCol != -1) {
        // AI�� ù ��° ��: �÷��̾� �ֺ��� ���� ��
        placeFirstMoveNearPlayer(board, lastPlayerRow, lastPlayerCol, row, col);
        return;
    }

    // ���� AI ����: �켱������ ���� ����
    if (findBestMove(board, row, col, 1, 4)) { // ���
        return;
    }

    if (findBestMove(board, row, col, 2, 4)) { // ����
        return;
    }

    for (int i = 0; i < SIZE; i++) { // ���� ��ġ
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 2) {
                int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
                for (int d = 0; d < 4; d++) {
                    int newRow = i + directions[d][0];
                    int newCol = j + directions[d][1];
                    if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == 0) {
                        *row = newRow;
                        *col = newCol;
                        return;
                    }
                }
            }
        }
    }

    int minDist = SIZE * SIZE, bestR = -1, bestC = -1; // �ּ� �Ÿ� ��ġ
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                for (int r = 0; r < SIZE; r++) {
                    for (int c = 0; c < SIZE; c++) {
                        if (board[r][c] == 2) {
                            int dist = abs(r - i) + abs(c - j);
                            if (dist < minDist) {
                                minDist = dist;
                                bestR = i;
                                bestC = j;
                            }
                        }
                    }
                }
            }
        }
    }

    if (bestR != -1 && bestC != -1) {
        *row = bestR;
        *col = bestC;
        return;
    }

    for (int i = 0; i < SIZE; i++) { // ���� ��ġ
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}