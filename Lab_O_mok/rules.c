#include "var.h"

int checkWin(int board[SIZE][SIZE], int row, int col) {
    int directions[4][2] = {
        {0, 1},  // 가로
        {1, 0},  // 세로
        {1, 1},  // 대각선 (\)
        {1, -1}  // 대각선 (/)
    };

    int player = board[row][col]; // 현재 돌의 플레이어
    if (player == 0) return 0;    // 빈 칸이면 승리 불가

    for (int d = 0; d < 4; d++) {
        int count = 1; // 현재 칸 포함

        // 한쪽 방향 체크
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

        // 반대쪽 방향 체크
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

        if (count >= 5) return player; // 승리 조건 충족
    }

    return 0; // 승리 조건 미충족
}

// 무승부 확인 함수
int checkDraw(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return 0; // 빈 칸이 있으면 무승부 아님
        }
    }
    return 1; // 모든 칸이 차 있으면 무승부
}

// 게임 초기화 함수
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
