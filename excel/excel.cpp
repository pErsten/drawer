#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN
#define SCREEN_WIDTH 101
#define SCREEN_HEIGHT 25
using namespace std;

int main()
{
	int posy = 3, posx = 1;

	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	for (int i = 1; i < 16; i++) {
		buffer[0][i-1].Char.AsciiChar = ' ';
		buffer[1][i-1].Char.AsciiChar = i + 48;
		buffer[0][i-1].Attributes = i*16;
	}

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		buffer[2][i].Char.AsciiChar = '*';
		buffer[SCREEN_HEIGHT - 1][i].Char.AsciiChar = '*';
	}
	for (int i = 2; i < SCREEN_HEIGHT; i++) {
		buffer[i][SCREEN_WIDTH - 1].Char.AsciiChar = '*';
		buffer[i][0].Char.AsciiChar = '*';
	}

	int color = 15;
	buffer[3][1].Char.AsciiChar = '_'; buffer[3][1].Attributes = color;
	WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	while (_kbhit) {
		char c = _getch();
		if ((int)(c) > 48 && (int)(c) < 64)
			color = (c - 48);
		else switch (c) {
		case 'w': if (buffer[posy][posx].Char.AsciiChar == '_') buffer[posy][posx].Char.AsciiChar = ' ';
				  if (posy > 3)					posy--; buffer[posy][posx].Char.AsciiChar = '_'; 
				  if (buffer[posy][posx].Attributes < 16) buffer[posy][posx].Attributes = color; break;
		case 'd': if (buffer[posy][posx].Char.AsciiChar == '_') buffer[posy][posx].Char.AsciiChar = ' ';
				  if (posx < SCREEN_WIDTH - 2)	posx++; buffer[posy][posx].Char.AsciiChar = '_';
				  if (buffer[posy][posx].Attributes < 16) buffer[posy][posx].Attributes = color; break;
		case 's': if (buffer[posy][posx].Char.AsciiChar == '_') buffer[posy][posx].Char.AsciiChar = ' ';
				  if (posy < SCREEN_HEIGHT - 2) posy++; buffer[posy][posx].Char.AsciiChar = '_';
				  if (buffer[posy][posx].Attributes < 16) buffer[posy][posx].Attributes = color; break;
		case 'a': if (buffer[posy][posx].Char.AsciiChar == '_') buffer[posy][posx].Char.AsciiChar = ' ';
				  if (posx > 1)					posx--; buffer[posy][posx].Char.AsciiChar = '_';
				  if (buffer[posy][posx].Attributes < 16) buffer[posy][posx].Attributes = color; break;
		case ' ': buffer[posy][posx].Char.AsciiChar = '_'; buffer[posy][posx].Attributes = color * 16; break;
		case 'z': buffer[posy][posx].Char.AsciiChar = '_'; buffer[posy][posx].Attributes = color; break;
		}
		WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
			dwBufferCoord, &rcRegion);
	}
}