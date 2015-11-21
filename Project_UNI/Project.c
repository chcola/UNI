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
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define true 1
#define T 1
#define false 0
#define F 0
#define bool int

#define BOARD_WIDTH 8        // 게임 영역의 가로(열) : ━
#define BOARD_HEIGHT 8        // 게임 영역의 세로(행) : ┃

#define BOARD_X 4 //보드 열 x좌표
#define BOARD_Y 2 //보드 행 y좌표

static int score = 0; //게임점수
static int level = 1; //게임레벨
static int speed = 500;
int board[BOARD_HEIGHT + 3][BOARD_WIDTH + 4] = { 0, };
int *s;
int Bcolor = 0;

// 키보드의 방향키와 스페이스에 대한 열거형 지정
// _getch()가 반환하는 값이
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,
	ESC = 27
};

// 커서 숨기기 : true, T(보이기), false, F(숨기기)
void CursorVisible(bool blnCursorVisible)    // Console.CursorVisible = false;
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = blnCursorVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void color(int n) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Bcolor + n);
}
void BackColor(char t) {
	switch (t) {
	case 'B': Bcolor = 16; break;
	case 'G': Bcolor = 32; break;
	case 'S': Bcolor = 48; break;
	case 'R': Bcolor = 64; break;
	case 'P': Bcolor = 80; break;
	case 'Y': Bcolor = 96; break;
	case 'W': Bcolor = 240; break;
	default: Bcolor = 0; break;
	}
}


// 현재 콘솔 내의 커서 위치를 설정
void gotoxy(int x, int y, const char* s)
{
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);


}

void SetCursors(int cursorLeft, int cursorTop)    // Console.SetCursorPosition(posX, posY);
{
	int posX = cursorLeft;
	int posY = cursorTop;

	COORD pos = { posX, posY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



void DrawBoard(int i, int j);
void fff(int *p) {
	int x, y;
	int *n;
	n = &board[0][0];
	x = ((p - n)) / 14;
	y = ((p - n)) % 14;
	if (x < 10 && y < 13) {
		while (1) {

			DrawBoard(y, x);
			Sleep(100);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "  ");
			Sleep(100);
			if (_kbhit())break;
		}
		DrawBoard(y, x);
	}

}
void kkk(int *p) {
	int x, y;
	int *n;
	n = &board[0][0];
	x = ((p - n)) / 14;
	y = ((p - n)) % 14;
	if (x<10 && y<13) {
		color(240);
		switch (board[y][x]) {
		case 5: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "★");
		}break;
		case 1: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "◆"); }break;
		case 2: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "♥"); }break;
		case 3: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "♣"); }break;
		case 4: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "♠"); }break;
		} //else 종료

	}
}

// 게임 시작..
// 커서가 가리키는 위치의 유니코드 배경 색 바꾸기.
// 0,0일때 8 + 2*x, +2* y +3 위치에 배경색 설정 후 printf("유니"); 스위치문 갖다 넣기
void StartGame() {
	int i, j;
	char ip = '\0';
	s = &board[0][0];
	fff(s);
	while (1) {
		if (_kbhit()) {
			ip = _getch();
			switch (ip) {
			case LEFT:if (s != &board[0][0] && s != &board[1][0] && s != &board[2][0] && s != &board[3][0] && s != &board[4][0] && s != &board[5][0] && s != &board[6][0] && s != &board[7][0] && s != &board[8][0] && s != &board[9][0]) { s = s - 1; fff(s); }break;
			case RIGHT:if (s != &board[0][9] && s != &board[1][9] && s != &board[2][9] && s != &board[3][9] && s != &board[4][9] && s != &board[5][9] && s != &board[6][9] && s != &board[7][9] && s != &board[8][9] && s != &board[9][9]) { s = s + 1; fff(s); }break;
			case UP:if (s != &board[0][0] && s != &board[0][1] && s != &board[0][2] && s != &board[0][3] && s != &board[0][4] && s != &board[0][5] && s != &board[0][6] && s != &board[0][7] && s != &board[0][8] && s != &board[0][9]) { s -= 14; fff(s); }break;
			case DOWN:if (s != &board[9][0] && s != &board[9][1] && s != &board[9][2] && s != &board[9][3] && s != &board[9][4] && s != &board[9][5] && s != &board[9][6] && s != &board[9][7] && s != &board[9][8] && s != &board[9][9]) { s += 14; fff(s); }break;
			case SPACE:if (*s>0)kkk(s); break;
			case ESC:system("cls"); exit(1); break;
			}

		}

	}
}

int StartGame2() {
	int x = 0, y = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, sel = F, count = 0;
	char ip = '\0';

	while (1) {
		if (_kbhit()) {
			if (sel != T) {
				BackColor(' ');
				DrawBoard(x1, y1);
			}
			
			BackColor('G');

			ip = _getch();

			switch (ip) {
			case LEFT:if (x > 0) x -= 1; DrawBoard(x, y); break;
			case RIGHT: sel = F; if (x < BOARD_WIDTH - 1) x += 1; DrawBoard(x, y); break;
			case UP:; sel = F; if (y > 0) y -= 1; DrawBoard(x, y); break;
			case DOWN: sel = F; if (y < BOARD_HEIGHT - 1) y += 1; DrawBoard(x, y); break;
			case SPACE: sel = F; BackColor('W'); DrawBoard(x, y); sel = T; count++;
				if (count >= 2) {
					BackColor(' ');
					Sleep(300);
					DrawBoard(x1, y1);
					DrawBoard(x2, y2);
					count = 0;
				} break;// if (*s > 0)kkk(s); break;
			case ESC: sel = F; system("cls"); exit(1); break;
			}

			x2 = x1; y2 = y1; x1 = x; y1 = y;

			SetCursors(0, 0);
			printf("%d  %d\n%d  %d %d", x1, y1, x2, y2, count);
		}
	}
}

