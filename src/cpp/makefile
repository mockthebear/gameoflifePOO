buildAndRun: linkMain
	./main

linkMain: compileAll
	g++ -o main Screen.o Statistics.o GameOfLife.o GameBoard.o Controller.o Main.o -lmingw32 -lSDLmain -lSDL -mwindows -lSDL_ttf
compileAll:
	g++ -c Screen.cpp Statistics.cpp GameOfLife.cpp GameBoard.cpp Controller.cpp Main.cpp

clean:
	rm *.o
