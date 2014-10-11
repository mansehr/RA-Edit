// ------------------------------- define ---------------------

#ifndef __CONIO_H
#define __CONIO_H
#endif

#ifdef __linux__
#define BLACK       0
#define RED         1
#define GREEN       2
#define BROWN       3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define LIGHTGRAY   7
#define DARKGRAY    0
#define LIGHTRED    1
#define LIGHTGREEN  2
#define YELLOW      3
#define LIGHTBLUE   4
#define PINK        5
#define LIGHTCYAN   6
#define WHITE       7
#else
#define DARKGRAY	0x7
#define WHITE 		0xF
#define BLACK		0x0
#define BLUE		0x9
#endif

void clrscr();

void cputs(const char*);

char getch();

int gotoxy(int x, int y);

void textbackground(short);

void textcolor(short);

// New Methods, not standard conio.h
void setTitle(const char*);

