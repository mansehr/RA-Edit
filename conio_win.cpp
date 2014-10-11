
#include <windows.h>
#include <stdio.h>
#include "conio.h"


/*
bit 0 - foreground blue
bit 1 - foreground green
bit 2 - foreground red
bit 3 - foreground intensity

bit 4 - background blue
bit 5 - background green
bit 6 - background red
bit 7 - background intensity
*/
int lastColor = 0x0F;
void setColor(int color) {
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
	lastColor = color;
}

void setTitle(char* str) {
	SetConsoleTitle(str);
}

void getWindowSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut = GetStdHandle( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo( hConsoleOut, &csbiInfo );
	//printf("%i\n",csbiInfo.dwSize.X);
	//printf("%i\n\n",csbiInfo.dwSize.Y);
}

void textcolor(short textcolor) {
	int color = (lastColor & 0xF0) | textcolor;
	setColor(color);
}

void textbackground(short bgcolor) {
	int color = (lastColor & 0xF) | (bgcolor << 4);
	setColor(color);
}

int last_x, last_y;
int gotoxy(int x, int y) {
	if(x < 1) {
		x = 1;
	}
	if(y < 1) {
		y = 1;
	}
	//Initialize the coordinates
	COORD coord = {x-1, y-1};
 	//Set the position
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 	last_x = x;
 	last_y = y;
 	return 0;
}

void clrscr() {
	COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void cputs(char* str)
{
    int beginning_x = last_x;

    while (*str != '\0')
    {
        if (*str == '\n')
        {
            gotoxy(last_x, last_y+1);
        }
        else if (*str == '\r')
        {
            gotoxy(beginning_x, last_y);
        }
        else if (*str == '\b')
        {
            gotoxy(last_x-1, last_y);
        }
        else
        {
            printf("%c", *str);

            gotoxy(last_x+1, last_y);
        }

        str++;
    }
}

bool hasSpecialChar = false;
char specialCharNum = '\0';
CHAR getch (VOID)
{
	if(hasSpecialChar) {
		hasSpecialChar = false;
		return specialCharNum;
	}
	
  HANDLE hStdin = GetStdHandle (STD_INPUT_HANDLE);
  INPUT_RECORD irInputRecord;
  DWORD dwEventsRead;
  CHAR cChar;

  while(ReadConsoleInputA (hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
    if (irInputRecord.EventType == KEY_EVENT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
    {
      cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
      if(cChar == 0) {
      	hasSpecialChar = true;
      	specialCharNum = char(irInputRecord.Event.KeyEvent.wVirtualScanCode);
      }
	  ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */
	  return cChar;
    }
  return EOF;
}
