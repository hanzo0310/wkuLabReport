#pragma once

#include "var.h"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ������ ��ǥ�� ���Ե� �ٵ��� ���
void GotoXY(int x, int y) {
    COORD pos;
    pos.X = 2 * x; // ���� ��ǥ�� 2��� Ȯ���Ͽ� ���
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ������ ��ǥ�� ���Ե� �ٵ��� ���
void printBoardWithHighlight(int board[SIZE][SIZE], int highlightPos[2], int turn) {
    system("cls"); // ȭ�� �ʱ�ȭ

    // �ٵ��� ���
    GotoXY(0, 0);
    printf("   ");
    for (char c = 'A'; c < 'A' + SIZE; c++) {
        printf("%c ", c); // �� ��ȣ�� ���ĺ� ���
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        GotoXY(0, i + 1);
        printf("%2d ", i + 1); // �� ��ȣ�� ���� ���
        for (int j = 0; j < SIZE; j++) {
            if (i == highlightPos[0] && j == highlightPos[1]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // �����
                if (board[i][j] == 1) {
                    printf("��");
                }
                else if (board[i][j] == 2) {
                    printf("��");
                }
                else {
                    printf("��");
                }
            }
            else {
                if (board[i][j] == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // �Ķ���
                    printf("��");
                }
                else if (board[i][j] == 2) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // ������
                    printf("��");
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // ���
                    printf("��");
                }
            }
        }
    }

    // �ȳ��� ��� ��ġ�� �̵�
    int infoX = SIZE + 3; // �ٵ��� �������� x ��ǥ (2�� Ȯ�� + ����)
    int infoY = 0; // �ٵ��� ���� y ��ǥ

    // �ȳ��� ���
    GotoXY(infoX, infoY);
    printf("���� ����\n\n");

    GotoXY(infoX, infoY + 2);
    printf("�Ķ��� : ����\n");

    GotoXY(infoX, infoY + 3);
    printf("������ : �İ�\n\n");

    GotoXY(infoX, infoY + 5);
    printf("���۹�:\n");

    GotoXY(infoX, infoY + 6);
    printf("  W / �� ����Ű - ���� �̵�\n");

    GotoXY(infoX, infoY + 7);
    printf("  A / �� ����Ű - ���� �̵�\n");

    GotoXY(infoX, infoY + 8);
    printf("  S / �Ʒ� ����Ű - �Ʒ��� �̵�\n");

    GotoXY(infoX, infoY + 9);
    printf("  D / ���� ����Ű - ������ �̵�\n");

    GotoXY(infoX, infoY + 10);
    printf("  Space - �� ����\n\n");

    // ���� �� ���
    GotoXY(infoX, infoY + 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), turn == 0 ? 9 : 12); // �Ķ��� �Ǵ� ������
    printf("%s���� ���Դϴ�!\n", turn == 0 ? "�Ķ�" : "����");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �⺻ ���� ����
}

// ���� ���� ȭ�� ���
void printGameOverScreen(int winner) {
    system("cls"); // ȭ�� �����

    setColor(winner == 1 ? 9 : 12); // ������ ����
    printf("\n\n\n\n\n");
    printf("         %s���� �¸��Ͽ����ϴ�!\n\n", winner == 1 ? "�Ķ�" : "����");
    printf("    -> �ٽ� �����Ϸ��� space-bar Ŭ��\n\n");
    setColor(7); // �⺻ ���� ����
}