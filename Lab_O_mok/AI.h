#pragma once
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

int findBestMove(int board[SIZE][SIZE], int* bestRow, int* bestCol, int player) {
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

                    if (count >= 4) { // �¸� �Ǵ� ��� ����
                        *bestRow = i;
                        *bestCol = j;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}


// AI�� ��: ������ ��ġ�� ����
void aiTurn(int board[SIZE][SIZE], int* row, int* col) {
    // 1. AI �¸� ���� ��ġ Ž��
    if (findBestMove(board, row, col, 2)) {
        return;
    }

    // 2. �÷��̾� ��� ��ġ Ž��
    if (findBestMove(board, row, col, 1)) {
        return;
    }

    // 3. ���Ƿ� �� ĭ ���� (�⺻ ���� ����)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
