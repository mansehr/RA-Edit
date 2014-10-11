			////////////////////////////////////////////////////////
			//																		//
			//			Fil: "TextEdit.hpp"									//
			//																		//
			//			Författad av: Andreas Sehr 2002,01,19			//
			//																		//
			//			Senast ändrad:	2002,01,19							//
			//																		//
			//			Innehåll: Klasser till editor programmet		//
			//																		//
			////////////////////////////////////////////////////////
#ifndef __ADTextEdit.hpp__
#define __ADTextEdit.hpp__

#include "String.hpp"
#include "TextObjekt.hpp"

const int MAX_BREDD = COLUMNS-2; //Tar bort kanterna (78)
const int RADER = ROWS-3;	//Tar bort meny och kanter

enum DrawRow { ALL, ACTIVE_ROW};

class TextEdit
{
public:
	TextEdit();
	~TextEdit();

	void 	addRow		();
	void 	baksteg		();
	void 	del			();
	void 	delActiveRow() 						{ delRow(activeRow); }
	bool 	deleteChar	(int initInt) 	const	{ return row[activeRow]->deleteChar(initInt); }
	void 	delRow		(int initRow);
	void 	draw			(DrawRow whatToDraw);
	void 	drawRow		(int row);
	void 	drawRow		(int startRow, int endRow);
	void 	enter			();
	int 	getActiveRow() { return activeRow; }
	char* getAllRows	();
	char 	getChar		(int initLoc) 	const	{ return row[activeRow]->getChar(initLoc); }
	int 	getLocOnRow	() 				const	{ return row[activeRow]->getLocOnRow(); }
	char* getString	() 				const	{ return row[activeRow]->getString();}
	void 	left			();
	void 	moveUpRow	(int initRow);			// Sätta ihop två rader, den som ligger före initRow
	bool 	ner			();
	void 	putIn			(char initChar);
	void 	right			();
	void 	showPointer	();
	void 	setToNull	();
	void 	testKey		(char initKey);
	void 	upp			();

private:
	void 	moveBack();
	void 	moveForward();
	void 	printRowColumn();

	int 						activeRow;
	int 						antRow;
	String 					helaFilen;
	vector<TextObjekt*> 	row;
	int 						visualStartRow;
};

TextEdit::TextEdit()
{
	activeRow 		= 0;
	antRow 			= 0;
	visualStartRow = 0;
	row.push_back(new TextObjekt());
	row[antRow]->setWidth(MAX_BREDD-1);
}

TextEdit::~TextEdit()
{
	for(int i = 0; i <= antRow; i++)
	{
		delete row[i];
		row[i] = 0;
	}
}

void TextEdit::addRow()
{
	row.push_back(new TextObjekt(*row[antRow]));	// Skapar ett nytt TextObjekt kommer sist i vektorn
	antRow += 1;											// En till rad
	for(int i = antRow; i > activeRow; i--)		// Flytta ner alla rader som kommer efter den
	{															// den nya aktiva raden
		row[i]->clone(*row[i-1]);						// Kopierar
	}

	activeRow += 1;										// Man har hoppat ner en rad, ökar activeRow
	row[activeRow]->setToNull();						// Nollställer raden
	row[activeRow]->setWidth(MAX_BREDD-1);			// Sätter MAX_BREDD efter att man nollställt

	if(activeRow+1 > visualStartRow+RADER)			// Är det för många objekt som ska ritas upp?
		visualStartRow++;									// Då flyttar vi upp alla rader ett steg
}

void TextEdit::baksteg()
{
	if(row[activeRow]->baksteg())						// Kan vi ta bort ett tecken
	{
		draw(ACTIVE_ROW);									// Rita om raden
	}
	else if(row[activeRow]->getLocOnRow() == 0 && activeRow > 0)	// Är pekaren längst till vänster
	{																					// och är det INTE raden högst upp
		row[activeRow-1]->setEndl(false);									// Raden ovanför är inte längre endl
		moveUpRow(activeRow);													// Sätt ihop raden med den ovanför

		if(row[activeRow]->getLen() == 0)									// Är raden tom?
		{
				delRow(activeRow);													// Ta bort raden.
		}
		else
		{
			activeRow--;
		}
		if(visualStartRow > activeRow)
			visualStartRow--;
		draw(ALL);												// Ritar upp allt en gång till
	}
}

