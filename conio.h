// Copyright (C) 2005  by Piotr He³ka (piotr.helka@nd.e-wro.pl)
// Linux C++ (not full) implementation of Borland's conio.h 
// v 1.01
// It uses Ncurses lib, so accept also its terms.



// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// ----------------------------- krotki opis ------------------

// Biblioteka obs³uguje mniej lub bardziej zgodnie:
//
// cgets()
// cputs()
// clreol()
// clrscr()
// cprintf()
// cscanf()
// getch() (chyba nie wszystkie kody tak jak w conio.h)
// getche()  
// gotoxy()
// kbhit()
// putch()
// textbackground()
// textcolor()
// wherex()
// wherey()
// window()
//
// kompatbyilno¶æ w kierunku Linux CONIO.H -> DOS CONIO.H
// bedzie zachowana

// Aby skompilowac
// $g++ nazwa_progsa.cpp -lncurses -o nazwa_progsa.o

// ------------------------------- define ---------------------

#ifndef __NCURSES_H
#include <ncurses.h>
#endif

#ifndef __CONIO_H
#define __CONIO_H
#endif

#define MAX_OKIEN 256

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

// -------------------------------- globalne ------------------

//int (* wsk_f)(void) = getch;

#undef getch
#define getch CURSgetch

#undef getche
#define getche CURSgetche


int last_x = 1;
int last_y = 1;

void inicjuj();

class Startuj   // konstruktor i destruktor klasy beda odpowiedzalni
{	public:     // za automagiczna inicjalizacje ustawien ;-)
	Startuj(){ inicjuj(); }
	~Startuj(){ endwin(); }
} Start;	    			// inicjuj!

typedef struct
{
	int 	xup;
	int 	yup;
	int 	xdown;
	int 	ydown;
	WINDOW*	okno;
} Okno;

bool	zainicjowane = FALSE; //czy juz po initscr() ?
int	znakSpecjalny = -1; //potrzebne do getch'a
int	n = 0; //liczba uzytych okienek

short	kolorTekstu = COLOR_WHITE;
short	kolorTla = COLOR_BLACK;
short	biezacaPara;

Okno	okienka[MAX_OKIEN];	//tablica struktur aktywnych okienek
WINDOW*	aktywneOkno = NULL;	//wsk na aktywne okno
    
    

// ----------------------------- koniec globalnych ------------

void inicjuj()
{
	initscr();
	start_color(); //wlaczmy kolorki
	cbreak(); //wylaczmy buforowanie wejscia
	noecho(); //bez wyswietlania na ekran
	//raw(); //nadpisywane i tak przez noecho
	keypad(stdscr, TRUE);
	scrollok(stdscr, TRUE);
	
	//domyslne okno
	aktywneOkno = stdscr;
	zainicjowane = TRUE;
	
	//utworzmy macierz 8x8 kolorow tla i tekstu
	short kolor = 1;
	for(short i=0; i<8; i++)
	{
		for(short j=0; j<8; j++, kolor++)
		{
			init_pair(kolor,i,j);
			if(i == COLOR_WHITE && j == COLOR_BLACK)	
			//ustawmy czarne tlo i bialey tekst jako standard
			{
				biezacaPara = kolor;
			}  
		}
	}
	
	wrefresh(aktywneOkno);
}

int simple_strlen(char* str)
{
	char* p;
	for(p = str; *p != 0; p++);
	return p-str;
}

int gotoxy(int x, int y);

short get_color_attr(void)
{
    short kolor = 1;
    for(short i=0; i<8; i++)
    {
        for(short j=0; j<8; j++, kolor++)
        {
            init_pair(kolor,i,j);
            if(i == kolorTekstu && j == kolorTla)
            {
                return COLOR_PAIR(kolor);
            }
        }
    }

    return 0;
}

void cputs(char* str)
{
    int beginning_x = last_x;

    attron(get_color_attr());

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
            char buf[] = {*str, '\0'};
            waddstr(aktywneOkno, buf);

            gotoxy(last_x+1, last_y);
        }

        str++;
    }

    wrefresh(aktywneOkno);

    attroff(get_color_attr());
}

char* cgets(char* str)
{ // nie wiem dokladnie jak dziala orginalna f. cgets bo nie mam
  // do niej referencji..
	if(str == NULL || *str == 0)
	{
		*(str+1) = 0;
		return NULL;
	}
	
	int max = (int)(*str);
	
	echo();
	
	if(wgetnstr(aktywneOkno, (str + 2), max) == ERR)
	{
		*(str+1) = 0;
		return NULL;
	}
	
	noecho();
	
	*(str+1) = (char)simple_strlen(str+2);
	
	return str+2;
}

void clreol()
{
	wclrtoeol(aktywneOkno);
	wrefresh(aktywneOkno);
}

void clrscr()
{
	if(!zainicjowane) inicjuj();
	wbkgd(aktywneOkno, COLOR_PAIR(biezacaPara));
	//trzeba przesunac kursor? chyba nie...
	wclear(aktywneOkno);
}

int cprintf(char *fmt, ...)
// czysty hardcore ;-)
{
	if(!zainicjowane) inicjuj();
	
	va_list ap; 
	va_start(ap, fmt);
	
        int i = vwprintw(aktywneOkno,fmt, ap);	//jakie proste ;-)
	
	va_end(ap);
	
	wrefresh(aktywneOkno);
	
	return i;
}

int cscanf(char *fmt, ...)
{
	if(!zainicjowane) inicjuj();
	
	echo();
	
	va_list ap;
	va_start(ap, fmt);
	
	int i = vwscanw(aktywneOkno, fmt, ap);
	
	va_end(ap);
	
	wrefresh(aktywneOkno);
	noecho();
	
	return i;
}

int CURSgetch()
{
	if(!zainicjowane) inicjuj();
	
	int znak;
	
	if(znakSpecjalny>0) //drugi czlon znaku specjalnego 0x00 i 0x??
	{
		//zamieniamy znak na kod DOSowy - conio.h
		znak = znakSpecjalny;
		znakSpecjalny = -1;
			
		return znak-265+59;
	}

	znak = wgetch(aktywneOkno);
	
	if(znak > 255) //to mamy znak specjalny 0x00
	{
		znakSpecjalny = znak;
		return 0;
	}

	return znak;
}

int CURSgetche()
{
	echo();
	int znak = getch();
	noecho();
	return znak;
}

int gotoxy(int x, int y)
{
        last_x = x;
        last_y = y;
	if(!zainicjowane) inicjuj();
	wmove(aktywneOkno, y - 1, x - 1);
	return 0;
}

int kbhit()
{
	int znak;
	wtimeout(aktywneOkno, 0);
	znak = wgetch(aktywneOkno);
	//wtimeout(aktywneOkno, -1);
	nodelay(aktywneOkno, FALSE);
	if (znak == ERR) return 0;
	ungetch(znak);
	return 1;
}

int putch(int znak)
{
	wechochar(aktywneOkno,znak);
}

void textbackground(short kolor)
{
    kolorTla = kolor%8;
}

void textcolor(short kolor)
{
    kolorTekstu = kolor%8;
}

int wherex(void)
{
	if(!zainicjowane) inicjuj();
	int x, y;
	getyx(aktywneOkno, y, x);
	return x + 1;
}

int wherey(void)
{
	if(!zainicjowane) inicjuj();
	int x, y;
	getyx(aktywneOkno, y, x);
	return y + 1;
}
