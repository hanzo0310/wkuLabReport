#pragma once

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 19

int board[SIZE][SIZE] = { 0 }; // 모든 요소를 0으로 초기화
int highlightPos[2] = { 0, 0 }; // {행, 열}을 저장하는 1차원 배열
int turn = 0; // 0: 블루턴, 1: 레드턴
int lastPlayerRow = -1, lastPlayerCol = -1;
int aiFirstMove = 1;