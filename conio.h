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

#undef getch
#define getch CURSgetch

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

short	kolorTekstu = COLOR_WHITE;
short	kolorTla = COLOR_BLACK;
short	biezacaPara;

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

int gotoxy(int x, int y)
{
    last_x = x;
    last_y = y;
    if(!zainicjowane) inicjuj();
    wmove(aktywneOkno, y - 1, x - 1);
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

void clrscr()
{
    if(!zainicjowane) inicjuj();
    wbkgd(aktywneOkno, COLOR_PAIR(biezacaPara));
    //trzeba przesunac kursor? chyba nie...
    wclear(aktywneOkno);
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

        switch (znak)
        {
            case KEY_DOWN:
                return 80;
            case KEY_UP:
                return 72;
            case KEY_LEFT:
                return 75;
            case KEY_RIGHT:
                return 77;
            default:
                return znak-265+59;
        }
    }

    znak = wgetch(aktywneOkno);

    if(znak > 255) //to mamy znak specjalny 0x00
    {
        znakSpecjalny = znak;
        return 0;
    }

    if (znak == 10)
    {
        return 13;
    }
    else
    {
        return znak;
    }
}

void textbackground(short kolor)
{
    kolorTla = kolor % 8;
}

void textcolor(short kolor)
{
    kolorTekstu = kolor % 8;
}
