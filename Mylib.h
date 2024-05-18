#pragma once
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <ctime> 
#include "windows.h" 
//======= l?y t?a d? x c?a con tr? hi?n t?i =============
#define KEY_NONE	-1
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= l?y t?a d? y c?a con tr? hi?n t?i =======
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
//============== d?ch con tr? hi?n t?i d?n di?m c? t?a d? (x,y) ==========
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//============= d?t m?u cho ch? =========
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== l?m ?n tr? chu?t ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//======= tr? v? m? ph?m ngu?i d?ng b?m =========
int inputKey()
{
	if (_kbhit()) //true
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}
	return KEY_NONE;
}
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

