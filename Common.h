#ifndef _COMMON_H_			
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define High 25  // 游戏画面尺寸
#define Width 50

void gotoxy(int x, int y);
void hidecursor();
int readfile(int game);
void writefile(int game, int score);

#endif
