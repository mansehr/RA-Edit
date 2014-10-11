			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "ADMenuBar.hpp"						//
			//														//
			//			Författad av: Andreas Sehr 2001,10,17		//
			//														//
			//			Senast ändrad:	2002,12,05					//
			//														//
			//////////////////////////////////////////////////////////
#ifndef __ADMenuBarhpp__
#define __ADMenuBarhpp__

#include "Constvars.hpp"
#include "Menu.hpp"
//----------------------------------------------------------
//	MenuBar: Har hand om alla Menu objekt. Sätter variablerna
// till dessa när de läggs till i listan. Använd funktionen
// drawGrund för att rita upp allting. DrawUpdate för att rita
// när något är aktivt. Objektet kan inte rensa sina menyer själv.
// Måste ha hjälp för att ta bort menyer som varit aktiva.
//----------------------------------------------------------
class MenuBar : public Objekt
{
	public:
		MenuBar();

		void 	add 			(Menu &initMenu);
		void 	drawGrund	();
		void 	drawUpdate	();
		int 	getEnd		() 	const { return right; }
		int 	getMenuAntal() 	const { return mAntal; }
		void 	test			(char initKey);

	private:
		Menu 	*menu[15];
		Menu 	*activeMenu;
		int 	iAktiveMenu;
		int 	mAntal;
		Status menuStatus;
};
//----------------------------------------------------------
//	MenuBar grund konstruktor.
// Sätter värden till alla variabler så att det inte blir något minnesfel
//----------------------------------------------------------
MenuBar::MenuBar() : Objekt()
{
	mAntal 		= 0;									// Inga under menyer har lagts till än
	top 			= 1;									// Den rad som objektet är på
	left 			= 1;									// Allt ska vara lika med 1 så att allt kommer
	right 		= 1;									// innanför skärmen när man annvänder gotoxy(int x, int y)
	menuStatus 	= Null;								// Objektet är inte aktivt på nåt sätt
	activeMenu 	= 0;									// Ingen under meny finns som kan vara aktiv
	iAktiveMenu = 0;									// -||-
	for(int i = 0; i < 15; i++)
		menu[i] = 0;									// Rensar minnet
}

//----------------------------------------------------------
//	Här läggs alla Menu objekt till. Alla värden sätts. Även
// nere på MenuItem nivå
//----------------------------------------------------------
void MenuBar::add(Menu &initMenu)
{
	int i = mAntal;									//Vilken knapp i vektorn
	menu[i] = &initMenu;								//Jobba med objektet
//Knappen
	menu[i]->setTop(top);							// Sätter knappens rad som den är på
	menu[i]->setLeft(right+1);						// Sätter kanppens vänstra pos
	menu[i]->setRight(menu[i]->getLeft() + menu[i]->getWidth());	// Räknar ut och sätter knappens högra del
//Menyn bakgrunden under menyItem
	menu[i]->setMenuTop(top+2);
	menu[i]->setMenuBottom(top+2);
	menu[i]->setMenuLeft(menu[i]->getLeft()+1);
	menu[i]->setMenuRight(menu[i]->getMenuLeft() + menu[i]->getMenuWidth());
//Uppdatera menyItem värdena i meny Objektet
	for (int z = 0; z < menu[i]->getMenuItemAntal(); z++)
	{
		menu[i]->menuItem[z]->setTop( menu[i]->menuItem[z]->getTop()+this->getTop()+1);
		menu[i]->menuItem[z]->setLeft( menu[i]->getLeft() + 1 );
		menu[i]->menuItem[z]->setRight( menu[i]->getMenuRight() - 1);
	}
	right = menu[i]->getRight()+1;				//MenuBar ny höger
	mAntal++;											//Öka Antalet objekt
}

void MenuBar::drawGrund()
{
//Den tomma gråa raden
	char tom[81];
	for(int i = 0; i < getWidth(); i++)
		tom[i] = ' ';
	tom[getWidth()] = '\0';
	textbackground(MBARBG);
	gotoxy(getTop(),getLeft());
	cputs(tom);

	drawUpdate();										//Knapparna och activa menyer
}

void MenuBar::drawUpdate()
{
	//Rita menyerna
	for ( int i = 0; i < mAntal; ++i)
	{
		menu[i]->draw();
	}
}

void MenuBar::test(char initKey)
{
	if(initKey == ENTER)								//ENTER
	{
		this->setStatus(Null);						// Nollställ menyBar
		activeMenu->setNotActive();				// Nollställ menyn
		if(activeMenu != 0 && activeMenu->activeMenuItem != 0)// Testar om de pekar på något objekt
			activeMenu->activeMenuItem->test(initKey);			// Testar om vi kan sätta menyItem Pressed
	}


	if(initKey == CHOPENMENU || initKey == CHESC)						//Visa menu
		if(this->getStatus() != Active)			// Om menuBar INTE ÄR aktiv blir den det
		{
			this->setStatus(Active);				// menuBar blir aktiv
			iAktiveMenu = 0;							// Första menynObjektet (Längst till vänster)
			activeMenu = menu[iAktiveMenu];		// AktiveMenu pekaren pekar på det aktiva objektet
			activeMenu->setActive();				// Första menyn blir aktiv
		}
		else
		{
			this->setStatus(Null);					// Nollställer menyBar
			activeMenu->setNotActive();;			// Nollställer menyn
			if(activeMenu->activeMenuItem != 0)
				activeMenu->activeMenuItem->setStatus(Null);
		}

	if(initKey == CHRIGHT || initKey == CHRIGHT1)//Pil höger
		if(this->getStatus() == Active)			// Om menuBar ÄR aktiv
		{
			iAktiveMenu += 1;							// Flytta höger
			if(iAktiveMenu >= mAntal)				// Utanför listan?
				iAktiveMenu = 0;						// Första objektet blir aktivt
			activeMenu->setNotActive();			// Nollställ gamla objektet
			if(activeMenu->activeMenuItem != 0)
				activeMenu->activeMenuItem->setStatus(Null);
			activeMenu = menu[iAktiveMenu];		// AktiveMenu pekaren pekar på det aktiva objektet
			activeMenu->setActive();				// Det nya aktiva objektet blir aktivt
		}

	if(initKey == CHLEFT || initKey == CHLEFT1)//Pil Vänster
		if(this->getStatus() == Active)			// Om menuBar ÄR aktiv
		{
			iAktiveMenu -= 1;							// Flytta vänster
			if(iAktiveMenu < 0)						// Utanför listan?
				iAktiveMenu = mAntal-1;				// Sista objektet blir aktivt
			activeMenu->setNotActive();			// Nollställ gamla objektet
			if(activeMenu->activeMenuItem != 0)
				activeMenu->activeMenuItem->setStatus(Null);
			activeMenu = menu[iAktiveMenu];		// AktiveMenu pekaren pekar på det aktiva objektet
			activeMenu->setActive();				// Det nya aktiva objektet blir aktivt
		}

	if(initKey == CHUP || initKey == CHUP1)	//Pil Upp
		if(this->getStatus() == Active)			//Om menuBar ÄR aktiv
			activeMenu->moveUp();					// Flytta upp i menyn

	if(initKey == CHDOWN || initKey == CHDOWN1)//Pil Ner
		if(this->getStatus() == Active)			//Om menuBar ÄR aktiv
			activeMenu->moveDown();					// Flytta ner i menyn
}

#endif /*__ADMenuBar.hpp__*/
