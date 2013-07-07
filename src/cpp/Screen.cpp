#include "../include/Screen.h"
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
Screen::Screen(int h,int w,int row2,int col2){
    SDL_Init( SDL_INIT_EVERYTHING );
    height = h;
    width = w;
    screen = SDL_SetVideoMode( h,w+32, 32, SDL_SWSURFACE );
    TTF_Init();
    font = TTF_OpenFont( "../content/defaut.ttf",12 );
    SDL_WM_SetCaption( "Game of life!", NULL );
    col = col2;
    row = row2;
    BG = SDL_LoadBMP( "../content/background.bmp" );
    MBG = SDL_LoadBMP( "../content/menubg.bmp" );
    gh = SDL_LoadBMP( "../content/grid_h.bmp" );
    gv = SDL_LoadBMP( "../content/grid_v.bmp" );
    play    = SDL_LoadBMP( "../content/play.bmp" );
    pause   = SDL_LoadBMP( "../content/pause.bmp" );
    f       = SDL_LoadBMP( "../content/f.bmp" );
    ff      = SDL_LoadBMP( "../content/ff.bmp" );
    fff     = SDL_LoadBMP( "../content/fff.bmp" );

    //Text:
    SDL_Color textColor = { 100, 0, 255 };
    txtp = TTF_RenderText_Solid( font, "Play/Pause:", textColor );
    txts = TTF_RenderText_Solid( font, "Speed:", textColor );

}

void Screen::apply_surface( int x, int y, SDL_Surface* source )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, screen, &offset );
}


void Screen::newText(int x,int y,const char *s){

}
void Screen::drawScreen(GameOfLife& game,int s,bool p){
    Surface *swt = surfaces;
    int i = 0;
    apply_surface(0,0,BG);
    int x=0;
    for (x=0;x<=(height/col);x++){
        apply_surface((height/col)*x,0,gv);
    }
    int y=0;
    for (y=0;y<=(width/row);y++){
        apply_surface(0,(width/row)*y,gh);
    }
    apply_surface(0,width-6,gh);
    apply_surface(height-6,0,gv);
    apply_surface(0,width,MBG);
    apply_surface(175,width+11,txtp);
    apply_surface(310,width+11,txts);
    if (!p)
        apply_surface(250,width+8,play);
    else
        apply_surface(250,width+8,pause);
    switch(s){
    case 1:
        apply_surface(350,width+8,f);
        break;
    case 2:
        apply_surface(350,width+8,ff);
        break;
    case 3:
        apply_surface(350,width+8,fff);
        break;

    }

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if (game.isCellAlive(j,i)){
                apply_surface((j)*(height/col)+16,(i)*(width/row)+10,game.getCell(j,i)->s);
            }
            //tela->setCell(i,j,);
        }
    }

    SDL_Flip( screen );

    SDL_Delay(10);
}

void Screen::setCell(int i,int j,bool b){

}
Screen::~Screen(){
        SDL_Quit();
        TTF_Quit();
}
