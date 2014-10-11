			////////////////////////////////////////////////////////
			//																		//
			//			Fil: "TextObjekt.hpp"								//
			//																		//
			//			Författad av: Andreas Sehr 2002,01,19			//
			//																		//
			//			Senast ändrad:	2002,01,19							//
			//																		//
			//			Innehåll: Ett textobjekt som ärver funktioner//
			//						 av klassen String, Kan ha en synlig//
			//						 sträng och en fullständig sträng. 	//
			//						 Bra klass att använda för textField//
			//						 och textArea klasser					//
			//																		//
			////////////////////////////////////////////////////////
#ifndef __TextObjekt.hpp__
#define __TextObjekt.hpp__

#include "String.hpp"

class TextObjekt
{
public:
	TextObjekt();
	TextObjekt( const TextObjekt &rhs );
	~TextObjekt();

//Generälla åtkomstmetoder
	void 	clone(const TextObjekt &rhs);
	bool 	deleteChar(int initInt);
	bool 	deleteLastChar()		const { return itsString->deleteLastChar();	}
	char 	getChar(int initLoc) const { return itsString->getChar(initLoc);	}
	bool	getEndl() 				const { return endl; 								}
	char 	getLastChar() 			const	{ return itsString->getLastChar();		}
	unsigned short getLen() 	const { return itsString->getLen();				}
	int 	getLocOnRow() 			const { return locOnRow;							}
	int 	getLocOnVisual() 		const { return locOnVisual;	 					}
	char* getString() 			const { return itsString->getString();			}
	int 	getVisualLen() 				{ getVisualString(); return visualString->getLen(); }
	int 	getVisualStart() 		const { return visualStart;	 					}
	char* getVisualString();
	int 	getWidth() 				const { return width;								}
	void 	putIn(char initChar);
	void 	setEndl(bool initEndl)		{ endl = initEndl;							}
	void 	setLocOnRow(int init);
	void 	setToNull();
	void 	setVisualStart(int initVS)	{ visualStart = initVS;						}
	void 	setWidth(int initWidth) 	{ width = initWidth;							}

//Tangenter
	bool 	baksteg();
	bool 	del();
	void 	left();
	void 	right();

private:
	String *itsString;
	String *visualString;

	void moveBack();
	void moveForward();

	int locOnRow;
	int locOnVisual;
	int visualStart;
	int width;
	bool endl;				// Innehåller strängen ett nyradstecken('\n')?
};

TextObjekt::TextObjekt()
{
	locOnRow 		= 0;
	visualStart 	= 0;
	locOnVisual 	= 0;
	width 			= 1;
	endl 				= false;
	visualString 	= new String;
	*visualString 	= "";
	itsString 		= new String;
	*itsString 		= "";
}

TextObjekt::TextObjekt( const TextObjekt &rhs)
{
	locOnRow 		= rhs.getLocOnRow();
	visualStart 	= rhs.getVisualStart();
	locOnVisual 	= rhs.getLocOnVisual();
	width 			= rhs.getWidth();
	endl 				= rhs.getEndl();

	itsString	 	= new String;
	*itsString 		= rhs.getString();
	visualString 	= new String();
	*visualString 	= "";
}

TextObjekt::~TextObjekt()
{
	delete visualString;
	visualString = 0;
	delete itsString;
	itsString = 0;
}

bool TextObjekt::deleteChar(int initInt)
{
	return itsString->deleteChar(initInt);
}

void TextObjekt::clone(const TextObjekt &rhs)
{
	delete itsString;
	itsString = 0;

	locOnRow 	= rhs.getLocOnRow();
	visualStart = rhs.getVisualStart();
	locOnVisual = rhs.getLocOnVisual();
	width 		= rhs.getWidth();
	endl 			= rhs.getEndl();
	itsString 	= new String;
	*itsString 	= rhs.getString();
}
//----------------------------------------------------------
//	Lägger till ett tecken i strängen och flyttar fram ett steg
//----------------------------------------------------------
void TextObjekt::putIn(char initChar)
{
	itsString->putIn(initChar, locOnRow);
	moveForward();
}

char* TextObjekt::getVisualString()
{
	*visualString = "";
	for(int i = visualStart, visual = 0; i < itsString->getLen() && visual < width; i++, visual++)
	{
		*visualString += itsString->getChar(i);
	}

	return visualString->getString();
}

void TextObjekt::setLocOnRow(int init)
{
	if(init > itsString->getLen())
	{
		init = itsString->getLen();
	}
	if(init>=0)
	{
		locOnRow = init;
		locOnVisual = (init <= width) ? init : width;
	}
}
void TextObjekt::setToNull()
{
	itsString->setToNull();
	visualString->setToNull();
	locOnRow 		= 0;
	visualStart 	= 0;
	locOnVisual 	= 0;
	width 			= 1;
	endl 				= false;
}

void TextObjekt::moveBack()
{
	//-------------------------------------------------------
	//	locOnRow blir väl inte mindre än noll
	//-------------------------------------------------------
	if(locOnRow > 0)
	{
		locOnRow--;
		locOnVisual--;
		//----------------------------------------------------
		//	Om vi kan flytta lite åt vänster.
		//----------------------------------------------------
		if(locOnVisual < 0 )
		{
			visualStart--;
			locOnVisual = 0;
			if(visualStart > 0)
			{
				visualStart--;
				locOnVisual = 1;
			}
		}
	}
}

void TextObjekt::moveForward()
{
	if(locOnRow < itsString->getLen() && itsString->getChar(locOnRow) != '\n')
	{
		locOnRow++;
		locOnVisual++;
		if(locOnVisual > width )
		{
			visualStart++;
			locOnVisual = width;
		}
	}
}

bool TextObjekt::baksteg()
{
	if(itsString->deleteChar(locOnRow))
	{
		moveBack();
		return true;
	}
	else
		return false;
}

bool TextObjekt::del()
{
	if(itsString->deleteChar(locOnRow+1))
		return true;
	else
		return false;
}

void TextObjekt::left()
{
	moveBack();
}

void TextObjekt::right()
{
	moveForward();
}

#endif /* __TextObjekt.hpp__ */