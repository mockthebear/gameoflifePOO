#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include <string>

#ifndef SCREEN_H
#define SCREEN_H

typedef struct Surfaces{
    int x,y,xx,yy;
    SDL_Surface *s;
    struct Surfaces *next;

}Surface;
class Screen{
    SDL_Surface* screen,*gh,*gv;
    SDL_Event event;
    TTF_Font *font;
    int col,row,height,width;
    Surface *surfaces;
    bool quit;
    public:

        Screen(int,int,int,int);
        ~Screen();
        void drawScreen();
        int refresh();
        void setCell(int,int,bool);
        void apply_surface( int , int , SDL_Surface* );
        void newText(int x,int y,const char *s);
        void createCell(int x,int y,int xxx,int yyy);
};

#endif
