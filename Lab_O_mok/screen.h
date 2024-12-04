#pragma once

#include "var.h"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ������ ��ǥ�� ���Ե� �ٵ��� ���
void printBoardWithHighlight(int board[SIZE][SIZE], int highlightPos[2], int turn, int mode) {
    system("cls"); // �ܼ� ȭ�� �����

    // ������ ���� ���
    printf("���� ����\n\n");
    printf("�Ķ��� : ����\n");
    printf("������ : �İ�\n\n");
    printf("���۹�:\n");
    printf("  W / �� ����Ű - ���� �̵�\n");
    printf("  A / �� ����Ű - ���� �̵�\n");
    printf("  S / �Ʒ� ����Ű - �Ʒ��� �̵�\n");
    printf("  D / ���� ����Ű - ������ �̵�\n");
    printf("  Space - �� ����\n\n");

    // ���� �� ǥ��
    setColor(turn == 0 ? 9 : 12); // �Ķ���: 9, ������: 12
    printf("%s���� ���Դϴ�!\n", turn == 0 ? "�Ķ�" : "����");
    setColor(7); // �⺻ ���� ����

    printf("\n   ");
    for (char c = 'A'; c < 'A' + SIZE; c++) {
        printf("%c ", c);
    }
    printf("\n");

    // �ٵ��� ���
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (i == highlightPos[0] && j == highlightPos[1]) { // ���õ� ��ǥ
                setColor(14); // �����
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
            else { // �Ϲ� ��ǥ
                if (board[i][j] == 1) {
                    setColor(9); // �Ķ���
                    printf("��");
                }
                else if (board[i][j] == 2) {
                    setColor(12); // ������
                    printf("��");
                }
                else {
                    setColor(15); // ���
                    printf("��");
                }
            }
        }
        printf("\n");
    }
    setColor(7); // �⺻ �ܼ� ���� ����
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