			////////////////////////////////////////////////////////
			//																		//
			//			Fil: "MenuButton.hpp"								//
			//																		//
			//			Författad av: Andreas Sehr 2002,02,12			//
			//																		//
			//			Senast ändrad:	2002,02,12							//
			//																		//
			////////////////////////////////////////////////////////
#ifndef __MenuButton.hpp__
#define __MenuButton.hpp__

#include "Objekt.hpp"

class MenuButton : public Objekt
{
	public:
		MenuButton() : Objekt() {}
		MenuButton(char* initString)
		{
			setText(initString);
			left = 1;
			top = 1;
			bottom = height + top;
			right = width + left;
		}

		void draw()
		{
			gotoxy(getLeft(), getTop());

			if (getStatus() == Pressed)
			{
				textbackground(MBPRESSEDBG);
				textcolor(MBPRESSEDTEXT);
			}
			else
			{
				textcolor(MBTEXT);
				textbackground(MBUTTONBG);
			}

			cputs(getText());
		}
};

#endif /*__ADMenuButton.hpp__*/