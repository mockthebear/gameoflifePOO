/**
 * @file
 * 
 * A game board to display a GameOfLife environment. 
 * This is one of the UI modules.
 *
 * @author Rodrigo Bonifacio (rbonifacio[at]cic.unb.br)
 * @date 05/2011
 */
#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <string>
using namespace std;

#include "GameOfLife.h"

const string line  = "+-----+";  
const string dead  = "|     |";  
const string alive = "|  o  |";

/*! GameBoard class definition
 *
 *  This class represents a basic game of life environment,  
 *  which comprises a bidimensional grid. New environments 
 *  shuld be implemented.  
 */
class GameBoard {
 private:
  int rows;
  int cols;
  void printLine();
  void printLineIds();
  void clearScreen();
 public:
  /*! basic constructor, taking the number of rows and columns */
  GameBoard(int r, int c) : rows(r), cols(c) {}
  /*! updates the environment representation */
  void update(GameOfLife& game);
};
#endif
