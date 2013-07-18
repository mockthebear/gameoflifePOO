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
    SDL_Surface* screen,*BG,*MBG,*play,*pause,*f,*ff,*fff,*txtp,*txts,*txte,*refresh,*ln1,*ln2,*gen,*txtg,*und;

    TTF_Font *font;
    int col,row,height,width;
    Surface *surfaces;
    public:

        Screen(int,int,int,int);
        ~Screen();
        SDL_Rect *getLine(int type,int xx,int yy);
        SDL_Surface *getScreen(){return screen;};
        void drawScreen(GameOfLife& game,int s,bool p);
        void apply_surface( int , int , SDL_Surface* );

};

#endif
