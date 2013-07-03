buildAndRun: linkMain
	./main

linkMain: compileAll 
	g++ -o main Statistics.o GameOfLife.o GameBoard.o Controller.o Main.o 

compileAll:  
	g++ -c Statistics.cpp GameOfLife.cpp GameBoard.cpp Controller.cpp Main.cpp

clean:
	rm *.o