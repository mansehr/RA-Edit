////////////////////////////////////////////////////////////
//																			 //
//		Fil: "TextField.hpp"											 //
//																			 //
//		Författad av: Andreas Sehr, 2002-12-17			 		 //
//																			 //
//		Beskrivning: Skapar ett textfält som är				 //
//						 lätt att redigera.							 //
//																			 //
////////////////////////////////////////////////////////////
#ifndef __TextFieldhpp__
#define __TextFieldhpp__

#include "TextObjekt.hpp"
#include "Objekt.hpp"

class TextField : public TextObjekt , public Objekt
{
	public:

		TextField () : TextObjekt() , Objekt()
		{	;	}

		const int getWidth() const {return TextObjekt::getWidth();}
		void setWidth (int initWidth) {TextObjekt::setWidth(initWidth);}
		void isActive();
		void draw();

	private:
};
//----------------------------------------------------------
//	isActive används när man vill skriva till TextFältet
//----------------------------------------------------------
void TextField::isActive()
{
	bool stop = false;
	while(!stop)
	{
		gotoxy(getLeft(), getTop());
		this->draw();
		char key=getch();
	/*Special*/
		if(key==0)
		{
			char key=getch();
			switch(key)
			{
/*Pil VÄNSTER*/	case CHLEFT: TextObjekt::left(); break;
	/*Pil HÖGER*/	case CHRIGHT: TextObjekt::right(); break;
	/*Del*/			case CHDEL: TextObjekt::del(); break;
	/*ANNAN*/		default: break;
			}
		}
		switch(key)
		{
/*Baksteg*/		case 8: this->baksteg(); break;
/*TAB <-->*/	case 9: for(int i=0; i<4; ++i)
							{	this->putIn(' ');	}
					break;
	/*Esc*/		case CHESC: stop = true; break;
	/*Enter*/	case ENTER: stop = true; break;
/*Tecken a-z*/	default: this->putIn(key); break;
		}
	}
}
void TextField::draw()
{
	textbackground(BLUE);
	textcolor(WHITE);
	char bg[COLUMNS];
	bg[0] = '[';
	for(int i = 1; i < getWidth()+1; i++)
	{
		bg[i] = ' ';
	}
	bg[getWidth()+1] = ']';
	bg[getWidth()+2] = '\0';

	gotoxy(getLeft(), getTop());
	cputs(bg);
	gotoxy(getLeft()+1, getTop());
	cputs(getVisualString());
}

#endif /*__TextField.hpp__*/