// 보드 배열 표시하기
void DrawBoard(int i, int j) {

	switch (board[i][j]) {
	case 5: {color(14);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "★");
	}break;
	case 1: {color(11);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "◆"); }break;
	case 2: {color(12);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "♥"); }break;
	case 3: {color(10);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "♣"); }break;
	case 4: {color(9);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "♠"); }break;
	} //else 종료

	SetCursors(7, 3);
}


// 맞출 수 있는 것이 3개 이상인지 확인. 없으면 MakeBoard() 재실행
// 바꾸지 않고 3개가 겹치면 터트리기 먼저.(터지는 것 구현 해도, 표시되면 안되니 따로 만들것.)
// 오른쪽이랑 바꾸고(바꾸는 함수 구현하여 사용), 오른쪽, 아래랑 3개 되는지 확인.
// 아래와 바꾸고 반복.

void CreateBoard();
void ConfirmBoard() {
	int x_axis, y_axis, count = 0;
	for (y_axis = 0; y_axis < BOARD_HEIGHT; y_axis++) {
		for (x_axis = 0; x_axis < BOARD_WIDTH; x_axis++) {
			if (board[y_axis][x_axis] == board[y_axis][x_axis + 1] && board[y_axis][x_axis + 1] == board[y_axis][x_axis + 2])
				count++;
			if (board[y_axis][x_axis] == board[y_axis + 1][x_axis] && board[y_axis + 1][x_axis] == board[y_axis + 2][x_axis])
				count++;
		}
	}

	if (count <= 3) CreateBoard();
}

// 보드 배열 만들기(main3)
void CreateBoard(void)
{
	srand(time(0));

	int board_width, board_height;
	for (board_height = 0; board_height < BOARD_HEIGHT; board_height++) {
		for (board_width = 0; board_width <= BOARD_WIDTH; board_width++) {
			board[board_height][board_width] = rand() % 5 + 1;
			// 배열의 마지막을 비워야 한다면
			//if (board_width == 0 || board_width == BOARD_WIDTH + 2 || board_height == 0) board[board_height][board_width] = 0;
		}
	}
	int i, j;
	//ConfirmBoard(); 보드에 맞출 수 있는것이 3개 이상인지 확인, 없으면 MakeBoard 실행
	for (i = 0; i < BOARD_WIDTH; i++) {
		for (j = 0; j < BOARD_HEIGHT; j++) {
			DrawBoard(i, j);
		}
	}
}


// 게임판 그리기(main2)
void DrawField(void)
{
	int x, y;

	//위 보드 라인
	for (x = 1; x <= 2 * BOARD_WIDTH + 1; x++)
	{
		board[2 * BOARD_HEIGHT][x] = 1; //board 배열 중앙 1인식
		gotoxy(BOARD_X + x, BOARD_Y, "─");  //콘솔좌표

	}

	//아래 보드 라인
	for (x = 1; x <= 2 * BOARD_WIDTH + 1; x++)
	{
		board[2 * BOARD_HEIGHT][x] = 1; //board 배열 중앙 1인식
		gotoxy((BOARD_X)+x, BOARD_Y + 2 * BOARD_HEIGHT, "─");  //콘솔좌표

	}

	//왼쪽 보드 라인
	for (y = 0; y < 2 * BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board 배열 왼쪽 1인식

		if (y == 0)
			gotoxy(BOARD_X, BOARD_Y + y, "┌");
		else if (y == 2 * BOARD_HEIGHT)
			gotoxy(BOARD_X, BOARD_Y + y, "└");
		else
			gotoxy(BOARD_X, BOARD_Y + y, "│");

	}
	//오른쪽 보드 라인
	for (y = 0; y < 2 * BOARD_HEIGHT + 1; y++)
	{
		board[y][2 * BOARD_WIDTH + 1] = 1; //board 배열 오른쪽 1인식

		if (y == 0)
			gotoxy(BOARD_X + (2 * BOARD_WIDTH + 2), BOARD_Y + y, "┐");

		else if (y == 2 * BOARD_HEIGHT)
			gotoxy(BOARD_X + (2 * BOARD_WIDTH + 2), BOARD_Y + y, "┘");
		else
			gotoxy(BOARD_X + (2 * BOARD_WIDTH + 2), BOARD_Y + y, "│");

	}

	//모서리값 값 변경
	board[20][0] = 1;
	board[20][11] = 1;

	puts(" ");
}



//게임 설명(main1)
void ConsoleInit()
{
	// 콘솔 초기화 및 시작 화면 구성 영역
	gotoxy(0, 0, "c언어 콘솔 테트리스");
	gotoxy(0, 1, "");
	gotoxy(0, 2, "=================================== ");
	gotoxy(0, 3, "조작법:");
	gotoxy(0, 4, "[→]     커서를 오른쪽으로 이동");
	gotoxy(0, 5, "[←]     커서를 왼쪽으로 이동");
	gotoxy(0, 6, "[↑]     커서를 왼쪽으로 이동");
	gotoxy(0, 7, "[↓]     커서를 아래로 이동");
	gotoxy(0, 8, "[Space]  커서가 가리키는 블럭 선택");
	gotoxy(0, 10, "아무키나 누르면 시작됩니다.");
	gotoxy(0, 11, "===================================");

	_getch();
	system("cls");            // Console.Clear();
	CursorVisible(false);    // 커서 숨기기
	SetCursors(0, 0); //보드표시 시작위치 설정
}
int main() {
	ConsoleInit();
	DrawField();
	CreateBoard();
	StartGame2();

	SetCursors(0, 0);
}