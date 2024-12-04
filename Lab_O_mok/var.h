#pragma once

#include <stdio.h>
#include <conio.h> // 키보드 입력 처리 (_getch())
#include <windows.h> 

#define SIZE 19

int board[SIZE][SIZE] = { 0 }; // 모든 요소를 0으로 초기화
int highlightPos[2] = { 0, 0 }; // {행, 열}을 저장하는 1차원 배열
int turn = 0; // 0: 블루턴, 1: 레드턴