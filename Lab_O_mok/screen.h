#pragma once

#include "var.h"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 강조된 좌표가 포함된 바둑판 출력
void printBoardWithHighlight(int board[SIZE][SIZE], int highlightPos[2], int turn, int mode) {
    system("cls"); // 콘솔 화면 지우기

    // 오목판 설명 출력
    printf("오목 게임\n\n");
    printf("파란색 : 선공\n");
    printf("빨간색 : 후공\n\n");
    printf("조작법:\n");
    printf("  W / 윗 방향키 - 위로 이동\n");
    printf("  A / 왼 방향키 - 왼쪽 이동\n");
    printf("  S / 아랫 방향키 - 아래로 이동\n");
    printf("  D / 오른 방향키 - 오른쪽 이동\n");
    printf("  Space - 돌 놓기\n\n");

    // 현재 턴 표시
    setColor(turn == 0 ? 9 : 12); // 파란색: 9, 빨간색: 12
    printf("%s색의 턴입니다!\n", turn == 0 ? "파란" : "빨간");
    setColor(7); // 기본 색상 복원

    printf("\n   ");
    for (char c = 'A'; c < 'A' + SIZE; c++) {
        printf("%c ", c);
    }
    printf("\n");

    // 바둑판 출력
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (i == highlightPos[0] && j == highlightPos[1]) { // 선택된 좌표
                setColor(14); // 노란색
                if (board[i][j] == 1) {
                    printf("●");
                }
                else if (board[i][j] == 2) {
                    printf("●");
                }
                else {
                    printf("■");
                }
            }
            else { // 일반 좌표
                if (board[i][j] == 1) {
                    setColor(9); // 파란색
                    printf("●");
                }
                else if (board[i][j] == 2) {
                    setColor(12); // 빨간색
                    printf("●");
                }
                else {
                    setColor(15); // 흰색
                    printf("■");
                }
            }
        }
        printf("\n");
    }
    setColor(7); // 기본 콘솔 색상 복원
}

// 게임 종료 화면 출력
void printGameOverScreen(int winner) {
    system("cls"); // 화면 지우기

    setColor(winner == 1 ? 9 : 12); // 승자의 색상
    printf("\n\n\n\n\n");
    printf("         %s색이 승리하였습니다!\n\n", winner == 1 ? "파란" : "빨간");
    printf("    -> 다시 시작하려면 space-bar 클릭\n\n");
    setColor(7); // 기본 색상 복원
}