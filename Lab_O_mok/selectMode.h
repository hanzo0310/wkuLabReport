#include "var.h"

int selectMode() {
    int choice;
    do {
        system("cls");
        printf("���� ���� ��带 �����ϼ���:\n");
        printf("1. AI�� �÷��� (PvE)\n");
        printf("2. �÷��̾� 2���̼� �÷��� (PvP)\n");
        printf("���� (1/2): ");
        choice = _getch() - '0'; // ���� �Է��� ���ڷ� ��ȯ
    } while (choice != 1 && choice != 2); // 1�� 2 �̿��� �Է��� �ݺ�
    return choice;
}