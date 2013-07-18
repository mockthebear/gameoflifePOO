#include <iostream>
#include <string>

using namespace std;

#include "../include/GameOfLife.h"

#include "../include/Controller.h"
#include "../include/Screen.h"

const int rows = 100;
const int cols = 100;
const int sx = (1036);
const int sy = (668);

int main(int argc, char** argv) {


  //-lmingw32 -llua51 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDLgfx
  Screen tela(sx, sy,cols, rows);
  GameOfLife game(cols, rows);

  Controller controller(game, cols, rows,sx, sy,&tela);

  controller.startGame();

}


/*!
Cool rules:

[4;255;155;100;6:3,4,5,6,7,8]

[6;155;255;200;3:6,7,8]
*/
