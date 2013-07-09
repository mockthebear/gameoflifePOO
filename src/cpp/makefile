CMP = g++
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.c=.o)

linkMain: compileAll
	$(CMP) -o main $(OBJ) -lmingw32 -lSDLmain -lSDL -mwindows -lSDL_ttf
compileAll:
	$(CMP) -c $(SRC)
clean:
	rm *.o