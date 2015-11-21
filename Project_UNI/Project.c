//
//  Project.c
//  151111
//
//  Created by �ݶ��ȫ�� on 2015. 11. 14..
//  Copyright ? 2015�� �ݶ��ȫ��. All rights reserved.
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

#define BOARD_WIDTH 8        // ���� ������ ����(��) : ��
#define BOARD_HEIGHT 8        // ���� ������ ����(��) : ��

#define BOARD_X 4 //���� �� x��ǥ
#define BOARD_Y 2 //���� �� y��ǥ

static int score = 0; //��������
static int level = 1; //���ӷ���
static int speed = 500;
int board[BOARD_HEIGHT + 3][BOARD_WIDTH + 4] = { 0, };
int *s;
int Bcolor = 0;

// Ű������ ����Ű�� �����̽��� ���� ������ ����
// _getch()�� ��ȯ�ϴ� ����
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,
	ESC = 27
};

// Ŀ�� ����� : true, T(���̱�), false, F(�����)
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


// ���� �ܼ� ���� Ŀ�� ��ġ�� ����
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
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "��");
		}break;
		case 1: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "��"); }break;
		case 2: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "��"); }break;
		case 3: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "��"); }break;
		case 4: {color(240);
			gotoxy(2 + BOARD_X + y * 2, 1 + BOARD_Y + x * 2, "��"); }break;
		} //else ����

	}
}

// ���� ����..
// Ŀ���� ����Ű�� ��ġ�� �����ڵ� ��� �� �ٲٱ�.
// 0,0�϶� 8 + 2*x, +2* y +3 ��ġ�� ���� ���� �� printf("����"); ����ġ�� ���� �ֱ�
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

// ���� �迭 ǥ���ϱ�
void DrawBoard(int i, int j) {

	switch (board[i][j]) {
	case 5: {color(14);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��");
	}break;
	case 1: {color(11);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
	case 2: {color(12);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
	case 3: {color(10);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
	case 4: {color(9);
		gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
	} //else ����

	SetCursors(7, 3);
}


// ���� �� �ִ� ���� 3�� �̻����� Ȯ��. ������ MakeBoard() �����
// �ٲ��� �ʰ� 3���� ��ġ�� ��Ʈ���� ����.(������ �� ���� �ص�, ǥ�õǸ� �ȵǴ� ���� �����.)
// �������̶� �ٲٰ�(�ٲٴ� �Լ� �����Ͽ� ���), ������, �Ʒ��� 3�� �Ǵ��� Ȯ��.
// �Ʒ��� �ٲٰ� �ݺ�.

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

// ���� �迭 �����(main3)
void CreateBoard(void)
{
	srand(time(0));

	int board_width, board_height;
	for (board_height = 0; board_height < BOARD_HEIGHT; board_height++) {
		for (board_width = 0; board_width <= BOARD_WIDTH; board_width++) {
			board[board_height][board_width] = rand() % 5 + 1;
			// �迭�� �������� ����� �Ѵٸ�
			//if (board_width == 0 || board_width == BOARD_WIDTH + 2 || board_height == 0) board[board_height][board_width] = 0;
		}
	}
	int i, j;
	//ConfirmBoard(); ���忡 ���� �� �ִ°��� 3�� �̻����� Ȯ��, ������ MakeBoard ����
	for (i = 0; i < BOARD_WIDTH; i++) {
		for (j = 0; j < BOARD_HEIGHT; j++) {
			DrawBoard(i, j);
		}
	}
}


// ������ �׸���(main2)
void DrawField(void)
{
	int x, y;

	//�� ���� ����
	for (x = 1; x <= 2 * BOARD_WIDTH + 1; x++)
	{
		board[2 * BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		gotoxy(BOARD_X + x, BOARD_Y, "��");  //�ܼ���ǥ

	}

	//�Ʒ� ���� ����
	for (x = 1; x <= 2 * BOARD_WIDTH + 1; x++)
	{
		board[2 * BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		gotoxy((BOARD_X)+x, BOARD_Y + 2 * BOARD_HEIGHT, "��");  //�ܼ���ǥ

	}

	//���� ���� ����
	for (y = 0; y < 2 * BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board �迭 ���� 1�ν�

		if (y == 0)
			gotoxy(BOARD_X, BOARD_Y + y, "��");
		else if (y == 2 * BOARD_HEIGHT)
			gotoxy(BOARD_X, BOARD_Y + y, "��");
		else
			gotoxy(BOARD_X, BOARD_Y + y, "��");

	}
	//������ ���� ����
	for (y = 0; y < 2 * BOARD_HEIGHT + 1; y++)
	{
		board[y][2 * BOARD_WIDTH + 1] = 1; //board �迭 ������ 1�ν�

		if (y == 0)
			gotoxy(BOARD_X + (2 * BOARD_WIDTH + 2), BOARD_Y + y, "��");

		else if (y == 2 * BOARD_HEIGHT)
			gotoxy(BOARD_X + (2 * BOARD_WIDTH + 2), BOARD_Y + y, "��");
		else
			gotoxy(BOARD_X + (2 * BOARD_WIDTH + 2), BOARD_Y + y, "��");

	}

	//�𼭸��� �� ����
	board[20][0] = 1;
	board[20][11] = 1;

	puts(" ");
}



//���� ����(main1)
void ConsoleInit()
{
	// �ܼ� �ʱ�ȭ �� ���� ȭ�� ���� ����
	gotoxy(0, 0, "c��� �ܼ� ��Ʈ����");
	gotoxy(0, 1, "");
	gotoxy(0, 2, "=================================== ");
	gotoxy(0, 3, "���۹�:");
	gotoxy(0, 4, "[��]     Ŀ���� ���������� �̵�");
	gotoxy(0, 5, "[��]     Ŀ���� �������� �̵�");
	gotoxy(0, 6, "[��]     Ŀ���� �������� �̵�");
	gotoxy(0, 7, "[��]     Ŀ���� �Ʒ��� �̵�");
	gotoxy(0, 8, "[Space]  Ŀ���� ����Ű�� �� ����");
	gotoxy(0, 10, "�ƹ�Ű�� ������ ���۵˴ϴ�.");
	gotoxy(0, 11, "===================================");

	_getch();
	system("cls");            // Console.Clear();
	CursorVisible(false);    // Ŀ�� �����
	SetCursors(0, 0); //����ǥ�� ������ġ ����
}
int main() {
	ConsoleInit();
	DrawField();
	CreateBoard();
	StartGame2();

	SetCursors(0, 0);
}