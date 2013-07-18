#include "../include/Screen.h"
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>    // std::max

//h = x
Screen::Screen(int h,int w,int row2,int col2){
    SDL_Init( SDL_INIT_EVERYTHING );
    height = h;
    width = w;
    screen = SDL_SetVideoMode( h,w+32, 32,  SDL_FULLSCREEN ); //SDL_SWSURFACE or
    if (!screen){
        exit(8);
    }
    TTF_Init();
    font = TTF_OpenFont( "../content/defaut.ttf",12 );
    SDL_WM_SetCaption( "Game of life!", NULL );
    col = col2;
    row = row2;
    BG = SDL_LoadBMP( "../content/background.bmp" );
    MBG = SDL_LoadBMP( "../content/menubg.bmp" );
    play    = SDL_LoadBMP( "../content/play.bmp" );
    pause   = SDL_LoadBMP( "../content/pause.bmp" );
    f       = SDL_LoadBMP( "../content/f.bmp" );
    ff      = SDL_LoadBMP( "../content/ff.bmp" );
    fff     = SDL_LoadBMP( "../content/fff.bmp" );
    refresh     = SDL_LoadBMP( "../content/refresh.bmp" );
    gen     = SDL_LoadBMP( "../content/gen.bmp" );

    //Text:
    SDL_Color textColor = { 100, 0, 255 };
    SDL_Color textColor2 = { 255, 10, 100 };
    txtp = TTF_RenderText_Solid( font, "Play/Pause:", textColor );
    txts = TTF_RenderText_Solid( font, "Speed:", textColor );
    txte = TTF_RenderText_Solid( font, "Refresh:", textColor );
    txtg = TTF_RenderText_Solid( font, "Next gen:", textColor );
    ln1 = TTF_RenderText_Solid( font, "Left click: common cell", textColor2 );
    ln2 = TTF_RenderText_Solid( font, "Right click: immortal cell", textColor2 );

}

void Screen::apply_surface( int x, int y, SDL_Surface* source )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, screen, &offset );
}
SDL_Rect *Screen::getLine(int type,int xx,int yy){
    SDL_Rect *clip = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    clip->x=xx;
    clip->y=yy;
    clip->w =type == 0 ? height : (((float)height/(float)row)/7.0 or 1.0);
    clip->h =type == 1 ? width : (((float)width/(float)col)/7.0 or 1.0);
    return clip;
}

void Screen::drawScreen(GameOfLife& game,int s,bool p){
    Surface *swt = surfaces;
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 237,191, 130 ) );
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = height;
    clip.h = width;
    SDL_FillRect( screen, &clip, SDL_MapRGB( screen->format, 255,255, 255 ) );


    int i = 0;
    SDL_Rect *vert =  getLine(1,0,0);
    SDL_Rect *hor =  getLine(0,0,0);
        int ax,ay;
    for (ax=0;ax<=(height/BG->w);ax++){
       for (ay=0;ay<=(width/BG->h);ay++)
        apply_surface(ax*BG->w,ay*BG->h,BG);
    }



    apply_surface(0,width,MBG);
    apply_surface(175,width+11,txtp);
    apply_surface(310,width+11,txts);
    apply_surface(410,width+11,txte);
    apply_surface(520,width+11,txtg);
    apply_surface(10,width+4,ln1);
    apply_surface(10,width+18,ln2);
    apply_surface(460,width+8,refresh);

    apply_surface(580,width+8,gen);
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
                int cola[3] = {255,255,255};
                struct rule *r = game.rules;
                while (r){
                    if (game.getCell(j,i)->getType() == r->id){
                        cola[0] = r->color[0];
                        cola[1] = r->color[1];
                        cola[2] = r->color[2];
                        break;
                    }

                    r = r->next;
                }
                SDL_Rect square;
                square.x = ((double)j)*((double)height/(double)col) -.5 ;
                square.y = ((double)i)*((double)width/(double)row) -.5;
                square.h = ((double)width/(double)col) + 1;
                square.w = ((double)height/(double)row) + 1 ;
                SDL_FillRect( screen, &square,  SDL_MapRGB( screen->format, cola[0],cola[1], cola[2] ) );
                //apply_surface(,,game.getCell(j,i)->s);
            }
            //tela->setCell(i,j,);
        }
    }

    int x=0;
    for (x=0;x<=(col);x++){
        vert->x = ((double)height/(double)col)*(double)x;
        if (game.grid)
        SDL_FillRect( screen, vert, SDL_MapRGB( screen->format, 237,191, 130 ) );
        //apply_surface(,0,gv);
    }
    int y=0;
    for (y=0;y<=(row);y++){
        hor->y = ((double)width/(double)row)*(double)y;

        //
        if (game.grid)
        SDL_FillRect( screen, hor, SDL_MapRGB( screen->format, 237,191, 130 ) );
        //apply_surface(0,,gh);
    }
    vert->x = ((double)height/(double)col)*(double)col;
    vert->w = height;
    hor->y = ((double)width/(double)row)*((double)row);
    hor->h = width;
    //SDL_FillRect( screen, vert, SDL_MapRGB( screen->format,237,191, 130 ) );
    //SDL_FillRect( screen, hor, SDL_MapRGB( screen->format, 237,191, 130 ) );
    free(hor);
    free(vert);
    SDL_Flip( screen );

    SDL_Delay(10);
}


Screen::~Screen(){
    SDL_FreeSurface(BG);
    SDL_FreeSurface(MBG);
       SDL_FreeSurface(play);
    SDL_FreeSurface(pause);
    SDL_FreeSurface(f);
    SDL_FreeSurface(ff);
    SDL_FreeSurface(fff);
    SDL_Quit();
    TTF_Quit();
}
