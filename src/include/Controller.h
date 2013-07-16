/**
 * @file
 *
 * A controller component of the GameOfLife game.
 *
 * @author Rodrigo Bonifacio (rbonifacio[at]cic.unb.br)
 * @date 05/2011
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL/SDL.h>
#include "GameOfLife.h"
#include "Screen.h"

/*! Controller class definition
 *
 * This class deals with the user inputs,
 * and based on the user actions it triggers
 * the proper functionality.
 *
 * Besides that, its interface is really simple. Only
 * one public method is available, which just start a game.
 */
class Controller{
 private:
  GameOfLife& game;
  SDL_Event event;
  Screen *tela;
  bool play;
  int speed;
  int col,row,height,width;
  void revive(int c,int r,int t);
  void nextGeneration();
 public:
  /*! Controller constructor, taking a game instance (model) and a game board (view) */
  Controller(GameOfLife& g, int c,int r,int h,int w,Screen *tela) : game(g), col(c), row(r), height(h), width(w),tela(tela) {speed = 1;play=false;}

  /*! Start the execution of the game */
  void startGame();

  /*! Receive inputs*/
  int input();
};
#endif
