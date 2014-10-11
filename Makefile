a.out: *.cpp *.h Include/*.hpp
	g++ Editor.cpp conio_unix.cpp -w -lncurses
