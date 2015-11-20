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

#define BOARD_WIDTH 20        // ���� ������ ����(��) >= 20 : ��
#define BOARD_HEIGHT 20        // ���� ������ ����(��) >= 20 : ��

#define BOARD_X 4 //���� �� x��ǥ
#define BOARD_Y 2 //���� �� y��ǥ

static int score = 0; //��������
static int level = 1; //���ӷ���
static int speed = 500;
int board[BOARD_HEIGHT][BOARD_WIDTH + 1] = { 0, };

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
void SetCur(int cursorLeft, int cursorTop)    // Console.SetCursorPosition(posX, posY);
{
	int posX = cursorLeft;
	int posY = cursorTop;

	COORD pos = { posX, posY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���� �����(main3)
void DrawBaord(void)
{
	srand(time(0));

	int board_width, board_height;
	for (board_height = 0; board_height < BOARD_HEIGHT - 1; board_height += 2) {
		SetCur(7, board_height + 3);
		for (board_width = 0; board_width <= BOARD_WIDTH; board_width += 2) {
			board[board_height][board_width] = rand() % 5;
			// �迭�� �������� ����� �Ѵٴϱ��
			//if (board_width == 0 || board_width == BOARD_WIDTH + 2 || board_height == 0) board[board_height][board_width] = 0;

			if (board_width == BOARD_WIDTH) printf("%d", board[board_height][board_width]);
			else printf("%-4d", board[board_height][board_width]);
		}
	}
}


// ������ �׸���(main2)
void DrawField(void)
{
	int x, y;

	//�� ���� ����
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		SetCur((BOARD_X)+x * 2, BOARD_Y);  //�ܼ���ǥ
		printf("��");
	}

	//�Ʒ� ���� ����
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		SetCur((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //�ܼ���ǥ
		printf("��");
	}

	//���� ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board �迭 ���� 1�ν�
		SetCur(BOARD_X, BOARD_Y + y);
		if (y == 0)
			printf("��");
		else if (y == BOARD_HEIGHT)
			printf("��");
		else
			printf("��");
	}
	//������ ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][BOARD_WIDTH + 1] = 1; //board �迭 ������ 1�ν�
		SetCur(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == 0)
			printf("��");
		else if (y == BOARD_HEIGHT)
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
	SetCur(0, 0); //����ǥ�� ������ġ ����
}

int main() {
	ConsoleInit();
	DrawField();
	DrawBaord();


	SetCur(0, 0);
}