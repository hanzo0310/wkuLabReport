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
        {0, 1},  // 가로
        {1, 0},  // 세로
        {1, 1},  // 대각선 (\)
        {1, -1}  // 대각선 (/)
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) { // 빈 칸만 확인
                for (int d = 0; d < 4; d++) {
                    int count = countStones(board, i, j, directions[d][0], directions[d][1], player) +
                        countStones(board, i, j, -directions[d][0], -directions[d][1], player);

                    if (count >= 4) { // 승리 또는 방어 가능
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


// AI의 턴: 최적의 위치를 선택
void aiTurn(int board[SIZE][SIZE], int* row, int* col) {
    // 1. AI 승리 가능 위치 탐색
    if (findBestMove(board, row, col, 2)) {
        return;
    }

    // 2. 플레이어 방어 위치 탐색
    if (findBestMove(board, row, col, 1)) {
        return;
    }

    // 3. 임의로 빈 칸 선택 (기본 전략 없음)
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
