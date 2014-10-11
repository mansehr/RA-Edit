
#include <windows.h>
#include <stdio.h>
#include <iostream>


#define DARKGRAY	1
#define WHITE 		1
#define BLACK		1
#define BLUE		1
#define DARKGRAY	1

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
void setColor(int color) {
	//SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}

void textcolor(int textcolor) {
	setColor(textcolor);
}

void textbackground(int bgcolor) {
	setColor(bgcolor);
}

void gotoxy(int x, int y) {
	//Initialize the coordinates
	COORD coord = {x-1, y-1};
 	//Set the position
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 	return;
}

void cputs(char* out) {
	std::cout << out;
}

CHAR getch (VOID)
{
	
	if(false)
		return 'a';
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
	ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */
	return cChar;
    }
  return EOF;
}
