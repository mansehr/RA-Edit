#define __VERSION__ 0.956

#include "conio.h"                                                                       //Inkluderar viktiga huvudbibliotek
#include "extra.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Include/Constvars.hpp"				//Inkluderar hemma-gjorda bibliotek
#include "Include/huvudram.cpp"
#include "Include/MenuBar.hpp"
#include "Include/EditorMenu.cpp"
#include "Include/Ruta.hpp"
#include "Include/String.hpp"
#include "Include/TextField.hpp"
#include "Include/TextEdit.hpp"

void 	menuAction();								//Funktioner
void	oppnaString();
void 	quit();
void 	runProgram();
void 	sparaString();

enum ProgStatus { Quit = 0, Init, Runing, Menu };
ProgStatus progStatus = Init;

TextEdit texten;

int main ()
{
	while(progStatus != Quit)					//Hoppar ur lopen om progStatus == quit
	{
		switch(progStatus)						// Vad ska programmet göra
		{
			case Init:								// Starta programmet
				clrscr();						// Rensa skärmen
				ritaRam();							// Rita ramen
				initMenu();							// Initiera menyn
				menuBar.drawGrund();				// Rita upp meny knapparna
				//-------------------------------------------------------
				//	Rita upp den nedre baren
				//-------------------------------------------------------
				{
					char bottom[80];
					int i = 0;
					for (;i < 79; i++)
					{
						bottom[i] = ' ';
					}
					bottom[i] = '\0';
					textbackground(7);
					gotoxy(1,25);
					cputs(bottom);
				}
				texten.draw(ALL);					// Rensar text delen.
				progStatus = Runing;				// Fortsätt kör programmet
			break;
			case Runing:							// Kör programmet
				runProgram();
			break;
			case Menu:								// Menyn är aktiv
				gotoxy(80,25);						//	När man är inne i menyn placerar vi pekaren längst ner i högra hörnet
				char key = getch();				// Vänta på knapptryckning
				if(key!=0)							// Ingen special knapp
				{
					menuBar.test(key);			// Skicka informationen vidare
					if(key == CHLEFT 	|| key == CHRIGHT  || key == ENTER 	|| key == CHOPENMENU ||
					 	key == CHLEFT1 || key == CHRIGHT1 || key == CHESC)
					{									// Ta bort den meny som inte längre är aktiv
						ritaRam(1);					// Rita översta raden på ramen
    					texten.drawRow(0, 6);	// Uppdatera texten
					}
					menuBar.drawUpdate();		// Rita om menyn
					menuAction();					// Har man tryckt på enter
				}
				if(menuBar.getStatus() == Null && progStatus != Quit)
				{										// Om menyn är nollställd
					progStatus = Runing;			// Fortsätt köra programmet
				}
				break;
		}
		texten.showPointer();					// Placera ut pekaren
	}
        return 0;
}

//----------------------------------------------------------
//	Har man tryck på menyn
//----------------------------------------------------------
void menuAction()
{
	if (miNytt.getStatus() == Pressed)		// Är nytt aktiv
	{
		texten.setToNull();						// Nollställ editorn
		texten.draw(ALL);							// Rensa allt
		miNytt.setStatus(Null);					// Nollställer menyItem
	}
	if (miOppna.getStatus() == Pressed)		// Är oppna aktiv
	{
		oppnaString();								// Oppna en fil
		texten.draw(ALL);							// Tar bort fönstret
		miOppna.setStatus(Null);				// Nollställer menyItem
	}
	if (miSpara.getStatus() == Pressed)		// Är spara aktiv
	{
		sparaString();								// Spara till en fil
		texten.draw(ALL);							// Tar bort fönstret
		miSpara.setStatus(Null);					// Nollställer menyItem
	}
	if	(miReadMe.getStatus() == Pressed)	// Är ReadMe aktiv
	{
		ifstream sparfil;							// Skapa ett filobjekt
		sparfil.open("ReadMe.txt");			// Försök öppna readMe.txt
		if (sparfil.fail())						// Misslyckades?
		{
			Popup oppna;							//	Skapa ett popupobjet för oppna rutan
			oppna.setRows(6);
			oppna.setCols(40);
			oppna.ritaRuta();
			oppna.printRubb(" ERROR ");
			oppna.printLine(1, "Kunde inte oppna 'ReadMe.txt'");	// Skriver ut felmeddelandet
			oppna.printLine(2,"Tryck på valfri tangent.");
			getch();									// Vänta på knapptryckning
		}
		else											// Det gick att öppna filen
		{
			texten.setToNull();					// Nollställer texten
			char TextBuffer[512];				// Skapar en textbuffert
			while(!sparfil.eof())				// Har vi nått slutet på filen
			{											// Om inte...
				sparfil.getline(TextBuffer, 512);// Kan vi läsa en rad till
				for(unsigned int i = 0; i < strlen(TextBuffer); i++)
					texten.putIn(TextBuffer[i]);// Kopiera in textbufferten på raden
				texten.addRow();					// Raden är slut
			}
			sparfil.clear();						// Tar bort eof biten
			sparfil.close();						// Stänger filen
		}
		texten.draw(ALL);
		miReadMe.setStatus(Null);					// Nollställer menyItem
	}
	if (miHelp.getStatus() == Pressed)		// Är hjälp aktiv
	{
		Popup hjalp;								// Ta fram popuprutan
		hjalp.setRows(11);
		hjalp.setCols(43);
		hjalp.ritaRuta();
		hjalp.printRubb(" OM EDITORN ");
		hjalp.printLine(1,"Denna editor är utvecklad av Andreas Sehr");
		hjalp.printLine(2,"och Rickard Lindberg under jullovet 2002.");
		hjalp.printLine(4,"Ni når oss via mail: ");
		hjalp.printLine(5,"ande_vega@hotmail.com & webmaster@ricki.nu");
		hjalp.printLine(7,"Version: Beta 0.956");

		getch();										// Vänta på knapptryckning
		texten.draw(ALL);							//Tar bort fönstret
		miHelp.setStatus(Null);					// Nollställer menyItem
	}
	if (miAvsluta.getStatus() == Pressed)	// Är Avsluta aktiv
	{
		quit();										// Avsluta!
	}
}

