#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
/*
cmd 속성-레아아웃 설정
화면 버퍼 크기 -- 너비(W): 120 높이(H): 9001   크기 조정 시 텍스트 출력 줄 바꿈 체크
창 크기 -- 너비(I): 120 높이(E): 30
*/
/*===========================================================================================*/
#define ESC 27
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define delay(n) Sleep(n)

/*===========================================================================================*/
enum {
	BLACK,
	D_BLUE,
	D_GREEN,
	D_SKYBLUE,
	D_RED,
	D_VIOLET,
	D_YELLOW,
	GRAY,
	D_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};
void setcolor(int backcolor, int fontcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor * 16 + fontcolor);
}
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void setcursortype(CURSOR_TYPE c);
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

/*===========================================================================================*/

int current_map = 0;
int map[3][25][45] =
{
	{
	1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,7 ,0 ,16,16,16,16,16,0 ,0 ,0 ,0 ,0 ,0 ,0 ,41,41,33,0 ,0 ,0 ,41,33,0 ,0 ,0 ,0 ,0 ,0 ,41,41,41,0 ,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,7 ,16,16,16,16,16,16,16,0 ,0 ,0 ,0 ,0 ,41,33,41,41,41,0 ,41,33,41,41,0 ,0 ,0 ,0 ,41,41,2 ,33,41,1 ,3 ,
	1 ,7 ,7 ,2 ,2 ,7 ,7 ,7 ,7 ,2 ,2 ,7 ,0 ,8 ,9 ,10,11,12,0 ,0 ,0 ,0 ,0 ,41,41,41,41,41,41,41,41,41,33,41,41,0 ,2 ,2 ,2 ,2 ,2 ,0 ,0 ,1 ,3 ,
	1 ,0 ,7 ,2 ,2 ,7 ,7 ,7 ,7 ,2 ,2 ,7 ,0 ,4 ,4 ,4 ,4 ,4 ,0 ,0 ,0 ,0 ,41,33,41,41,33,41,33,41,41,41,41,41,33,41,2 ,0, 0 ,41,0 ,0 ,0 ,1 ,3 ,
	1 ,0 ,7 ,2 ,2 ,7 ,7 ,7 ,7 ,2 ,2 ,7 ,0 ,4 ,4 ,19,4 ,4 ,0 ,0 ,0 ,33,41,41,41,2 ,2 ,41,41,41,33,41,41,33,41,41,41,41,33,41,41,0 ,0 ,1 ,3 ,
	1 ,0 ,7 ,2 ,2 ,7 ,7 ,7 ,7 ,2 ,2 ,7 ,7 ,7 ,2 ,2 ,2 ,7 ,0 ,0 ,0 ,0, 0 ,0 ,7 ,2 ,2 ,7 ,0 ,0 ,0 ,0 ,0 ,0 ,41,41,33,41,41,41,33,41,0 ,1 ,3 ,
	1 ,0 ,7 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,7 ,0 ,0 ,0 ,43,0 ,0 ,7 ,2 ,2 ,7 ,0 ,0 ,0 ,6 ,6 ,0 ,0 ,6 ,6 ,6 ,0 ,0 ,6 ,6 ,0 ,1 ,3 ,
	1 ,0 ,7 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,7 ,0 ,0 ,44,42,44,0 ,7 ,2 ,2 ,7 ,0 ,0 ,0 ,28,29,0 ,0 ,28,32,29,0 ,0 ,28,29,0 ,1 ,3 ,
	1 ,14,14,14,14,14,14,14,14,14,14,14,14,2 ,2 ,2 ,2 ,7 ,0 ,0 ,0 ,43,0 ,0 ,7 ,2 ,2 ,7 ,0 ,0 ,0 ,23,35,0 ,0 ,23,22,35,0 ,0 ,23,35,0 ,1 ,3 ,
	1 ,13,13,13,13,13,13,13,13,13,13,13,14,14,2 ,2 ,2 ,7 ,0 ,0 ,15,15,15,0 ,7 ,2 ,2 ,7 ,0 ,0 ,0 ,23,22,32,36,37,38,39,40,32,22,35,0 ,1 ,3 ,
	1 ,13,13,13,13,13,13,25,25,13,13,13,13,14,14,2 ,2 ,7 ,0 ,0 ,15,15,15,0 ,7 ,2 ,2 ,7 ,0 ,0 ,0 ,23,22,22,22,22,22,22,22,22,22,35,0 ,1 ,3 ,
	1 ,13,13,13,13,13,25,25,26,27,13,13,13,13,14,2 ,2 ,7 ,0 ,0 ,15,1 ,15,0 ,7 ,2 ,2 ,7 ,0 ,0 ,0 ,31,34,34,34,34,24,34,34,34,34,30,0 ,1 ,3 ,
	1 ,13,13,13,13,13,25,25,13,13,25,25,13,13,14,2 ,2 ,7 ,0 ,0 ,15,15,15,0 ,7 ,2 ,2 ,7 ,0 ,0 ,0 ,0 ,0 ,45,45,2 ,2 ,2 ,45,45,0 ,0 ,0 ,1 ,3 ,
	1 ,13,13,13,13,13,25,25,13,25,25,26,27,13,14,2 ,2 ,7 ,7 ,7 ,7 ,2 ,7 ,7 ,7 ,2 ,2 ,7 ,1 ,1 ,1 ,1 ,1 ,45,45,2 ,2 ,2 ,45,45,0 ,0 ,0 ,1 ,3 ,
	1 ,13,13,13,25,25,13,13,13,25,25,13,13,13,14,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,45,0 ,0 ,0 ,1 ,3 ,
	1 ,13,13,25,25,26,27,13,13,25,25,13,13,13,14,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,45,0 ,0 ,0 ,1 ,3 ,
	1 ,13,13,25,25,13,13,13,13,13,13,13,13,13,13,14,14,14,14,2 ,2 ,2 ,7 ,7 ,7 ,7 ,7 ,7 ,1 ,1 ,1 ,1 ,1 ,45,45,45,45,45,45,45,0 ,0 ,0 ,1, 3 ,
	1 ,13,13,25,25,13,13,13,13,13,13,13,13,13,13,13,13,13,14,2 ,2 ,2 ,7 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,45,45,45,45,45,45,45,0 ,0 ,0 ,1 ,3 ,
	1 ,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,14,2 ,5 ,2 ,7 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,3 ,
	1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,
	},


	{
		1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,
		1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,33,46,33,46,33,46,33,46,33,46,2 ,21,2 ,33,2 ,2 ,2 ,46,1 ,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,46,33,46,33,46,33,46,33,46,33,2 ,2 ,2 ,46,2 ,2 ,2 ,33,1 ,45,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,33,46,33,46,33,46,33,46,33,46,2 ,2 ,2 ,33,2 ,2 ,2 ,46,1 ,45,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,33,46,33,46,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,33,1 ,45,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,33,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,46,1 ,45,2 ,2 ,2 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,46,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,33,1 ,45,2 ,2 ,2 ,1 ,45,45,45,45,45,45,1 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,33,2 ,2 ,2 ,46,33,46,33,46,33,46,33,46,33,2 ,2 ,2 ,2 ,2 ,2 ,2 ,46,1 ,45,2 ,2 ,2 ,1 ,45,45,45,45,45,45,1 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,46,2 ,2 ,2 ,33,46,2 ,2 ,2 ,2 ,2 ,2 ,2 ,46,2 ,2 ,2 ,33,46,33,46,33,1 ,45,2 ,2 ,2 ,1 ,45,45,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,33,2 ,2 ,2 ,46,33,2 ,2 ,2 ,2 ,2 ,2 ,2 ,33,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,1 ,45,45,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,46,2 ,2 ,2 ,33,46,2 ,2 ,2 ,2 ,2 ,2 ,2 ,46,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,1 ,45,45,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,33,2 ,2 ,2 ,46,33,2 ,2 ,2 ,33,2 ,2 ,2 ,33,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,1 ,45,45,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,33,46,2 ,2 ,2 ,46,2 ,2 ,2 ,46,2 ,2 ,2 ,46,33,46,33,33,46,45,2 ,2 ,2 ,1 ,45,45,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,46,33,2 ,2 ,2 ,33,2 ,2 ,2 ,33,2 ,2 ,2 ,33,1 ,1 ,1 ,1 ,1 ,45,2 ,2 ,2 ,1 ,45,45,45,45,45,45,1 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,33,46,2 ,2 ,2 ,46,2 ,2 ,2 ,46,2 ,2 ,2 ,46,1 ,45,45,45,45,45,2 ,2 ,2 ,1 ,45,45,45,45,45,45,1 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,46,33,46,33,46,33,46,33,46,33,2 ,2 ,2 ,33,2 ,2 ,2 ,33,1 ,1 ,1 ,1 ,1 ,45,2 ,2 ,2 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,46,2 ,2 ,2 ,46,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,33,2 ,2 ,2 ,33,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1, 3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,46,2 ,2 ,2 ,46,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,45,1 ,3 ,
	1 ,46,33,46,33,46,33,46,33,46,46,33,46,33,46,33,46,33,46,33,46,33,1 ,1 ,1 ,1 ,1 ,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,1 ,3 ,
	1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,
	},


	{
		1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,
		1 ,2 ,2 ,2 ,2 ,2 ,2 ,58,60,59,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2, 2, 2, 2, 2, 2, 2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,60,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2, 64,64,64,64,64,64,2 ,64,64,64,64,64,64,2 ,2 ,2 ,1 ,3 ,
	1 ,2 ,58,57,57,57,57,57,51,57,57,57,57,57,59,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,0 ,0 ,64,0 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,52,49,49,49,49,49,49,49,52,0 ,1 ,1 ,1 ,1 ,1 ,2 ,1 ,1 ,1 ,1 ,1 ,0 ,64,0 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,52,51,0 ,0 ,2 ,0 ,0 ,51,52,0 ,1 ,13,13,13,1 ,2 ,1 ,13,13,13,1 ,0 ,64,0 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,52,51,0 ,0 ,2 ,0 ,0 ,51,52,0 ,1 ,13,1 ,1 ,1 ,2 ,1 ,1 ,1 ,13,1 ,0 ,64,0 ,0 ,0 ,0 ,0 ,62,2 ,62,0 ,0 ,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,52,51,0 ,0 ,2 ,0 ,0 ,51,52,0 ,1 ,13,1 ,45,1 ,2 ,1 ,45,1 ,13,1 ,0 ,64,0 ,0 ,0 ,0 ,62,2 ,2 ,2 ,62,0 ,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,52,51,0 ,2 ,2 ,2 ,0 ,51,52,0 ,1 ,1 ,1 ,1 ,1 ,2 ,1 ,1 ,1 ,1 ,1 ,0 ,64,0 ,0 ,0 ,62,2 ,2 ,2 ,2 ,2 ,62,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,53,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,63,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,52,51,0 ,2 ,2 ,2 ,0 ,51,52,0 ,1 ,1 ,1 ,1 ,1 ,2 ,1 ,1 ,1 ,1 ,1 ,0 ,64,0 ,0 ,0 ,62,2 ,2 ,2 ,2 ,2 ,62,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,52,51,0 ,0 ,2 ,0 ,0 ,51,52,0 ,1 ,13,1 ,45,1 ,2 ,1 ,45,1 ,13,1 ,0 ,64,0 ,0 ,0 ,0 ,62,2 ,2 ,2 ,62,0 ,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,52,51,0 ,0 ,2 ,0 ,0 ,51,52,0 ,1 ,13,1 ,1 ,1 ,2 ,1 ,1 ,1 ,13,1 ,0 ,64,0 ,0 ,0 ,0 ,0 ,62,2 ,62,0 ,0 ,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,50,51,0 ,0 ,2 ,0 ,0 ,51,54,0 ,1 ,13,13,13,1 ,2 ,1 ,13,13,13,1 ,0 ,64,0 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,0 ,0 ,64,2 ,2 ,1 ,3 ,
	1 ,2, 2 ,2 ,2 ,50,51,0 ,2 ,0 ,51,54,0 ,0 ,1 ,1 ,1 ,1 ,1 ,2 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,64,64,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,64,64,2 ,2 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,50,51,2 ,51,54,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,64,64,0 ,0 ,0 ,2 ,0 ,0 ,0 ,64,64,2 ,2 ,2 ,2 ,1 ,3 ,
	1 ,2 ,47,47,47,2 ,2 ,50,55,54,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,64,64,64,0 ,2 ,0 ,64,64,64,2 ,7 ,7 ,7 ,2 ,1 ,3 ,
	1 ,2 ,47,1 ,47,2 ,2 ,2 ,56,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,64,64,2 ,64,64,2 ,2 ,2 ,7 ,1 ,7 ,2 ,1 ,3 ,
	1 ,2 ,47,47,47,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,7 ,7 ,7 ,2 ,1 ,3 ,
	1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,20,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,1 ,3 ,
	1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,3 ,
	}

};
char a, input;
char *skill[3], *username;
int i, j;
int turn = 1, sel, com_level, com_sel1, com_sel2;
int user_hp, user_atk, user_mp = 0, user_crit, user_critper, user_dodge, user_dodgeper;
int com_hp, com_atk, com_mp = 0, com_crit, com_dodge;
int user_dg_turn = 0, guard = 1, guard_turn = 0, user_cri_turn = 0, nurf_turn = 0;
int com_dg_turn = 0, com_cri_turn = 0;
int damage, com_damage;
char character[4] = "옷";
int cx = 2, cy = 1;
/*===========================================================================================*/
void printmap(); //맵출력
void printmap() {
	int i, j;
	for (i = 0; i < 25; i++) {
		for (j = 0; j < 45; j++) {
			switch (map[current_map][i][j]) {
			case 0:
				printf("  ");
				break;
			case 1:
				printf("■");
				break;
			case 2:
				setcolor(BLACK, D_YELLOW); printf("▒"); setcolor(BLACK, GRAY);
				break;
			case 3:
				printf("\n");
				break;
			case 4:
				setcolor(D_BLUE, YELLOW); printf("〓"); setcolor(BLACK, GRAY);
				break;
			case 5:
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY);//마을->사냥터 포탈
				break;
			case 6:
				setcolor(BLACK, RED);  printf("♨");  setcolor(BLACK, GRAY);
				break;
			case 7:
				setcolor(BLACK, GREEN);  printf("♣");  setcolor(BLACK, GRAY);
				break;
			case 8:
				setcolor(D_BLUE, YELLOW); printf(" S"); setcolor(BLACK, GRAY);
				break;
			case 9:
				setcolor(D_BLUE, YELLOW); printf(" T"); setcolor(BLACK, GRAY);
				break;
			case 10:
				setcolor(D_BLUE, YELLOW); printf(" O"); setcolor(BLACK, GRAY);
				break;
			case 11:
				setcolor(D_BLUE, YELLOW); printf(" R"); setcolor(BLACK, GRAY);
				break;
			case 12:
				setcolor(D_BLUE, YELLOW); printf(" E"); setcolor(BLACK, GRAY);
				break;
			case 13:
				setcolor(BLUE, SKYBLUE); printf("~~"); setcolor(BLACK, GRAY);
				break;
			case 14:
				setcolor(BLACK, WHITE); printf("●"); setcolor(BLACK, GRAY);
				break;
			case 15:
				setcolor(YELLOW, D_GREEN); printf("▨"); setcolor(BLACK, GRAY);
				break;
			case 16:
				setcolor(BLACK, RED); printf("▲"); setcolor(BLACK, GRAY);
				break;
			case 17:
				setcolor(SKYBLUE, YELLOW); printf("┼"); setcolor(BLACK, GRAY);
				break;
			case 18:
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY);//마을->결투장
				break;
			case 19:
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY);//마을->상점
				break;
			case 20:
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY); //상점->마을
				break;
			case 21:
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY); //사냥터->마을
				break;
			case 22:
				setcolor(GRAY, BLACK); printf("┼"); setcolor(BLACK, GRAY);
				break;
			case 23:
				setcolor(GRAY, BLACK); printf("├"); setcolor(BLACK, GRAY);
				break;
			case 24:
				setcolor(D_BLUE, BLACK); printf("▥"); setcolor(BLACK, GRAY);
				break;
			case 25:
				setcolor(D_GREEN, BLACK); printf("〓"); setcolor(BLACK, GRAY);
				break;
			case 26:
				setcolor(D_GREEN, BLACK); printf("으"); setcolor(BLACK, GRAY);
				break;
			case 27:
				setcolor(D_GREEN, BLACK); printf("'<"); setcolor(BLACK, GRAY);
				break;
			case 28:
				setcolor(GRAY, BLACK); printf("┌"); setcolor(BLACK, GRAY);
				break;
			case 29:
				setcolor(GRAY, BLACK); printf("┐"); setcolor(BLACK, GRAY);
				break;
			case 30:
				setcolor(GRAY, BLACK); printf("┘"); setcolor(BLACK, GRAY);
				break;
			case 31:
				setcolor(GRAY, BLACK); printf("└"); setcolor(BLACK, GRAY);
				break;
			case 32:
				setcolor(GRAY, BLACK); printf("┬"); setcolor(BLACK, GRAY);
				break;
			case 33:
				setcolor(D_GREEN, GREEN);  printf("♠");  setcolor(BLACK, GRAY);
				break;
			case 34:
				setcolor(GRAY, BLACK); printf("┴"); setcolor(BLACK, GRAY);
				break;
			case 35:
				setcolor(GRAY, BLACK); printf("┤"); setcolor(BLACK, GRAY);
				break;
			case 36:
				setcolor(GRAY, RED); printf("CO"); setcolor(BLACK, GRAY);
				break;
			case 37:
				setcolor(GRAY, RED); printf("LO"); setcolor(BLACK, GRAY);
				break;
			case 38:
				setcolor(GRAY, RED); printf("SS"); setcolor(BLACK, GRAY);
				break;
			case 39:
				setcolor(GRAY, RED); printf("EU"); setcolor(BLACK, GRAY);
				break;
			case 40:
				setcolor(GRAY, RED); printf("M "); setcolor(BLACK, GRAY);
				break;
			case 41:
				setcolor(D_GREEN, GREEN); printf(".."); setcolor(BLACK, GRAY);
				break;
			case 42:
				setcolor(WHITE, BLACK); printf("┼"); setcolor(BLACK, GRAY);
				break;
			case 43:
				setcolor(WHITE, BLACK); printf("│"); setcolor(BLACK, GRAY);
				break;
			case 44:
				setcolor(WHITE, BLACK); printf("─"); setcolor(BLACK, GRAY);
				break;
			case 45:
				setcolor(RED, WHITE);  printf("~~");  setcolor(BLACK, GRAY);
				break;
			case 46:
				setcolor(D_GREEN, GREEN);  printf("♣");  setcolor(BLACK, GRAY);
				break;
			case 47:
				setcolor(BLACK, GREEN);  printf("♠");  setcolor(BLACK, GRAY);
				break;
			case 48:
				setcolor(RED, YELLOW);  printf("♨");  setcolor(BLACK, GRAY);
				break;
			case 49:
				setcolor(BLACK, GRAY);  printf("--");  setcolor(BLACK, GRAY);
				break;
			case 50:
				setcolor(GRAY, BLACK);  printf("▼");  setcolor(BLACK, GRAY);
				break;
			case 51:
				setcolor(BLACK, GRAY);  printf("<>");  setcolor(BLACK, GRAY);
				break;
			case 52:
				setcolor(GRAY, BLACK);  printf("■");  setcolor(BLACK, GRAY);
				break;
			case 53:
				setcolor(BLACK, GRAY);  printf("◈");  setcolor(BLACK, GRAY);
				break;
			case 54:
				setcolor(GRAY, BLACK);  printf("▼");  setcolor(BLACK, GRAY);
				break;
			case 55:
				setcolor(GRAY, BLACK);  printf("■");  setcolor(BLACK, GRAY);
				break;
			case 56:
				setcolor(GRAY, BLACK);  printf("▼");  setcolor(BLACK, GRAY);
				break;
			case 57:
				setcolor(GRAY, BLACK);  printf("■");  setcolor(BLACK, GRAY);
				break;
			case 58:
				setcolor(BLACK, GRAY);  printf("≪");  setcolor(BLACK, GRAY);
				break;
			case 59:
				setcolor(BLACK, GRAY);  printf("≫");  setcolor(BLACK, GRAY);
				break;
			case 60:
				setcolor(BLACK, GRAY);  printf("§");  setcolor(BLACK, GRAY);
				break;
			case 61:
				setcolor(GRAY, BLACK);  printf("※");  setcolor(BLACK, GRAY);
				break;
			case 62:
				setcolor(GRAY, BLACK);  printf("◆");  setcolor(BLACK, GRAY);
				break;
			case 63:
				setcolor(GRAY, BLACK);  printf("●");  setcolor(BLACK, GRAY);
				break;
			case 64:
				setcolor(GRAY, BLACK);  printf("■");  setcolor(BLACK, GRAY);
				break;
			}
		}

	}

}

