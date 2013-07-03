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

#include "GameOfLife.h"
#include "GameBoard.h"

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
  GameBoard& board;
  void revive();
  void nextGeneration();
 public:
  /*! Controller constructor, taking a game instance (model) and a game board (view) */
  Controller(GameOfLife& g, GameBoard& b) : game(g), board(b) {} 
  
  /*! Start the execution of the game */
  void startGame();
};
#endif
