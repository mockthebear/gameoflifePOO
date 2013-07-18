buildAndRun: linkMain
	./main

linkMain: compileAll
	g++ -o main Screen.o Statistics.o GameOfLife.o GameBoard.o Controller.o RuleReader.o Undo.o Main.o -lmingw32 -lSDLmain -lSDL -mwindows -lSDL_ttf
compileAll:
	g++ -c Screen.cpp Statistics.cpp GameOfLife.cpp GameBoard.cpp Controller.cpp Undo.cpp RuleReader.cpp Main.cpp

clean:
	rm *.o
