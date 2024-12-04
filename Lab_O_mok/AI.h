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


