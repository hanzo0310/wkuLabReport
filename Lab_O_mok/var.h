#pragma once

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 19

int board[SIZE][SIZE] = { 0 }; // ��� ��Ҹ� 0���� �ʱ�ȭ
int highlightPos[2] = { 0, 0 }; // {��, ��}�� �����ϴ� 1���� �迭
int turn = 0; // 0: �����, 1: ������
int lastPlayerRow = -1, lastPlayerCol = -1;
int aiFirstMove = 1;