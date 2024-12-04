#pragma once

#include "var.h"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 강조된 좌표가 포함된 바둑판 출력
void GotoXY(int x, int y) {
    COORD pos;
    pos.X = 2 * x; // 가로 좌표는 2배로 확대하여 출력
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 강조된 좌표가 포함된 바둑판 출력
void printBoardWithHighlight(int board[SIZE][SIZE], int highlightPos[2], int turn) {
    system("cls"); // 화면 초기화

    // 바둑판 출력
    GotoXY(0, 0);
    printf("   ");
    for (char c = 'A'; c < 'A' + SIZE; c++) {
        printf("%c ", c); // 열 번호로 알파벳 출력
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        GotoXY(0, i + 1);
        printf("%2d ", i + 1); // 행 번호로 숫자 출력
        for (int j = 0; j < SIZE; j++) {
            if (i == highlightPos[0] && j == highlightPos[1]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // 노란색
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
            else {
                if (board[i][j] == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // 파란색
                    printf("●");
                }
                else if (board[i][j] == 2) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // 빨간색
                    printf("●");
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // 흰색
                    printf("■");
                }
            }
        }
    }

    // 안내문 출력 위치로 이동
    int infoX = SIZE + 3; // 바둑판 오른쪽의 x 좌표 (2배 확대 + 여백)
    int infoY = 0; // 바둑판 위쪽 y 좌표

    // 안내문 출력
    GotoXY(infoX, infoY);
    printf("오목 게임\n\n");

    GotoXY(infoX, infoY + 2);
    printf("파란색 : 선공\n");

    GotoXY(infoX, infoY + 3);
    printf("빨간색 : 후공\n\n");

    GotoXY(infoX, infoY + 5);
    printf("조작법:\n");

    GotoXY(infoX, infoY + 6);
    printf("  W / 윗 방향키 - 위로 이동\n");

    GotoXY(infoX, infoY + 7);
    printf("  A / 왼 방향키 - 왼쪽 이동\n");

    GotoXY(infoX, infoY + 8);
    printf("  S / 아랫 방향키 - 아래로 이동\n");

    GotoXY(infoX, infoY + 9);
    printf("  D / 오른 방향키 - 오른쪽 이동\n");

    GotoXY(infoX, infoY + 10);
    printf("  Space - 돌 놓기\n\n");

    // 현재 턴 출력
    GotoXY(infoX, infoY + 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), turn == 0 ? 9 : 12); // 파란색 또는 빨간색
    printf("%s색의 턴입니다!\n", turn == 0 ? "파란" : "빨간");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 기본 색상 복원
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