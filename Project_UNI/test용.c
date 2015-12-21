//
//  Project.c
//  151111
//
//  Created by �ݶ��ȫ�� on 2015. 11. 14..
//  Copyright �� 2015�� �ݶ��ȫ��. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <process.h>

#define true 1
#define T 1
#define false 0
#define F 0 
#define bool int


#define TEST F //������
#define noCF F


#define BOARD_WIDTH 8        // ���� ������ ����(��) : ��
#define BOARD_HEIGHT 8        // ���� ������ ����(��) : ��

#define BOARD_X 4 //���� �� x��ǥ
#define BOARD_Y 2 //���� �� y��ǥ

#define size 0

static int score = 0; //��������
static int level = 1; //���ӷ���
static int speed = 500;

static clock_t start, end;
static long timer = 0;
static long t_limit = 15;
static int s_limit = 3000;

static clock_t fevt;
int fev_lev = 1;

int board[BOARD_WIDTH + 2][BOARD_HEIGHT + 2] = { 0, };
int *s;
int Bcolor = 0;
int RANDOM = 5;
int work = 0;



// Ű������ ����Ű�� �����̽��� ���� ������ ����
// _getch()�� ��ȯ�ϴ� ����
// ���ͳ� ����
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,
	ESC = 27
};

struct Record {
	char name[30];
	int Level;
	int Score;
};


// Ŀ�� ����� : true, T(���̱�), false, F(�����)
// ���ͳ� ����
void CursorVisible(bool blnCursorVisible)    // Console.CursorVisible = false;
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = blnCursorVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


// ���� �� ���� �Լ�.
void color(int n) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Bcolor + n);
}

// ��׶��� ���� �����ϴ� �Լ�.
// �� �Ŀ� color �Լ��� ����ؾ� ����ȴ�.
void BackColor(char t) {
	switch (t) {
	case 'B': Bcolor = 16; break;
	case 'G': Bcolor = 32; break;
	case 'S': Bcolor = 48; break;
	case 'R': Bcolor = 64; break;
	case 'P': Bcolor = 80; break;
	case 'Y': Bcolor = 96; break;
	case 'W': Bcolor = 240; break;
	case 'C': Bcolor = 160; break;
	case 'I': Bcolor = 192; break;
	default: Bcolor = 0; break;
	}
}


