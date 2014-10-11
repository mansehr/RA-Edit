////////////////////////////////////////////////////////////
//																			 //
//		Fil: "ram.cpp"												 	 //
//																			 //
//		Författad av: Rickard Lindberg, 2002-12-16			 //
//																			 //
//		Beskrivning: Denna fil innehåller en funktion som	 //
//						 skriver ut huvudramen. 					 //
//																			 //
////////////////////////////////////////////////////////////

#include <cstring>

void ritaRam(int rows = ROWS-1)		// Rita antalet rader från toppen är som standard höjd minus 1
{											// Går att skicka egna värden...
	// Definera fönstrets storlek
	const int MAX_COLUMNS = COLUMNS-2;
	const int MAX_ROWS = ROWS-1;

	// Definera ram-vektorn, titeln och räknaren
	char ram[1 + (MAX_COLUMNS+4)*MAX_ROWS];
	char * titel = " RA Editor - Beta " __VERSION_STR__ " ";
	int counter = 0;

	// Loopa igenom varje rad
	for (int i=1;i<=rows;i++)
	{
		// Om det är första raden ska något spec skrivas ut
		if (i==1)
		{
			ram[counter++] = LUCORNER;

			for (unsigned int j=1;j<=MAX_COLUMNS;j++)
			{
				ram[counter++] = VAGRAT;

				// Räkna ut positionen där rubriken ska börja skrivas ut
				if (j==((MAX_COLUMNS/2)-(strlen(titel)/2)))
				{
					// Printa ut rubriken
					for (unsigned int k=0;k<strlen(titel);k++)
					{
						ram[counter++] = titel[k];
					}

					j+=strlen(titel);
				}
			}

			ram[counter++] = RUCORNER;
			ram[counter++] = '\r';
			ram[counter++] = '\n';
		}
		// Om det är sista raden ska något spec skrivas ut
		else if (i==MAX_ROWS)
		{
			ram[counter] = LBCORNER; counter++;

			for (int j=1;j<=MAX_COLUMNS;j++)
			{
				ram[counter++] = VAGRAT;
			}

			ram[counter++] = RBCORNER;
			ram[counter++] = '\r';
			ram[counter++] = '\n';
		}
		// Om det är en "vanlig rad skriver vi ut detta"
		else
		{
			ram[counter++] = LODRAT;

			for (int j=1;j<=MAX_COLUMNS;j++)
			{
				ram[counter++] = ' ';
			}

			ram[counter++] = LODRAT;
			ram[counter++] = '\r';
			ram[counter++] = '\n';
		}
	}
	// Här slutar vektorn
	ram[counter] = '\0';

	textbackground(BLACK);
	textcolor(WHITE);
	gotoxy(1,2);
	cputs(ram);
}
