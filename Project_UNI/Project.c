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
#include <time.h>
#include <windows.h>
//#include <conio.h>

#define true 1
#define T 1
#define false 0
#define F 0
#define bool int

#define BOARD_WIDTH 8        // ���� ������ ����(��) >= 10 : ��
#define BOARD_HEIGHT 8        // ���� ������ ����(��) >= 10 : ��8
#define BOARD_X 4 //���� �� x��ǥ
#define BOARD_Y 2 //���� �� y��ǥ

static int score = 0; //��������
static int level = 1; //���ӷ���
static int speed = 500;
int board[BOARD_HEIGHT + 3][BOARD_WIDTH + 4] = { 0, };


// Ű������ ����Ű�� �����̽��� ���� ������ ����
// _getch()�� ��ȯ�ϴ� ����
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

// Ŀ�� ����� : true, T(���̱�), false, F(�����)
void CursorVisible(bool blnCursorVisible)    // Console.CursorVisible = false;
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = blnCursorVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ���� �ܼ� ���� Ŀ�� ��ġ�� ����
void SetCursors(int cursorLeft, int cursorTop)    // Console.SetCursorPosition(posX, posY);
{
	int posX = cursorLeft;
	int posY = cursorTop;

	COORD pos = { posX, posY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���� ����..
// Ŀ���� ����Ű�� ��ġ�� �����ڵ� ��� �� �ٲٱ�.
// 0,0�϶� 8 + 2*x, +2* y +3 ��ġ�� ���� ���� �� printf("����"); ����ġ�� ���� �ֱ�
void StartGame() {
	return 0;
}

// ���� �迭 ǥ���ϱ�
void DrawBoard(void) {
	int board_width, board_height;
	for (board_height = 0; board_height < BOARD_HEIGHT; board_height ++) {
		SetCursors(8, 2 * board_height + 3);
		for (board_width = 0; board_width < BOARD_WIDTH; board_width++) {
			if (board_width == BOARD_WIDTH) {
				switch (board[board_height][board_width]) {
				case 1: printf("��"); break;
				case 2: printf("��"); break;
				case 3: printf("��"); break;
				case 4: printf("��"); break;
				case 5: printf("��"); break;
				}
			}
			else {
				switch (board[board_height][board_width]) {
				case 1: printf("��  "); break;
				case 2: printf("��  "); break;
				case 3: printf("��  "); break;
				case 4: printf("��  "); break;
				case 5: printf("��  "); break;
				}
			} //else ����
		} // ���� for ����
	} // �ٱ� for ����

	SetCursors(7, 3);
}

// ���� �� �ִ� ���� 3�� �̻����� Ȯ��. ������ MakeBoard() �����
// �ٲ��� �ʰ� 3���� ��ġ�� ��Ʈ���� ����.(������ �� ���� �ص�, ǥ�õǸ� �ȵǴ� ���� �����.)
// �������̶� �ٲٰ�(�ٲٴ� �Լ� �����Ͽ� ���), ������, �Ʒ��� 3�� �Ǵ��� Ȯ��.
// �Ʒ��� �ٲٰ� �ݺ�.

void CreateBoard();
ConfirmBoard() {
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
	return 0;
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

	//ConfirmBoard(); ���忡 ���� �� �ִ°��� 3�� �̻����� Ȯ��, ������ MakeBoard ����
	DrawBoard();
}


// ������ �׸���(main2)
void DrawField(void)
{
	int x, y;

	//�� ���� ����
	for (x = 1; x <= 2 * BOARD_WIDTH + 1; x++)
	{
		board[2 * BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		SetCursors((BOARD_X)+x * 2, BOARD_Y);  //�ܼ���ǥ
		printf("��");
	}

	//�Ʒ� ���� ����
	for (x = 1; x <= 2 * BOARD_WIDTH + 1; x++)
	{
		board[2 * BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		SetCursors((BOARD_X)+x * 2, BOARD_Y + 2 * BOARD_HEIGHT);  //�ܼ���ǥ
		printf("��");
	}

	//���� ���� ����
	for (y = 0; y < 2 * BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board �迭 ���� 1�ν�
		SetCursors(BOARD_X, BOARD_Y + y);
		if (y == 0)
			printf("��");
		else if (y == 2 * BOARD_HEIGHT)
			printf("��");
		else
			printf("��");
	}
	//������ ���� ����
	for (y = 0; y < 2 * BOARD_HEIGHT + 1; y++)
	{
		board[y][2 * BOARD_WIDTH + 1] = 1; //board �迭 ������ 1�ν�
		SetCursors(BOARD_X + (2 * BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == 0)
			printf("��");
		else if (y == 2 * BOARD_HEIGHT)
			printf("��");
		else
			printf("��");
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
	printf("C��� �ܼ� ��Ʈ����\n\n");
	printf(""
		"===================================        \n"
		"���۹�:                                        \n"
		"[��]     Ŀ���� ���������� �̵�              \n"
		"[��]     Ŀ���� �������� �̵�                \n"
		"[��]     Ŀ���� �������� �̵�            \n"
		"[��]     Ŀ���� �Ʒ��� �̵�            \n"
		"[Space]  Ŀ���� ����Ű�� �� ����                  \n"
		"                                            \n"
		"�ƹ�Ű�� ������ ���۵˴ϴ�.                    \n"
		"===================================           \n");
	_getch();
	system("cls");            // Console.Clear();
	CursorVisible(false);    // Ŀ�� �����
	SetCursors(0, 0); //����ǥ�� ������ġ ����
}

int main() {
	ConsoleInit();
	DrawField();
	CreateBoard();
	StartGame();

	SetCursors(0, 0);
}