// ���� �ܼ� ���� Ŀ�� ��ġ�� ����.
void SetCursors(int cursorLeft, int cursorTop)    // Console.SetCursorPosition(posX, posY);
{
	int posX = cursorLeft;
	int posY = cursorTop;

	COORD pos = { posX, posY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


// ���� �ܼ� ���� Ŀ�� ��ġ�� ������ �� ����Ѵ�
// ���ͳ� ����
void gotoxy(int x, int y, const char* s)
{
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}


// ���� �迭 ǥ���ϱ�
// by �ѳ�
void DrawBoard(int i, int j) {
	if (i >= 0 && i < BOARD_WIDTH&& j >= 0 && j < BOARD_HEIGHT) {
		switch (board[i][j]) {

		case 1: {color(11);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 2: {color(12);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 3: {color(10);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 4: {color(9);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 5: {color(14);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 6: {color(13);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 7: {color(11);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 8: {color(12);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 9: {color(10);
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "��"); }break;
		case 0:
			gotoxy(2 + BOARD_X + i * 2, 1 + BOARD_Y + j * 2, "  ");
			break;
		} //else ����
	}
	SetCursors(7, 3);
}


void fever(int count) {
	if (count == 0) fev_lev = 1;
	else if (count > 3) {
		fev_lev += (count - 3);
		fevt = clock();
	}
	BackColor(' ');
	color(15);
	SetCursors(62, 12);
	printf("%2d", fev_lev);
	SetCursors(58, 11);
	if (fev_lev == 1) printf("off");
	else {
		SetCursors(58, 11);
		printf("      ");
		SetCursors(58, 11);
		printf("on");
	}
}


// ��Ʈ����_����
void Bomb_Height(int x, int y, int(*bomb)[BOARD_HEIGHT]) {
	int plus, minus, shape = board[x][y], temp = 0;

	for (minus = y; minus >= 0; minus--) { // y��ǥ ����
		if (board[x][minus] != shape) break;
	}
	for (plus = y; plus <= BOARD_HEIGHT; plus++) { // y��ǥ �Ʒ���
		if (board[x][plus] != shape) break;
	}

	plus--; minus++;
	if (plus>7)plus--;
	if (minus<0)minus++;
	temp = plus - minus;

	if (temp >= 3 - 1) {

		if (TEST == T) {
			SetCursors(0, 4);
			printf("p:%d m:%d", plus, minus);
		}

		//BackColor('C');
		for (minus; minus <= plus; minus++) {
			bomb[x][minus] = 1;
		}
	}
}


// ��Ʈ����_����
void Bomb_Width(int x, int y, int(*bomb)[BOARD_HEIGHT]) {
	int plus, minus, shape = board[x][y], temp = 0;


	for (minus = x; minus >= 0; minus--) { // x��ǥ ��������
		if (board[minus][y] != shape) break;
	}
	for (plus = x; plus <= BOARD_WIDTH; plus++) { // x��ǥ ����������
		if (board[plus][y] != shape) break;
	}

	plus--; minus++;
	if (plus>7)plus--;
	if (minus<0)minus++;

	temp = plus - minus;

	if (temp >= 3 - 1) {

		if (TEST == T) {
			SetCursors(0, 3);
			printf("p:%d  m:%d", plus, minus);
		}

		//BackColor('C');
		for (minus; minus <= plus; minus++) {
			bomb[minus][y] = 1;
		}
	}
}


// ��Ʈ����
int Bomb(int x, int y, int O) {
	int bomb[BOARD_WIDTH][BOARD_HEIGHT] = { 0, };
	int a, b, count = 0;

	Bomb_Width(x, y, bomb);
	Bomb_Height(x, y, bomb);



	for (b = 0; b < BOARD_HEIGHT; b++) {
		for (a = 0; a < BOARD_WIDTH; a++) {
			if (bomb[a][b] == 1) {
				if (O == 1)	board[a][b] = 0;
				count++;
			}
		}
	}

	if (TEST == T) { SetCursors(20, 25); printf("%d", count); }

	if (count >= 3) {
		if (O == 1) {
			printf("\a");
			BackColor(' ');
			//DrawBoard(x, y);
			score += (count)* 10 * fev_lev;
			if (work == 1) fever(count);
		}
		return count;
	}

	return 0;
}


// by �ѳ�
void drop() {
	int i, j, A;
	srand(time(0));
	int Q;

	while (1) {
		Q = 0;
		for (i = 0; i < BOARD_WIDTH; i++) {
			for (j = 0; j < BOARD_HEIGHT; j++) {
				if (board[i][j] == 0)
				{
					if (j - 1 >= 0) {
						board[i][j] = board[i][j - 1];
						DrawBoard(i, j);

						if (TEST == T) Sleep(75);	// ������
						board[i][j - 1] = 0;
						DrawBoard(i, j - 1);
						Sleep(75);
					}
				}
			}
		}

		for (i = 0; i < BOARD_WIDTH; i++) {
			for (j = 0; j < BOARD_HEIGHT; j++) {
				if (board[i][0] == 0) {
					board[i][j] = rand() % RANDOM + 1;
					DrawBoard(i, j);
					Sleep(100);
				}
			}
		}

		for (i = 0; i < BOARD_WIDTH; i++) {
			for (j = 0; j < BOARD_HEIGHT; j++) {
				if (board[i][j] != 0) {
					Q++;
				}
			}
		}
		if (Q == 64)break;
	}

	BackColor(' ');
	color(15);
	SetCursors(56, 10);
	printf("%5d", score);
	if (score > s_limit && timer <= t_limit) {
		level++;

		BackColor(' ');
		color(15);
		SetCursors(56, 8);
		printf("%d", level);

		if (level % 2 == 0) t_limit -= 3;
		if (level % 2 == 1) RANDOM++;
		score = 0;
	}

	else if ((end - start)>500);
	start = clock();
}

// by �ѳ�
void swap(int *a, int*b, int x, int y, int x2, int y2) {

	int tmp, X, Y;
	int i, j, A, B = 0;

	tmp = *a;
	*a = *b;
	*b = tmp;

	DrawBoard(x, y);
	DrawBoard(x2, y2);

	X = Bomb(x, y, 1);
	Y = Bomb(x2, y2, 1);

	if (X + Y == 0) {
		BackColor('I');

		DrawBoard(x, y);
		DrawBoard(x2, y2);

		Sleep(300);
		tmp = *a;
		*a = *b;
		*b = tmp;

		BackColor(' ');

		DrawBoard(x, y);
		DrawBoard(x2, y2);
	}
	else {
		/*
		end = clock();
		timer = -((start - end) / CLOCKS_PER_SEC);
		BackColor(' ');
		color(15);

		SetCursors(50, 9);
		printf("              ");
		SetCursors(50, 9);
		printf("Time: %02d", timer);

		SetCursors(56, 9);
		printf("%02d", timer);
		*/

		//Sleep(800);


		drop();

		while (1) {
			B = 0;
			for (i = 0; i < BOARD_WIDTH; i++) {
				for (j = 0; j < BOARD_HEIGHT; j++) {
					Sleep(10);
					A = Bomb(i, j, 1);
					drop();
					B += A;
				}
			}
			if (B == 0) break;
		}
	}

}

// ���� �� �ִ� ���� 3�� �̻����� Ȯ��. ������ MakeBoard() �����
// �ٲ��� �ʰ� 3���� ��ġ�� ��Ʈ���� ����.(������ �� ���� �ص�, ǥ�õǸ� �ȵǴ� ���� �����.)
// �������̶� �ٲٰ�(�ٲٴ� �Լ� �����Ͽ� ���), ������, �Ʒ��� 3�� �Ǵ��� Ȯ��.
// �Ʒ��� �ٲٰ� �ݺ�.
// �̿�!
int StartGame();
void CreateBoard();
void ConfirmBoard() {
	int i, j, n = 0;
	int tmp;
	char ip = '\0';
	for (i = 0; i<BOARD_HEIGHT; i++) {
		for (j = 0; j<BOARD_WIDTH; j++) {
			tmp = board[j][i];
			board[j][i] = board[j][i + 1];
			board[j][i + 1] = tmp;
			n += Bomb(i, j, 0);
			tmp = board[j][i];
			board[j][i] = board[j][i + 1];
			board[j][i + 1] = tmp;
		}
	}


	for (i = 0; i<BOARD_HEIGHT; i++) {
		for (j = 0; j<BOARD_WIDTH; j++) {
			tmp = board[j][i];
			board[j][i] = board[j + 1][i];
			board[j + 1][i] = tmp;
			n += Bomb(i, j, 0);
			tmp = board[j][i];
			board[j][i] = board[j + 1][i];
			board[j + 1][i] = tmp;

		}
	}
	if (TEST == T) { SetCursors(20, 23); printf("%d", n); }

	if (n < 2) {
		color(15);
		SetCursors(5, 20);
		printf("�� �̻� ���������� ��ƽ��ϴ�.");
		SetCursors(5, 21);
		printf("������ ����Ϸ��� space,�׸��ѷ��� esc�� �����ּ���.");
		ip = _getch();
		switch (ip) {
		case ESC: system("cls"); exit(1); break;
		case UP:
		case DOWN:
		case LEFT:
		case RIGHT:
		case SPACE: {
			SetCursors(5, 20);
			printf("                                                   ");
			SetCursors(5, 21);
			printf("                                                      \n");
			CreateBoard();
			StartGame();
			break;
		}
		}
	}
}


void record_R();
void record_W() {
	struct Record r[10];
	int i;
	char NAME[30];
	FILE *f;

	f = fopen("record.txt", "r");

	for (i = 0; i<10; i++)
		fscanf(f, "%s %d %d\n", r[i].name, &r[i].Level, &r[i].Score);
	fclose(f);

	for (i = 8; i >= 0; i--) {

		strcpy(r[i + 1].name, r[i].name);
		r[i + 1].Level = r[i].Level;
		r[i + 1].Score = r[i].Score;

	}

	printf("������� �̸��� �Է��Ͻÿ�.\n");

	gets(r[size].name);
	r[size].Level = level;
	r[size].Score = score;

	f = fopen("record.txt", "w");

	for (i = 0; i<10; i++) {
		fprintf(f, "%s %d %d\n", r[i].name, r[i].Level, r[i].Score);
	}
	fclose(f);
}


// ���� ����.
// Ŀ���� ����Ű�� ��ġ�� �����ڵ� ��� �� �ٲٱ�.
// 0,0�϶� 8 + 2*x, +2* y +3 ��ġ�� ���� ���� �� printf("����"); ����ġ�� ���� �ֱ�
int StartGame() {
	int i, j, A, B;

	if (noCF == F) ConfirmBoard();

	BackColor(' ');
	color(15);
	SetCursors(50, 8);
	printf("Level:%d", level);
	SetCursors(50, 9);
	printf("Time: %d ", timer);
	SetCursors(50, 10);
	printf("score:%d", score);
	SetCursors(50, 11);
	printf("fever:  off");
	SetCursors(50, 12);
	printf("fever level: %d", fev_lev);


	while (1) {
		B = 0;
		for (i = 0; i < BOARD_WIDTH; i++) {
			for (j = 0; j < BOARD_HEIGHT; j++) {
				Sleep(50);
				A = Bomb(i, j, 1);

				drop();
				B += A;

			}
		}
		if (B == 0)break;
	}


	int x = 0, y = 0, x1 = 0, y1 = 0, x2 = -1, y2 = -1, sel = F, count = 0;
	char ip = '\0';

	BackColor('G');
	DrawBoard(x, y);

	work = 1;
	while (1) {
		if (start > end) fevt = fevt + (start - end) / 2;

		if (TEST == T) { SetCursors(50, 14); printf("%03d", (end - fevt) / CLOCKS_PER_SEC); }


		if ((end - fevt) / CLOCKS_PER_SEC == 10) {
			fever(0);
		}
		Sleep(10);

		end = clock();
		timer = -((start - end) / CLOCKS_PER_SEC);
		BackColor(' ');
		color(15);
		SetCursors(56, 9);
		printf("%02d", timer);
		SetCursors(60, 9);
		printf("      ");
		SetCursors(60, 9);
		printf("/%d", t_limit);

		if (timer > t_limit) {
			BackColor(' ');
			color(15);
			SetCursors(50, 7);
			printf("Game Over");
			Sleep(2000);
			system("cls");
			record_W();
			exit(1);
		}

		if (_kbhit()) {

			if (sel != T) {
				if (x1 == x2 && y1 == y2) BackColor('W');
				else BackColor(' ');

				DrawBoard(x1, y1);
			}

			BackColor('G');


			ip = _getch();


			switch (ip) {
			case LEFT:sel = F; if (x > 0) x -= 1; DrawBoard(x, y); break;
			case RIGHT: sel = F; if (x < BOARD_WIDTH - 1) x += 1; DrawBoard(x, y); break;
			case UP:; sel = F; if (y > 0) y -= 1; DrawBoard(x, y); break;
			case DOWN: sel = F; if (y < BOARD_HEIGHT - 1) y += 1; DrawBoard(x, y); break;
			case SPACE:sel = T; if ((x1 == x2 + 1 && y1 == y2) || (x1 == x2&&y1 == y2 + 1) || (x1 == x2 - 1 && y1 == y2) || (x1 == x2&&y1 == y2 - 1) || count == 0)BackColor('W'); DrawBoard(x, y);  count++; if (count == 1) { x2 = x; y2 = y; }
					   if (count >= 2) {

						   BackColor(' ');
						   if ((x1 == x2 + 1 && y1 == y2) || (x1 == x2&&y1 == y2 + 1) || (x1 == x2 - 1 && y1 == y2) || (x1 == x2&&y1 == y2 - 1)) {

							   swap(&board[x][y], &board[x2][y2], x, y, x2, y2);
							   if (noCF == F) ConfirmBoard();
						   }

						   BackColor(' ');
						   DrawBoard(x, y);
						   //DrawBoard(x2, y2);
						   count = 0;
						   x2 = -1; y2 = -1;
					   }

					   break;

			case ESC: sel = F; system("cls"); exit(1); break;
			}

			x1 = x; y1 = y;

			sel = F;

			SetCursors(0, 0);
			if (TEST == T) printf("%d  %d\n%d  %d %d \n %d", x1, y1, x2, y2, count, sel);
		}
	}
}


// ���� �迭 �����(main3).
void CreateBoard(void)
{
	work = 0;
	srand(time(0));

	int board_width, board_height;
	for (board_height = 0; board_height < BOARD_HEIGHT; board_height++) {
		for (board_width = 0; board_width <= BOARD_WIDTH; board_width++) {
			board[board_height][board_width] = rand() % RANDOM + 1;
			// �迭�� �������� ����� �Ѵٸ�
			//if (board_width == 0 || board_width == BOARD_WIDTH + 2 || board_height == 0) board[board_height][board_width] = 0;
		}
	}

	
	board[0][0] = 1;
	board[0][1] = 1;
	board[0][2] = 2;
	board[0][3] = 2;
	board[0][4] = 3;
	board[0][5] = 3;
	board[0][6] = 4;
	board[0][7] = 4;
	board[1][0] = 1;
	board[1][1] = 1;
	board[1][2] = 2;
	board[1][3] = 2;
	board[1][4] = 3;
	board[1][5] = 3;
	board[1][6] = 4;
	board[1][7] = 4;
	board[2][0] = 3;
	board[2][1] = 3;
	board[2][2] = 4;
	board[2][3] = 4;
	board[2][4] = 5;
	board[2][5] = 5;
	board[2][6] = 1;
	board[2][7] = 1;
	board[3][0] = 3;
	board[3][1] = 3;
	board[3][2] = 4;
	board[3][3] = 4;
	board[3][4] = 5;
	board[3][5] = 5;
	board[3][6] = 1;
	board[3][7] = 1;
	board[4][0] = 5;
	board[4][1] = 5;
	board[4][2] = 1;
	board[4][3] = 1;
	board[4][4] = 2;
	board[4][5] = 2;
	board[4][6] = 3;
	board[4][7] = 3;
	board[5][0] = 5;
	board[5][1] = 5;
	board[5][2] = 1;
	board[5][3] = 1;
	board[5][4] = 2;
	board[5][5] = 2;
	board[5][6] = 3;
	board[5][7] = 3;
	board[6][0] = 2;
	board[6][1] = 2;
	board[6][2] = 3;
	board[6][3] = 3;
	board[6][4] = 4;
	board[6][5] = 4;
	board[6][6] = 5;
	board[6][7] = 5;
	board[7][0] = 2;
	board[7][1] = 2;
	board[7][2] = 3;
	board[7][3] = 3;
	board[7][4] = 4;
	board[7][5] = 4;
	board[7][6] = 5;
	board[7][7] = 5;
	

	int i, j;
	//if(noCF == F) ConfirmBoard(); //���忡 ���� �� �ִ°��� 3�� �̻����� Ȯ��, ������ MakeBoard ����
	for (i = 0; i < BOARD_WIDTH; i++) {
		for (j = 0; j < BOARD_HEIGHT; j++) {
			DrawBoard(i, j);
		}
	}
}


// ������ �׸���(main2).
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



//���� ����(main1).
void ConsoleInit()
{
	char ip = '\0';
	// �ܼ� �ʱ�ȭ �� ���� ȭ�� ���� ����
	gotoxy(7, 4, "c��� �ܼ� ��Ʈ����");
	gotoxy(3, 5, "");
	gotoxy(3, 6, "=================================== ");
	gotoxy(3, 7, "���۹�:");
	gotoxy(3, 8, "[��]     Ŀ���� ���������� �̵�");
	gotoxy(3, 9, "[��]     Ŀ���� �������� �̵�");
	gotoxy(3, 10, "[��]     Ŀ���� �������� �̵�");
	gotoxy(3, 11, "[��]     Ŀ���� �Ʒ��� �̵�");
	gotoxy(3, 12, "[Space]  Ŀ���� ����Ű�� �� ����");
	gotoxy(3, 13, "[R,r]    ��������� �� �� �ֽ��ϴ�");
	gotoxy(3, 15, "�ƹ�Ű�� ������ ���۵˴ϴ�.");
	gotoxy(3, 16, "===================================");

	ip = _getch();

	if (ip == 82 || ip == 114) {
		system("cls");
		record_R();

	}
	else {
		system("cls");            // Console.Clear();
		CursorVisible(false);    // Ŀ�� �����
		SetCursors(0, 0); //����ǥ�� ������ġ ����
	}
}


int main() {
	system("cls");
	ConsoleInit();
	DrawField();
	CreateBoard();
	StartGame();

	SetCursors(0, 0);
}

void record_R() {
	struct Record r[10];
	int i;
	char ip = '\0';
	FILE *f;
	f = fopen("record.txt", "r");

	for (i = 0; i<10; i++)
		fscanf(f, "%s %d %d\n", r[i].name, &r[i].Level, &r[i].Score);
	fclose(f);

	printf(" �̸� Lv ����\n");
	printf("-----------------\n");
	for (i = 0; i<10; i++)
		printf("%s %d %d\n", r[i].name, r[i].Level, r[i].Score);
	printf("\n�ƹ�Ű�� ������ ����ȭ��");

	ip = _getch();

	if (ip == ESC)exit(0);
	else {
		system("cls");
		ConsoleInit();
		DrawField();
		CreateBoard();
		StartGame();
	}
}