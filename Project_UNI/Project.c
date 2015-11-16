//
//  Project.c
//  151111
//
//  Created by 콜라맛홍삼 on 2015. 11. 14..
//  Copyright ? 2015년 콜라맛홍삼. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define true 1
#define T 1
#define false 0
#define F 0
#define bool int

#define BOARD_WIDTH 20        // 게임 영역의 가로(열) >= 20 : ━
#define BOARD_HEIGHT 20        // 게임 영역의 세로(행) >= 20 : ┃

#define BOARD_X 4 //보드 열 x좌표
#define BOARD_Y 2 //보드 행 y좌표

static int score = 0; //게임점수
static int level = 1; //게임레벨
static int speed = 500;
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };

// 키보드의 방향키와 스페이스에 대한 열거형 지정
// _getch()가 반환하는 값이
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

// 커서 숨기기 : true, T(보이기), false, F(숨기기)
void CursorVisible(bool blnCursorVisible)    // Console.CursorVisible = false;
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = blnCursorVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 현재 콘솔 내의 커서 위치를 설정
void SetCur(int cursorLeft, int cursorTop)    // Console.SetCursorPosition(posX, posY);
{
	int posX = cursorLeft;
	int posY = cursorTop;

	COORD pos = { posX, posY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 보드 만들기


// 게임판 그리기
void DrawField(void)
{
	int x, y;

	//위 보드 라인
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board 배열 중앙 1인식
		SetCur((BOARD_X)+x * 2, BOARD_Y);  //콘솔좌표
		printf("━");
	}

	//아래 보드 라인
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board 배열 중앙 1인식
		SetCur((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //콘솔좌표
		printf("━");
	}

	//왼쪽 보드 라인
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board 배열 왼쪽 1인식
		SetCur(BOARD_X, BOARD_Y + y);
		if (y == 0)
			printf("┏");
		else if (y == BOARD_HEIGHT)
			printf("┗");
		else
			printf("┃");
	}
	//오른쪽 보드 라인
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][BOARD_WIDTH + 1] = 1; //board 배열 오른쪽 1인식
		SetCur(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == 0)
			printf("┓");
		else if (y == BOARD_HEIGHT)
			printf("┛");
		else
			printf("┃");
	}

	//모서리값 값 변경
	board[20][0] = 1;
	board[20][11] = 1;

	puts(" ");
}

//게임 설명
void ConsoleInit()
{
	// 콘솔 초기화 및 시작 화면 구성 영역
	printf("C언어 콘솔 테트리스\n\n");
	printf(""
		"===================================        \n"
		"조작법:                                        \n"
		"[→]     커서를 오른쪽으로 이동              \n"
		"[←]     커서를 왼쪽으로 이동                \n"
		"[↑]     커서를 왼쪽으로 이동            \n"
		"[↓]     커서를 아래로 이동            \n"
		"[Space]  커서가 가리키는 블럭 선택                  \n"
		"                                            \n"
		"아무키나 누르면 시작됩니다.                    \n"
		"===================================           \n");
	_getch();
	system("cls");            // Console.Clear();
	CursorVisible(false);    // 커서 숨기기
	SetCur(0, 0); //보드표시 시작위치 설정
}

int main() {
	ConsoleInit();
	DrawField();
}