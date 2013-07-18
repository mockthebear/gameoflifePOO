#include <iostream>

using namespace std;

#include "../include/Controller.h"
#include "../include/Screen.h"
#include "../include/Statistics.h"
int Controller::input(){


        while( SDL_PollEvent( &event ) )
        {

            if( event.type == SDL_KEYDOWN )
            {
                //event.key.keysym.sym
                int key = event.key.keysym.sym;
                if (key == 27){
                    exit(1);
                }else if(key == 'g'){
                    game.nextGeneration();
                }else if(key == 'n'){
                    game.killEnvironment();
                }else if(key == 'p'){
                    play = !play;
                }else if(key == 'u'){
                    game.undo();
                }else if (key == '.'){
                    game.grid = !game.grid;
                }else if(key == 's'){
                    speed++;
                    speed = speed > 3 ? 1 : speed;
                }else if(key == 'c'){
                    //J
                    SDL_Color textColor = { 255, 100, 0 };
                    char ss[80];
                    sprintf(ss,"Mortas %d Vivas %d.",game.getStat()->getKill(),game.getStat()->getSurvive());
                    tela->apply_surface( 10 , 10 ,TTF_RenderText_Solid( TTF_OpenFont( "../content/defaut.ttf",20 ),ss, textColor ));
                    SDL_Flip( tela->getScreen() );
                    SDL_Delay(1000);
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


                    int ROW = ((double)row*(double)YY)/((double)width);
                    int COL = ((double)col*(double)XX)/((double)height);
                    game.update();
                    revive(COL,ROW,0);

                    if (XX >= 250 and XX <= 270 and YY >= width+8 and YY <= width+28 ){
                        play = !play;
                    }
                    if (XX >= 350 and XX <= 370 and YY >= width+8 and YY <= width+28 ){
                        speed++;
                        speed = speed > 3 ? 1 : speed;
                    }
                    if (XX >= 460 and XX <= 480 and YY >= width+8 and YY <= width+28 ){
                        game.killEnvironment();
                    }
                    if (XX >= 580 and XX <= 600 and YY >= width+8 and YY <= width+28 ){
                        game.nextGeneration();
                    }
                }else if( event.button.button == SDL_BUTTON_RIGHT )
                {
                    int XX = event.motion.x;
                    int YY = event.motion.y;

                 int ROW = ((double)row*(double)YY)/((double)width);
                    int COL = ((double)col*(double)XX)/((double)height);
                    game.update();
                    revive(COL,ROW,1);


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
        t =  SDL_GetTicks() + (1000.0 - (1000.0/(3.1-(float)speed)) );
        nextGeneration();
        tela->drawScreen(game,speed,play);
    }
  }
}

void Controller::revive(int c,int r,int t) {
  int cols = game.getWidth();
  int rows = game.getHeight();
   if (game.isCellAlive(c,r))
    game.makeCellDead(c,r);
   else
    game.makeCellAlive(c, r,t);
   //board.update(game);
   tela->drawScreen(game,speed,play);
}

void Controller::nextGeneration() {
  game.nextGeneration();
  //board.update(game);
  tela->drawScreen(game,speed,play);
}
