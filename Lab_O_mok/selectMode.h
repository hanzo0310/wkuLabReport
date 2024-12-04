#include "var.h"

int selectMode() {
    int choice;
    do {
        system("cls");
        printf("오목 게임 모드를 선택하세요:\n");
        printf("1. AI와 플레이 (PvE)\n");
        printf("2. 플레이어 2명이서 플레이 (PvP)\n");
        printf("선택 (1/2): ");
        choice = _getch() - '0'; // 문자 입력을 숫자로 변환
    } while (choice != 1 && choice != 2); // 1과 2 이외의 입력을 반복
    return choice;
}