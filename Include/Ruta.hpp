////////////////////////////////////////////////////////////
//																			 //
//		Fil: "ruta.hpp"												 //
//																			 //
//		Författad av: Rickard Lindberg, 2002-12-16			 //
//																			 //
//																			 //
//		Beskrivning: Denna fil innehåller en klass som		 //
//						 skriver ut en popupruta. Man kan		 //
//						 sedan enkelt lägga till rubrik och		 //
//						 text i rutan med hjälp av metoder.		 //
//																			 //
////////////////////////////////////////////////////////////

class Popup
{
	private:

		int rows;	// Antal rader i rutan
		int cols;	// Antal columner i rutan
		int activeRow;
		int activeCol;
		int top;		// Y-position där rutan skall börja skrivas ut
		int left;	// X-position där rutan skall börja skrivas ut

	public:

		void ritaRuta ();

		void setRows(int rader)
		{
			rows = rader;
		}

		void setCols(int kolumner)
		{
			cols = kolumner;
		}

		int getActiveRow()
		{
			return activeRow;
		}

		int getActiveCol()
		{
			return activeCol;
		}

		//----------------------------------------------------
		//	Skriver ut en centrerad rubrik på första raden
		//----------------------------------------------------
		void printRubb(char * text)
		{
			gotoxy(left+(cols/2)-strlen(text)/2,top);
			cputs(text);
			gotoxy(80,25);
		}

		//----------------------------------------------------
		//	Skriver ut en text på rad X
		//----------------------------------------------------
		void printLine(int rad, char * text)
		{
			textbackground(1);	// Blå bg
			textcolor(15);			// Vit text
			gotoxy(left+2,top+1+rad);

			activeRow = top+1+rad;
			activeCol = left+2+strlen(text);

			cputs(text);
			gotoxy(80,25);
		}
};

//----------------------------------------------------------
//	Rita upp popup-rutan med skugga
//----------------------------------------------------------
void Popup::ritaRuta ()
{
	char ruta[2000];
	char skugga[2000];

	//-------------------------------------------------------
	//	Håller reda på vilken position i arrayen vi ska
	// mata in ett tecken på
	//-------------------------------------------------------
	int counter = 0;

	//-------------------------------------------------------
	//	Lagra skuggan i en array
	//-------------------------------------------------------
	for (int i=1;i<=rows;i++)
	{
		for (int j=1;j<=cols+2;j++)
		{
			skugga[counter++] = ' ';
		}

		skugga[counter++] = '\n';

		//----------------------------------------------------
		//	Efter radbrytningen backar vi så många steg som
		// vi har antal kolumner+2 (ramkanterna)
		//----------------------------------------------------
		for (int k=0;k<cols+2;k++)
		{
			skugga[counter++] = '\b';
		}
	}
	//-------------------------------------------------------
	//	Här slutar skuggvektorn
	//-------------------------------------------------------
	skugga[counter] = '\0';
	counter = 0;

	//-------------------------------------------------------
	//	Lagra fönstret i en array
	//-------------------------------------------------------
	for (int i=1;i<=rows;i++)
	{
		//----------------------------------------------------
		//	Om det är första raden ska en sak lagras
		//----------------------------------------------------
		if (i==1)
		{
			ruta[counter++] = LUCORNER;

			for (int j=1;j<=cols;j++)
			{
				ruta[counter++] = VAGRAT;
			}

			ruta[counter++] = RUCORNER;
			ruta[counter++] = '\n';

			//-------------------------------------------------
			//	Efter radbrytningen backar vi så många steg som
			// vi har antal kolumner+2 (ramkanterna)
			//-------------------------------------------------
			for (int k=0;k<cols+2;k++)
			{
				ruta[counter++] = '\b';
			}
		}
		//----------------------------------------------------
		//	Om det är sista raden ska en annan sak lagras
		//----------------------------------------------------
		else if (i==rows)
		{
			ruta[counter++] = LBCORNER;

			for (int j=1;j<=cols;j++)
			{
				ruta[counter++] = VAGRAT;
			}

			ruta[counter++] = RBCORNER;
			ruta[counter++] = '\n';
		}
		//----------------------------------------------------
		//	Om det är en vanlig rad lagrar vi detta
		//----------------------------------------------------
		else
		{
			ruta[counter++] = LODRAT;

			for (int j=1;j<=cols;j++)
			{
				ruta[counter++] = ' ';
			}

			ruta[counter++] = LODRAT;
			ruta[counter++] = '\n';

			//-------------------------------------------------
			//	Efter radbrytningen backar vi så många steg som
			// vi har antal kolumner+2 (ramkanterna)
			//-------------------------------------------------
			for (int k=0;k<cols+2;k++)
			{
				ruta[counter++] = '\b';
			}
		}
	}
	//-------------------------------------------------------
	//	Här slutar popupvektorn
	//-------------------------------------------------------
	ruta[counter] = '\0';

	//-------------------------------------------------------
	//	Räkna ut x och y för centrering
	// (punkt uppe i vänstra hörnet)
	//-------------------------------------------------------
	top	= 12-(rows/2);
	left	= 40-(cols/2);

	//-------------------------------------------------------
	//	Skriv ut skuggan
	//-------------------------------------------------------
	gotoxy(left+1,top+1);
	textbackground(7); // Grå färg på skuggan
	cputs(skugga);

	//-------------------------------------------------------
	//	Skriv ut rutan ovanpå skuggan
	//-------------------------------------------------------
	gotoxy(left,top);
	textbackground(1);	// Blå bg
	textcolor(15);			// Vit text
	cputs(ruta);
}

