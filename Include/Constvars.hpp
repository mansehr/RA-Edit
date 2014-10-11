#ifndef __Constvarshpp__
#define __Constvarshpp__

// Definera olika rambitar
const char LUCORNER	= char(201);
const char LBCORNER	= char(200);
const char RUCORNER	= char(187);
const char RBCORNER	= char(188);
const char LODRAT		= char(186);
const char VAGRAT		= char(205);
const char TTOP		= char(203);
const char TBOTTOM	= char(202);
const char TLEFT		= char(204);
const char TRIGHT		= char(185);
const char KORS		= char(206);

const char TLUCORNER	= char(218);
const char TLBCORNER	= char(192);
const char TRUCORNER	= char(191);
const char TRBCORNER	= char(217);
const char TLODRAT	= char(179);
const char TVAGRAT	= char(196);
const char TTTOP		= char(194);
const char TTBOTTOM	= char(193);
const char TTLEFT		= char(195);
const char TTRIGHT	= char(180);
const char TKORS		= char(197);


// Definera fönstrets storlek
int COLUMNS	= get_console_width();
int ROWS		= get_console_height()-1;

//Olika knappar		Piltangenter							F1 - F4
const char CHUP 		= char(72); const char CHUP1 		= char(60);
const char CHDOWN 	= char(80); const char CHDOWN1 	= char(61);
const char CHLEFT 	= char(75); const char CHLEFT1 	= char(59);
const char CHRIGHT 	= char(77); const char CHRIGHT1 	= char(62);

const char CHESC 		= char(27);				// ESC
const char ENTER 		= char(13);				// Enter
const char CHDEL 		= char(83);				// DEL

//MenyKnappar
const char CHOPENMENU = char(39);			// '

//Meny Färger	0-15(Text) 0-7(Bakgrunder)
const int MBUTTONBG 		= int(7);			// MB = MenuButton
const int MBTEXT 			= int(0);			// Text
const int MBPRESSEDTEXT = int(15);
const int MBPRESSEDBG 	= int(0);
const int MBARBG 			= int(7);			// MenuBar Background
const int MDOWNBG 		= int(7);			// MenuDown Menyn
const int MITEXT 			= int(0);			// MI = MenuItem
const int MIACTIVETEXT 	= int(15);
const int MIACTIVEBG		= int(0);			// Aktiv Alternativ BG

#endif /*__Constvars.hpp__*/