void TextEdit::del()
{
	if(row[activeRow]->getLen() == row[activeRow]->getLocOnRow()
		&& activeRow < antRow)
	{
		row[activeRow]->setEndl(false);
		moveUpRow(activeRow+1);
		draw(ALL);
	}
	else if(row[activeRow]->del())
	{	draw(ACTIVE_ROW);	}
}

void TextEdit::delRow(int initRow)
{
	for(int i = initRow; i < antRow; i++)			// Flyttar fram alla objekt som är efter den
	{															// aktiva raden
		row[i]->clone(*row[i+1]);						// Kopierar
	}															// Två lika rader sist i vektorn
	delete row[antRow];									// Ger tillbaka minnet vi lånat
	row[antRow] = 0;										// Nollar minnet för säkerhets skull
	row.pop_back();										// Tar bort den sista raden från vektorn
	antRow -= 1;											// En rad mindre
	activeRow -= 1;										// minska activeRow med ett
}

void TextEdit::draw(DrawRow whatToDraw)
{
	printRowColumn();
//Ska den rensa hela textdelen av skärmen
	if(whatToDraw == ALL)
	{
		textcolor(WHITE);
		textbackground(BLACK);
		char tom[MAX_BREDD+1];
		String tempString;
		
		for(int i = visualStartRow; i < visualStartRow+RADER-1; i++)
		{
			tempString += "\n\r";
			tempString += LODRAT;
			if(i <= antRow)
			{
				tom[0] = '\0';
				for(int j = 0; j < MAX_BREDD - row[i]->getVisualLen(); j++ )
				{
					tom[j]	= ' ';
					tom[j+1] = '\0';
				}
				tempString += row[i]->getVisualString();
				tempString += tom;
			}
			else
			{
				//Rensar hela Raden
				for(int j = 0; j < MAX_BREDD; j++ )
				{
					tom[j]	= ' ';
				}
				tom[MAX_BREDD] = '\0';
				tempString += tom; //Rensar resten av raden om tex senaste tecknet var baksteg
			}
		}
		gotoxy(1,2);
		cputs(tempString.getString());
	}
//Rita bara aktiv rad
	if(whatToDraw == ACTIVE_ROW)
	{
		drawRow(activeRow);
	}
}

void TextEdit::drawRow(int init)
{
	if(init >= 0)
	{
		textcolor(WHITE);
		textbackground(BLACK);
		char tom[MAX_BREDD];
		if(init <= antRow)
		{
			tom[0] = '\0';
			for(int j = 0; j < MAX_BREDD - row[init]->getLen(); j++ )
			{
				tom[j]	= ' ';
				tom[j+1] = '\0';
			}
			gotoxy(2,3+init-visualStartRow);
			String tempString(row[init]->getVisualString());
			tempString += tom;
			cputs(tempString.getString());
		}
		else
		{
			//Rensar hela Raden
			for(int j = 0; j < MAX_BREDD; j++ )
			{
				tom[j]	= ' ';
			}
			tom[MAX_BREDD] = '\0';
			gotoxy(2,3+init-visualStartRow);
			cputs(tom); //Rensar resten av raden om tex senaste tecknet var baksteg
		}
	}
}

void TextEdit::drawRow(int startRow, int endRow)
{
	printRowColumn();
	for(int i = startRow; i < endRow && i < RADER; i++)
	{
		drawRow(i+visualStartRow);
	}
}

void TextEdit::enter()
{
	row[activeRow]->setEndl(true);
	int oldRow = activeRow;								// Lagrar gamla activeRow värdet i en variabel
	addRow();
	while(row[oldRow]->getLen() > row[oldRow]->getLocOnRow())
	{															// Flytta alla tecken som är efter locOnRow
		row[activeRow]->putIn(row[oldRow]->getChar(row[oldRow]->getLocOnRow()));
		row[oldRow]->del();								// Ta bort det kopierade tecknet
	}
	row[activeRow]->setLocOnRow(0);					// Sätter pekaren längst till vänster
	for(int i = 0; i <= antRow; i++)
		row[i]->setVisualStart(0);
	draw(ALL);
}

char* TextEdit::getAllRows()
{
	String allRows;
	for(int i = 0; i <= antRow; i++)
	{
		allRows += row[i]->getString();
		if(row[i]->getEndl() == true)
			allRows += '\n';
	}

	return allRows.getString();
}