//----------------------------------------------------------
//	Öppna texten
//----------------------------------------------------------
void oppnaString ()
{
	ifstream sparfil;

	Popup oppna;									//	Skapa ett popupobjet för oppna rutan
	oppna.setRows(7);
	oppna.setCols(40);
	oppna.ritaRuta();
	oppna.printRubb(" Oppna FIL ");
	oppna.printLine(1,"Filnamn: ");

	TextField fileName;							//	Skapa ett textfält där man kan skriva in ett filnamn
	fileName.setWidth(15);
	fileName.setTop(oppna.getActiveRow());
	fileName.setLeft(oppna.getActiveCol());
	fileName.isActive();							// Den blir aktiv så att man kan skriva i den

	sparfil.open(fileName.getString());		// När man tryck på enter försöker vi öppna filen
	if (sparfil.fail())							// Misslyckades
	{
		String tempString;						// Skapa ett strängobjekt som är lättare att arbeta med
		tempString = tempString + "Kunde inte oppna '" + fileName.getString() + "'";
		oppna.printLine(2, tempString.getString());	// Skriver ut felmeddelandet
		oppna.printLine(3,"Tryck på valfri tangent.");
		getch();										// Vänta på knapptryckning
		return;										// Hoppa ur funktionen
	}
	else												// Det gick att öppna filen
	{
		texten.setToNull();						// Nollställer texten
		char TextBuffer[512];					// Skapar en textbuffert
		while(!sparfil.eof())					// Har vi nått slutet på filen
		{												// Om inte...
			sparfil.getline(TextBuffer, 512);// Kan vi läsa en rad till
			for(unsigned int i = 0; i < strlen(TextBuffer); i++)
				texten.putIn(TextBuffer[i]);	// Kopiera in textbufferten på raden
			texten.addRow();						// Raden är slut
		}
		sparfil.clear();							// Tar bort eof biten
		sparfil.close();							// Stänger filen

		oppna.printLine(2,"Filen är Oppnad.");// Skriv ut att det löstes utan problem
		oppna.printLine(3,"Tryck på valfri tangent.");

		getch();										// Väntar på knapptryckning
		return;										// Hoppar ur funktionen
	}
}

//----------------------------------------------------------
//	Avslutar programmet
//----------------------------------------------------------
void quit()
{
	progStatus = Quit;							// Avsluta
	clrscr();									// Rensa skärmen
}

//----------------------------------------------------------
//	Funktionen som körs när TextEdit objektet är aktivt
//----------------------------------------------------------
void runProgram()
{
	char key = getch();							// Vänta på knapptryckning från tangentbordet

	switch(key)
	{
		case CHESC:									// Man tryckte på ESC	(Öppna menyn)
		case CHOPENMENU:							// Man tryckte på öppna meny knappen
			menuBar.test(key);					// Testar meny knappen == sätter menyn till aktiv
			menuBar.drawUpdate();				// Rita den uppdaterade menyn
			progStatus = Menu;					// Menyn är aktiv
		return;										// Ska inte testa att skriva knappen.

		default:										// Annars
			texten.testKey(key);					// Testa knapptryckningen, och rita uppdateringen
		break;
	}
}

//----------------------------------------------------------
//	Spara texten
//----------------------------------------------------------
void sparaString ()
{
	ofstream sparfil;								// Skapa ett filobjekt

	Popup spara;									//	Skapa ett popupobjet för spara rutan
	spara.setRows(7);
	spara.setCols(40);
	spara.ritaRuta();
	spara.printRubb(" SPARA FIL ");
	spara.printLine(1,"Filnamn: ");

	TextField fileName;							//	Skapa ett textfält där man kan skriva in ett filnamn
	fileName.setWidth(15);
	fileName.setTop(spara.getActiveRow());
	fileName.setLeft(spara.getActiveCol());
	fileName.isActive();							// Den blir aktiv så att man kan skriva i den

	sparfil.open(fileName.getString());		// När man tryck på enter försöker vi öppna filen
	if (sparfil.fail())							// Misslyckades
	{
		String tempString;						// Skapa ett strängobjekt som är lättare att arbeta med
		tempString = tempString + "Kunde inte oppna '" + fileName.getString() + "'";
		spara.printLine(2, tempString.getString());	// Skriver ut felmeddelandet
		spara.printLine(3,"Tryck på valfri tangent.");
		getch();										// Vänta på knapptryckning
		return;										// Hoppa ur funktionen
	}
	else												// Det gick att öppna filen
	{
		sparfil << texten.getAllRows();		// Spara ALLA rader ifrån texten
		sparfil.close();							// Stäng filen

		spara.printLine(2,"Filen är sparad.");	// Skriv ut att det löstes utan problem
		spara.printLine(3,"Tryck på valfri tangent.");

		getch();										// Vänta på knapptryckning
		return;										// Hoppa ur programmet
	}
}