void status();   //플레이어 능력치
void status() {
	gotoxy(0, 25);
	printf("┏상태창━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃체력 :%6d     공격력 :%4d     치명타율 :%3d%%    회피율 :%3d%%      ┃\n", user_hp, user_atk, user_critper, user_dodgeper);
	printf("┃직업 :%6s       레벨 :           경험치 :        소지금 :          ┃\n", username);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

}

void startgame();   //게임 시작부분
void startgame() {
	printf("                                  .-.\n");
	printf("                                 {{@}}\n");
	printf("                 <>               8@8\n");
	printf("               .::::.             888\n");
	printf("           @\\\\/\\W\/\\/\\W\//@         8@8\n");
	printf("            \\\\/^\\/\\/^\\//     _    )8(    _\n");
	printf("             \\_O_<>_O_/     (@)__/8@8\\__(@)\n");
	printf("        ____________________ `~"" -= ) :(= -""~`\n");
	printf("       |<><><>  |  |  <><><>|     |.|\n");
	printf("       |<>      |  |      <>|     |S|\n");
	printf("       |<>      |  |      <>|     |'|\n");
	printf("       |<>   .--------.   <>|     |.|\n");
	printf("       |     |   ()   |     |     |P|\n");
	printf("       |_____| (O\\/O) |_____|     |'|\n");
	printf("       |     \\   /\\   /     |     |.|\n");
	printf("       |------\\  \\/  /------|     |U|\n");
	printf("       |       '.__.'       |     |'|\n");
	printf("       |        |  |        |     |.|\n");
	printf("       :        |  |        :     |N|\n");
	printf("        \\<>     |  |     <>/      |'|\n");
	printf("         \\<>    |  |    <>/       |.|\n");
	printf("          \\<>   |  |   <>/        |K|\n");
	printf("           `\\<> |  | <>/'         |'|\n");
	printf("             `-.|  |.-`           \\ /\n");
	printf("                '--'               ^\n");

	printf("              시작(enter)\n");


	getchar();



	system("cls");

	printf("===============================\n");
	printf("         캐릭터 선택\n");
	printf("===============================\n\n");


	printf("1.전사            2.암살자          3.성기사\n");
	printf("HP  : 1000        HP  : 700         HP  : 1200\n");
	printf("ATK : 75          ATK : 90          ATK : 50\n");
	printf("Cri : 10%%         Cri : 20%%         Cri : 5%%\n");
	printf("DG  : 10%%         DG  : 5%%          DG  : 20%%\n");
	printf("선택 : ");
	scanf_s("%d", &sel);

	switch (sel)
	{
	case 1:
		printf("『전사』를 고르셨습니다.\n");
		printf("공격: 기본공격력의 데미지를주며 마나 1을 얻습니다.\n");
		printf("방어: 다음턴까지 회피율이 50%%로 고정되며 마나 1을 얻고 턴을 넘깁니다.\n");;
		printf("스킬1: 강타(100의 피해를 입힌다.)\n");
		printf("스킬2: 집중(3턴동안 치명타확률 50%%)\n");
		printf("스킬3: 결정타(400의 피해를 입니다.)\n");
		printf("(enter)");
		username = "전사";
		user_hp = 1000;
		user_atk = 75;
		user_critper = 10;
		user_crit = rand() % 10;
		user_dodgeper = 10;
		user_dodge = rand() % 10;
		skill[0] = "강타";
		skill[1] = "집중";
		skill[2] = "결정타";
		break;
	case 2:
		printf("『암살자』를 고르셨습니다.\n");
		printf("공격: 기본공격력의 데미지를주며 마나 1을 얻습니다.\n");
		printf("방어: 다음턴까지 회피율이 50%%로 고정되며 마나 1을 얻고 턴을 넘깁니다.\n");
		printf("스킬1: 더블스탭(2회 공격)\n");
		printf("스킬2: 흡혈(공격력 3배의 피해를 주고, 입힌 피해의 50%% 회복)\n");
		printf("스킬3: 암살(상대 현재 체력의 50%%만큼 피해를 준다.[회피불가])\n");
		printf("(enter)");
		username = "암살자";
		user_hp = 700;
		user_atk = 90;
		user_critper = 20;
		user_crit = rand() % 5;
		user_dodgeper = 5;
		user_dodge = rand() % 20;
		skill[0] = "더블스탭";
		skill[1] = "흡혈";
		skill[2] = "암살";
		break;
	case 3:
		printf("『성기사』를 고르셨습니다.\n");
		printf("공격: 기본공격력의 데미지를주며 마나 1을 얻습니다.\n");
		printf("방어: 다음턴까지 회피율이 50%%로 고정되며 마나 1을 얻고 턴을 넘깁니다.\n");
		printf("스킬1: 반격 (30%%확률로 상대의 공격을 반사)\n");
		printf("스킬2: 무력화(4턴간 상대의 공격력을 반절 낮춤)\n");
		printf("스킬3: 수혈(최대 체력의 30%% 체력회복)\n");
		printf("(enter)");
		username = "성기사";
		user_hp = 1200;
		user_atk = 50;
		user_critper = 5;
		user_crit = rand() % 20;
		user_dodgeper = 20;
		user_dodge = rand() % 5;
		skill[0] = "반격";
		skill[1] = "무력화";
		skill[2] = "수혈";
		break;


	}
	scanf("%c", &a);
	while (getchar() != '\n');
	system("cls");
}

