////////////////////////////////////////////////////////////
//																			 //
//		Fil: "ram.hpp"												 	 //
//																			 //
//		Författad av: Rickard Lindberg, 2002-12-16			 //
//																			 //
//		Beskrivning: Denna fil innehåller en klass som		 //
//						 skriver ut en enkel ram. 					 //
//																			 //
////////////////////////////////////////////////////////////

/*
Ram ram;
ram.setRows(7);
ram.setCols(40);
ram.setLeft(30);
ram.setTop(2);
ram.printRam();
*/

class Ram
{
	private:

		int rows;	// Antal rader i ramen
		int cols;	// Antal columner i ramen
		int top;		// Y-position där ramen skall börja skrivas ut
		int left;	// X-position där ramen skall börja skrivas ut

	public:

		void printRam ();

		void setRows(int rader)
		{
			rows = rader;
		}

		void setCols(int kolumner)
		{
			cols = kolumner;
		}

		void setTop(int y)
		{
			top = y;
		}

		void setLeft(int x)
		{
			left = x;
		}
};

//----------------------------------------------------------
//	Rita upp ramen
//----------------------------------------------------------
void Ram::printRam ()
{
	char ram[2000];

	//-------------------------------------------------------
	//	Håller reda på vilken position i arrayen vi ska
	// mata in ett tecken på
	//-------------------------------------------------------
	int counter = 0;

	//-------------------------------------------------------
	//	Lagra ramen i en array
	//-------------------------------------------------------
	for (int i=1;i<=rows;i++)
	{
		//----------------------------------------------------
		//	Om det är första raden ska en sak lagras
		//----------------------------------------------------
		if (i==1)
		{
			ram[counter++] = TLUCORNER;

			for (int j=1;j<=cols;j++)
			{
				ram[counter++] = TVAGRAT;
			}

			ram[counter++] = TRUCORNER;
			ram[counter++] = '\n';

			//-------------------------------------------------
			//	Efter radbrytningen backar vi så många steg som
			// vi har antal kolumner+2 (ramkanterna)
			//-------------------------------------------------
			for (int k=0;k<cols+2;k++)
			{
				ram[counter++] = '\b';
			}
		}
		//----------------------------------------------------
		//	Om det är sista raden ska en annan sak lagras
		//----------------------------------------------------
		else if (i==rows)
		{
			ram[counter++] = TLBCORNER;

			for (int j=1;j<=cols;j++)
			{
				ram[counter++] = TVAGRAT;
			}

			ram[counter++] = TRBCORNER;
			ram[counter++] = '\n';
		}
		//----------------------------------------------------
		//	Om det är en vanlig rad lagrar vi detta
		//----------------------------------------------------
		else
		{
			ram[counter++] = TLODRAT;

			for (int j=1;j<=cols;j++)
			{
				ram[counter++] = ' ';
			}

			ram[counter++] = TLODRAT;
			ram[counter++] = '\n';

			//-------------------------------------------------
			//	Efter radbrytningen backar vi så många steg som
			// vi har antal kolumner+2 (ramkanterna)
			//-------------------------------------------------
			for (int k=0;k<cols+2;k++)
			{
				ram[counter++] = '\b';
			}
		}
	}
	//-------------------------------------------------------
	//	Här slutar ramvektorn
	//-------------------------------------------------------
	ram[counter] = '\0';

	//-------------------------------------------------------
	//	Skriv ut ramen
	//-------------------------------------------------------
	gotoxy(left,top);
	textbackground(7);	// Grå bg
	textcolor(0);			// Svart text
	cputs(ram);
}

