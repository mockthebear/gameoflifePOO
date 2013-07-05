#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include <string>

#include "GameOfLife.h"
#ifndef SCREEN_H
#define SCREEN_H

typedef struct Surfaces{
    int x,y,xx,yy;
    SDL_Surface *s;
    struct Surfaces *next;

}Surface;
class Screen{
    SDL_Surface* screen,*gh,*gv,*BG,*MBG,*play,*pause,*f,*ff,*fff,*txtp,*txts;

    TTF_Font *font;
    int col,row,height,width;
    Surface *surfaces;
    public:

        Screen(int,int,int,int);
        ~Screen();
        void drawScreen(GameOfLife& game,int s,bool p);

        void setCell(int,int,bool);
        void apply_surface( int , int , SDL_Surface* );
        void newText(int x,int y,const char *s);

};

#endif