void TextEdit::left()
{
//Ska raden ovanför bli aktiv?
	if(row[activeRow]->getLocOnRow() == 0 && activeRow > 0)
	{
		activeRow--;
		row[activeRow]->setLocOnRow(row[activeRow]->getLen());
		if(visualStartRow > activeRow)
			visualStartRow--;
	}
	else
	{
		moveBack();
	}
}

void TextEdit::moveBack()
{
	row[activeRow]->left();
}

void TextEdit::moveForward()
{
	row[activeRow]->right();
}

void TextEdit::moveUpRow(int initRow)
{
	if(initRow > 0 && initRow <= antRow)
	{
		row[initRow]->setLocOnRow(0);						// Sätter pekaren längst till vänster
		const int tempLen = row[initRow-1]->getLen();
		while(row[initRow-1]->getLen() < MAX_BREDD && row[initRow]->getLen() != 0)
		{															// Flytta alla tecken som är efter locOnRow
			row[initRow-1]->putIn(row[initRow]->getChar(row[initRow]->getLocOnRow()));
			row[initRow]->del();								// Ta bort det kopierade tecknet
		}
		row[initRow-1]->setLocOnRow(tempLen);
	}
}

bool TextEdit::ner()
{
	if(activeRow < antRow)
	{
		row[activeRow+1]->setLocOnRow(row[activeRow]->getLocOnRow());
		activeRow++;
		if(activeRow+1 > visualStartRow+RADER)
		{
			visualStartRow++;
			draw(ALL);
		}
		return true;
	}
	else
		return false;
}

void TextEdit::printRowColumn()
{
//Skriver ut rad och column på den gråa raden längst ner
	textcolor(BLACK);
	textbackground(7);
	gotoxy(4,25);
	char chColums[18], chRows[18];
	itoa(activeRow+1,chRows, 10);					// Gör om inten till en char vektor
	itoa(row[activeRow]->getLocOnRow()+1,chColums, 10);
	String tempString;
	tempString = tempString + "Rad: " + chRows + "    Kol: " + chColums + "    ";
	cputs(tempString.getString());
}

void TextEdit::putIn(char initChar)
{
	row[activeRow]->putIn(initChar);
	for(int i = 0; i <= antRow; i++)
		row[i]->setVisualStart(row[activeRow]->getVisualStart());
}

void TextEdit::right()
{
	if(row[activeRow]->getLocOnRow() < MAX_BREDD && row[activeRow]->getLocOnRow() <= row[activeRow]->getLen())
	{
		if(row[activeRow]->getLocOnRow() == row[activeRow]->getLen())
		{
			if(ner())
				row[activeRow]->setLocOnRow(0);
		}
		else
			moveForward();
	}
}

void TextEdit::showPointer()
{
	gotoxy(row[activeRow]->getLocOnVisual()+2, 3+activeRow-visualStartRow);
}

void TextEdit::setToNull()
{
	row.clear();										//Destruerar

	activeRow 		= 0;								//Konstruerar
	antRow 			= 0;
	visualStartRow = 0;
	row.push_back(new TextObjekt());
	row[antRow]->setWidth(MAX_BREDD-1);
}

void TextEdit::testKey(char initKey)
{

	if(initKey==0)										//	Specialtecken
	{
		switch(getch())
		{
			case CHUP:
			case CHUP1: // Pil upp
				this->upp();
			break;
			case CHLEFT:
			case CHLEFT1: // Pil vänster
				this->left();
			break;
			case CHRIGHT:
			case CHRIGHT1: // Pil höger
				this->right();
			break;
			case CHDOWN:
			case CHDOWN1: // Pil ner
				this->ner();
			break;
			case CHDEL: // Del
				this->del();
			break;
			default: // Annan
			break;
		}
	}

	else													//	Vanliga tecken
	{
		switch(initKey)
		{
			case 8: // Backsteg
				this->baksteg();
			break;
			case 9: // Tab
				for(int i=0; i<4; ++i)
				{
					this->putIn(' ');
				}
			break;
			case 13: // Enter
				this->enter();
			break;
			default: // Tecken a-z
				this->putIn(initKey);
			break;
		}
	}
	if(row[activeRow]->getVisualStart() > 0)
		draw(ALL);
	else
		draw(ACTIVE_ROW);
}

void TextEdit::upp()
{
	if(activeRow > 0)
	{
		row[activeRow-1]->setLocOnRow(row[activeRow]->getLocOnRow());
		activeRow--;
		if(visualStartRow > activeRow)
		{
			visualStartRow--;
			draw(ALL);
		}
	}
}
#endif /* ADEditor.hpp */
