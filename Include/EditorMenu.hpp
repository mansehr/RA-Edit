			////////////////////////////////////////////////////////
			//																		//
			//			Fil: "EditorMenu.cpp"								//
			//																		//
			//			Författad av: Andreas Sehr 2002,12,04			//
			//																		//
			//			Senast ändrad:	2002,12,04							//
			//																		//
			////////////////////////////////////////////////////////

// Menyn är tyvär global...
MenuBar 		menuBar;							// Globala variabler
Menu 			arkiv			("Arkiv");
Menu 			help			("Hjalp");
MenuItem 	miNytt		("Nytt");
MenuItem 	miOppna		("Oppna");
MenuItem 	miSpara		("Spara");
MenuItem 	miAvsluta	("Avsluta");
MenuItem 	miHelp		("Om Editor");
MenuItem 	miReadMe		("Read Me");
bool 			menyIsDone 	= 	false;
void initMenu()
{
	if(menyIsDone != true)				// Har menyn blivit initierad redan?
	{											// Om inte....
		arkiv.add(miNytt);				// Initiera menyn
		arkiv.add(miOppna);
		arkiv.add(miSpara);
		arkiv.add(miAvsluta);
		help.add(miHelp);
		help.add(miReadMe);
		menuBar.setLeft(1);
		menuBar.setTop(1);
		menuBar.setRight(2);
		menuBar.setWidth(COLUMNS);
		menuBar.add(arkiv);
		menuBar.add(help);
	}
	menyIsDone = true;				// Menyn har blivit iordninggjord
}
