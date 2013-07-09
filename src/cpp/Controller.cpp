#include <iostream>

using namespace std;

#include "../include/Controller.h"
#include "../include/Screen.h"
int Controller::input(){


        while( SDL_PollEvent( &event ) )
        {

            if( event.type == SDL_KEYDOWN )
            {
                //event.key.keysym.sym
                int key = event.key.keysym.sym;
                if (key == 27){
                    exit(1);
                }
            }

            else if( event.type == SDL_QUIT )
            {

                return -1;
            }else if( event.type == SDL_MOUSEBUTTONDOWN  )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    int XX = event.motion.x;
                    int YY = event.motion.y;

                    int XX_ = XX-XX%(height/col)+((height/col)/3);
                    int YY_ = YY-YY%((width/row))+((width/row)/4);
                    int ROW = (YY-YY%((width/row)))/(width/row);
                    int COL = (XX-XX%(height/col))/(height/col);

                    revive(COL,ROW);
                    if (XX >= 250 and XX <= 270 and YY >= width+8 and YY <= width+28 ){
                        play = !play;
                    }
                    if (XX >= 350 and XX <= 370 and YY >= width+8 and YY <= width+28 ){
                        speed++;
                        speed = speed > 3 ? 1 : speed;
                    }
                }
            }
    }
}

void Controller::startGame() {
    int t = SDL_GetTicks();
  while(true) {
    tela->drawScreen(game,speed,play);
    int menu = input();

    if (t <= SDL_GetTicks() and play){
        t =  SDL_GetTicks() + (1000/(speed));
        nextGeneration();
        tela->drawScreen(game,speed,play);
    }
  }
}

/*void Controller::revive(int c,int r) {
  int cols = game.getWidth();
  int rows = game.getHeight();
   if (game.isCellAlive(c,r))
    game.makeCellDead(c,r);
   else
    game.makeCellAlive(c, r);
   //board.update(game);
   tela->drawScreen(game,speed,play);
}*/

void Controller::nextGeneration() {
  game.nextGeneration();
  //board.update(game);
  tela->drawScreen(game,speed,play);
}
