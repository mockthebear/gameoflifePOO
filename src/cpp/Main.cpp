#include <iostream>
#include <string>

using namespace std;

#include "../include/GameOfLife.h"

#include "../include/Controller.h"
#include "../include/Screen.h"

const int rows = 10;
const int cols = 10;

int main(int argc, char** argv) {



  //-lmingw32 -llua51 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDLgfx
  Screen tela(640, 480,cols, rows);
  GameOfLife game(cols, rows);

  Controller controller(game, cols, rows,640, 480,&tela);

  controller.startGame();

}


