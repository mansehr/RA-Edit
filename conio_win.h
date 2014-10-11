
#include <windows.h>
#include <stdio.h>
#include <iostream>


#define DARKGRAY	0x7
#define WHITE 		0xF
#define BLACK		0x0
#define BLUE		0x9

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

void textcolor(int textcolor) {
	int color = (lastColor & 0xF0) | textcolor;
	setColor(color);
}

void textbackground(int bgcolor) {
	int color = (lastColor & 0xF) | (bgcolor << 4);
	setColor(color);
}

int lastX, lastY;
void gotoxy(int x, int y) {
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
 	lastX = x;
 	lastY = y;
 	return;
}

void clearscreen() {
	
}

void cputs(char* out) {
	char ch;
	do {
		ch = *out;
		if(ch == '\n') {
			gotoxy(lastX, lastY+1);
		} else if(ch == '\r' || ch == '\b') {
			// ignore
		} else {
			printf("%c", ch);
		}
		++out;
	} while(ch != '\0');
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
	/*&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL*/)
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
