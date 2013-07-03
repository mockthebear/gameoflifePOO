runTests: linkMain
	./main

linkMain: compileAll 
	g++ -o main Statistics.o GameOfLife.o GameOfLifeTest.o Main.o -lcppunit

compileAll:  
	g++ -c ../cpp/Statistics.cpp ../cpp/GameOfLife.cpp GameOfLifeTest.cpp Main.cpp

clean:
	rm *.o