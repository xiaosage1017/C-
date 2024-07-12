#include "Common.h"

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	// 获得控制台窗口句柄
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);				// 设置控制台光标坐标
}

void hidecursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	// 获得控制台窗口句柄
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = 0;
	SetConsoleCursorInfo(handle, &info);				// 设置控制台光标属性
}

int readfile(int game)
{
	int n[5] = {0};
	//
	FILE* fp = fopen("data.txt", "r");
	fscanf(fp, "game1=%d,game2=%d,game3=%d,game4=%d,game5=%d", &n[0], &n[1], &n[2], &n[3], &n[4]);
	fclose(fp);
	//
	return n[game-1];
}

void writefile(int game, int score)
{
	int n[5] = {0};
	//
	FILE* fp = fopen("data.txt", "r");
	fscanf(fp, "game1=%d,game2=%d,game3=%d,game4=%d,game5=%d", &n[0], &n[1], &n[2], &n[3], &n[4]);
	fclose(fp);
	//
	n[game-1] = score;
	//
	fp = fopen("data.txt", "w");
	fprintf(fp, "game1=%d,game2=%d,game3=%d,game4=%d,game5=%d", n[0], n[1], n[2], n[3], n[4]);
	fclose(fp);
}
