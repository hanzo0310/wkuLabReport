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

// 돌을 배치할 최적의 위치를 탐색
int findBestMove(int board[SIZE][SIZE], int* bestRow, int* bestCol, int player, int targetCount) {
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

                    if (count >= targetCount - 1) { // 목표 돌 개수 이상 충족
                        *bestRow = i;
                        *bestCol = j;
                        return 1; // 최적의 위치 발견
                    }
                }
            }
        }
    }
    return 0;
}

// AI의 턴: 우선순위에 따라 동작
void placeFirstMoveNearPlayer(int board[SIZE][SIZE], int playerRow, int playerCol, int* aiRow, int* aiCol) {
    int directions[4][2] = {
        {0, 1},  // 오른쪽
        {1, 0},  // 아래
        {0, -1}, // 왼쪽
        {-1, 0}  // 위
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

// AI의 턴
void aiTurn(int board[SIZE][SIZE], int* row, int* col, int isFirstMove, int lastPlayerRow, int lastPlayerCol) {
    if (isFirstMove && lastPlayerRow != -1 && lastPlayerCol != -1) {
        // AI의 첫 번째 수: 플레이어 주변에 돌을 둠
        placeFirstMoveNearPlayer(board, lastPlayerRow, lastPlayerCol, row, col);
        return;
    }

    // 기존 AI 로직: 우선순위에 따라 동작
    if (findBestMove(board, row, col, 1, 4)) { // 방어
        return;
    }

    if (findBestMove(board, row, col, 2, 4)) { // 공격
        return;
    }

    for (int i = 0; i < SIZE; i++) { // 근접 배치
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

    int minDist = SIZE * SIZE, bestR = -1, bestC = -1; // 최소 거리 배치
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

    for (int i = 0; i < SIZE; i++) { // 랜덤 배치
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}