void mapmove();    //맵 동작
void mapmove() {

	switch (input) {
	case LEFT:
		if (map[current_map][cy][cx / 2 - 1] == 0 || map[current_map][cy][cx / 2 - 1] == 2 || map[current_map][cy][cx / 2 - 1] == 5 || map[current_map][cy][cx / 2 - 1] == 18 || map[current_map][cy][cx / 2 - 1] == 19 || map[current_map][cy][cx / 2 - 1] == 20 || map[current_map][cy][cx / 2 - 1] == 21) {
			gotoxy(cx, cy);
			if (map[current_map][cy][cx / 2] == 0) {
				printf("  ");
			}
			if (map[current_map][cy][cx / 2] == 2) {
				setcolor(BLACK, D_YELLOW); printf("▒"); setcolor(BLACK, GRAY);
			}
			if (map[current_map][cy][cx / 2] == 5 || map[current_map][cy][cx / 2] == 18 || map[current_map][cy][cx / 2] == 19 || map[current_map][cy][cx / 2] == 20 || map[current_map][cy][cx / 2] == 21) {
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY);
			}
			gotoxy(cx - 2, cy);
			cx -= 2;
			printf("%s", character);
		}
		break;
	case RIGHT:
		if (map[current_map][cy][cx / 2 + 1] == 0 || map[current_map][cy][cx / 2 + 1] == 2 || map[current_map][cy][cx / 2 + 1] == 5 || map[current_map][cy][cx / 2 + 1] == 18 || map[current_map][cy][cx / 2 + 1] == 19 || map[current_map][cy][cx / 2 + 1] == 20 || map[current_map][cy][cx / 2 + 1] == 21) {
			gotoxy(cx, cy);
			if (map[current_map][cy][cx / 2] == 0) {
				printf("  ");
			}
			if (map[current_map][cy][cx / 2] == 2) {
				setcolor(BLACK, D_YELLOW); printf("▒"); setcolor(BLACK, GRAY);
			}
			if (map[current_map][cy][cx / 2] == 5 || map[current_map][cy][cx / 2] == 18 || map[current_map][cy][cx / 2] == 19 || map[current_map][cy][cx / 2] == 20 || map[current_map][cy][cx / 2] == 21) {
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY);
			}
			gotoxy(cx + 2, cy);
			cx += 2;
			printf("%s", character);

		}
		break;
	case UP:
		if (map[current_map][cy - 1][cx / 2] == 0 || map[current_map][cy - 1][cx / 2] == 2 || map[current_map][cy - 1][cx / 2] == 5 || map[current_map][cy - 1][cx / 2] == 18 || map[current_map][cy - 1][cx / 2] == 19 || map[current_map][cy - 1][cx / 2] == 20 || map[current_map][cy - 1][cx / 2] == 21) {
			gotoxy(cx, cy);
			if (map[current_map][cy][cx / 2] == 0) {
				printf("  ");
			}
			if (map[current_map][cy][cx / 2] == 2) {
				setcolor(BLACK, D_YELLOW); printf("▒"); setcolor(BLACK, GRAY);
			}
			if (map[current_map][cy][cx / 2] == 5 || map[current_map][cy][cx / 2] == 18 || map[current_map][cy][cx / 2] == 19 || map[current_map][cy][cx / 2] == 20 || map[current_map][cy][cx / 2] == 21) {
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY);
			}
			gotoxy(cx, cy - 1);
			cy -= 1;
			printf("%s", character);

		}
		break;
	case DOWN:
		if (map[current_map][cy + 1][cx / 2] == 0 || map[current_map][cy + 1][cx / 2] == 2 || map[current_map][cy + 1][cx / 2] == 5 || map[current_map][cy + 1][cx / 2] == 18 || map[current_map][cy + 1][cx / 2] == 19 || map[current_map][cy + 1][cx / 2] == 20 || map[current_map][cy + 1][cx / 2] == 21) {
			gotoxy(cx, cy);
			if (map[current_map][cy][cx / 2] == 0) {
				printf("  ");
			}
			if (map[current_map][cy][cx / 2] == 2) {
				setcolor(BLACK, D_YELLOW); printf("▒"); setcolor(BLACK, GRAY);
			}
			if (map[current_map][cy][cx / 2] == 5 || map[current_map][cy][cx / 2] == 18 || map[current_map][cy][cx / 2] == 19 || map[current_map][cy][cx / 2] == 20 || map[current_map][cy][cx / 2] == 21) {
				setcolor(BLACK, SKYBLUE); printf("▣"); setcolor(BLACK, GRAY);
			}
			gotoxy(cx, cy + 1);
			cy += 1;
			printf("%s", character);

		}
		break;
	}

	if (map[current_map][cy][cx / 2] == 5) {
		input = _getch();

		if (input == 'a') {
			system("cls");
			current_map = 1;
			printmap();
			status();
			cx = 40;
			cy = 1;
			gotoxy(cx, cy);
			printf("%s", character);

		}
	}

	if (map[current_map][cy][cx / 2] == 19) {
		input = _getch();

		if (input == 'a') {
			system("cls");
			current_map = 2;
			printmap();
			status();
			cx = 40;
			cy = 19;
			gotoxy(cx, cy);
			printf("%s", character);

		}
	}
	/*if (map[current_map][cy][cx / 2] == 18) {
	input = _getch();

	if (input == 'a') {
	system("cls");
	current_map = 2;
	printmap();
	cx = 40;
	cy = 1;
	gotoxy(cx, cy);
	printf("%s", character);

	}
	}*/
	if (map[current_map][cy][cx / 2] == 20) {
		input = _getch();

		if (input == 'a') {
			system("cls");
			current_map = 0;
			printmap();
			status();
			cx = 30;
			cy = 6;
			gotoxy(cx, cy);
			printf("%s", character);

		}
	}
	if (map[current_map][cy][cx / 2] == 21) {
		input = _getch();

		if (input == 'a') {
			system("cls");
			current_map = 0;
			printmap();
			status();
			cx = 40;
			cy = 18;
			gotoxy(cx, cy);
			printf("%s", character);

		}
	}

}
/*===========================================================================================*/




