#include "../include/Screen.h"
Screen::Screen(int h,int w,int row2,int col2){
    SDL_Init( SDL_INIT_EVERYTHING );
    height = h;
    width = w;
    screen = SDL_SetVideoMode( h,w, 32, SDL_SWSURFACE );
    TTF_Init();
    quit = false;
    font = TTF_OpenFont( "../content/defaut.ttf",12 );
    SDL_WM_SetCaption( "Game of life!", NULL );
    surfaces = (Surface*)malloc(sizeof(Surfaces));
    surfaces->next = NULL;
    surfaces->x = surfaces->y = 0;
    col = col2;
    row = row2;
    surfaces->s = SDL_LoadBMP( "../content/background.bmp" );
    gh = SDL_LoadBMP( "../content/grid_h.bmp" );
    gv = SDL_LoadBMP( "../content/grid_v.bmp" );
}

void Screen::apply_surface( int x, int y, SDL_Surface* source )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, screen, &offset );
}
void Screen::createCell(int x,int y,int xxx,int yyy){
    Surface *f = surfaces;
    SDL_Color textColor = { 255, 255, 255 };
    if (surfaces == NULL){
        f = surfaces = (Surface*)malloc(sizeof(Surfaces));
    }else{
        f = surfaces;
        while (f->next != NULL){
            f = f->next;
        }
        f = f->next = (Surface*)malloc(sizeof(Surfaces));
    }
    f->x = x;
    f->y = y;
    f->xx = xxx;
    f->yy = yyy;
    f->s = SDL_LoadBMP( "../content/yellow.bmp" );
    f->next = NULL;

}

void Screen::newText(int x,int y,const char *s){
    Surface *f = surfaces;
    SDL_Color textColor = { 255, 255, 255 };
    if (surfaces == NULL){
        f = surfaces = (Surface*)malloc(sizeof(Surfaces));
    }else{
        f = surfaces;
        while (f->next != NULL){
            f = f->next;
        }
        f = f->next = (Surface*)malloc(sizeof(Surfaces));
    }
    //f = (Surface*)malloc(sizeof(Surfaces));
    f->x = x;
    f->y = y;
    f->s = TTF_RenderText_Solid( font, s, textColor );
    f->next = NULL;

}
void Screen::drawScreen(){
    Surface *swt = surfaces;
    int i = 0;
    while (swt != NULL){
        i++;
        apply_surface(swt->x,swt->y,swt->s);
        swt = swt->next;
    }
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
    SDL_Delay(10);
}
int Screen::refresh(){
    while( quit == false )
    {
        drawScreen();
        if( SDL_PollEvent( &event ) )
        {

            if( event.type == SDL_KEYDOWN )
            {
                //event.key.keysym.sym
                int key = event.key.keysym.sym;
                return key-'0';
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
                    //createCell(XX_,YY_,ROW,COL);
                    /*
                    Pressed ROW & COL
                    */
                }
            }
        }

        if( SDL_Flip( screen ) == -1 )
        {
            return -1;
        }
    }
}
void Screen::setCell(int i,int j,bool b){

}
Screen::~Screen(){
        SDL_Quit();
        TTF_Quit();
}