int main()
{
	srand(time(0));
	setcursortype(NOCURSOR);
	startgame();
	printmap();
	status();
	while (1) {

		gotoxy(cx, cy);
		printf("%s", character);
		while (1) {
			input = _getch();
			mapmove();
		}



	}


	/*printf("┌──────────────┐\n");
	printf("│난이도를 설정해주세요.(1~5) │\n");
	printf("└──────────────┘\n");
	printf("");
	scanf("%d", &com_level);
	switch (com_level) {
	case 1:
	com_hp = 6000;
	com_atk = 40;
	com_crit = rand() % 10;
	com_dodge = rand() % 10;
	break;
	case 2:
	com_hp = 800;
	com_atk = 50;
	com_crit = rand() % 7;
	com_dodge = rand() % 10;
	break;
	case 3:
	com_hp = 1000;
	com_atk = 60;
	com_crit = rand() % 10;
	com_dodge = rand() % 15;
	break;

	case 4:
	com_hp = 1200;
	com_atk = 70;
	com_crit = rand() % 12;
	com_dodge = rand() % 20;
	break;

	case 5:
	com_hp = 1400;
	com_atk = 80;
	com_crit = rand() % 15;
	com_dodge = rand() % 25;
	break;


	}

	system("cls");
	*/

	while (user_hp > 0 && com_hp > 0) {
		damage = user_atk * (0.9 + (rand() % 10) / 5.0);
		com_damage = com_atk * (0.9 + (rand() % 10) / 5.0);
		printf("┌────────────────────────┐\n");
		printf("│   당신의 상태         상대방의 상태            │\n");
		printf("│   HP  : %4d            HP  : %5d            │\n", user_hp, com_hp);
		printf("│   MP  : %4d                                   │\n", user_mp, com_mp);
		printf("│   ATK : %4d                                   │\n", user_atk, com_atk);
		printf("└────────────────────────┘\n");
		printf("userdeal: %d COMdeal: %d\n", damage, com_damage);
		printf("userDG: %d COMDG: %d\n", user_dodge, com_dodge);
		printf("userguard: %d turn : %d\n", guard, guard_turn);
		printf("\n\n\n\n\n\n");
		if (turn % 2 == 1) {

			printf("당신의 차례입니다.\n");
			printf("1.공격\t2.방어\n");
			printf("3.%s\n", skill[0]);
			printf("4.%s\n", skill[1]);
			printf("5.%s\n", skill[2]);
			printf("선택 : ");
			scanf("%d", &sel);




			switch (sel) {

			case 1:
				if (com_dodge == 0) {

				}
				else {
					if (user_crit == 0) {
						com_hp -= damage * 2;
					}
					else {
						com_hp -= damage;
					}
				}
				break;
			case 2:
				user_dodge = rand() % 2;
				user_dg_turn++;
				break;

			case 3:
				if (username == "전사") {
					if (com_dodge == 0) {

					}
					else {
						com_hp -= 100;
					}
				}
				else if (username == "암살자")
					if (com_dodge == 0) {

					}
					else {
						if (user_crit == 0) {
							com_hp -= (damage * 2) * 2;
						}
						else
							com_hp -= damage * 2;
					}
				else if (username == "성기사") {
					guard = rand() % 2;
					guard_turn += 4;
				}
				break;
			case 4:
				if (username == "전사") {
					user_crit = rand() % 2;
					user_cri_turn += 3;
				}

				else if (username == "암살자") {
					if (com_dodge == 0) {

					}
					else {
						if (user_crit == 0) {
							com_hp -= (damage * 2) * 3;
							user_hp += ((damage * 2) * 3) / 2.0;
						}
						else {
							com_hp -= (damage * 3);
							user_hp += (damage * 3) / 2.0;
						}
					}
				}
				else if (username == "성기사") {
					com_atk = com_atk / 2.0;
					nurf_turn += 4;
				}
				break;
			case 5:
				if (username == "전사") {
					com_hp -= 400;
				}
				else if (username == "암살자") {
					com_hp = com_hp / 2.0;
				}

				else if (username == "성기사") {
					user_hp += 360;
				}
				break;

			}

			user_mp++;
			turn++;
		}

		else {
			switch (com_level) {

			case 1:

				com_sel1 = rand() % 10;
				if (com_mp >= 0) {
					if (com_sel1 <= 10) {
						if (guard == 0) {
							com_hp -= com_damage;
						}
						else {
							if (user_dodge == 0) {

							}
							else {
								if (com_crit == 0) {
									user_hp -= com_damage * 2;
								}
								else
									user_hp -= com_damage;
							}
						}
					}
					/*else if (com_sel1 > 6) {
					com_dodge = rand() % 2;
					com_dg_turn++;
					}*/


				}
				break;
				//case 2:
				//case 3:
				//case 4:
				//case 5:



			}

			if (user_dg_turn > 0) {
				user_dodge = rand() % 2;
				user_dg_turn--;
				if (user_dg_turn == 0) {
					if (username == "전사") {
						user_dodge = rand() % 10;
					}
					else if (username == "암살자") {
						user_dodge = rand() % 20;
					}

					else if (username == "성기사") {
						user_dodge = rand() % 5;
					}
				}
			}

			if (guard_turn > 0) {
				guard = rand() % 2;
				guard_turn--;
				if (guard_turn == 0) {
					guard = 1;
				}
			}

			if (user_cri_turn > 0) {
				user_crit = rand() % 2;
				user_cri_turn--;

				if (user_cri_turn == 0) {
					if (username == "전사") {
						user_crit = rand() % 5;
					}
				}
			}

			if (nurf_turn > 0) {
				nurf_turn--;
				if (nurf_turn == 0) {
					com_atk = com_atk*2.0;
				}
			}
			if (username == "전사") {
				user_dodge = rand() % 10;
			}
			else if (username == "암살자") {
				user_dodge = rand() % 20;
			}

			else if (username == "성기사") {
				user_dodge = rand() % 5;
			}
			com_mp++;
			turn++;



		}

		system("cls");
	}

	if (user_hp > 0) {
		printf("Win!!");
	}
	else if (com_hp > 0) {
		printf("Lose...");
	}






	return 0;
}