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
#include "Screen.h"


class GameBoard {
 private:
  int rows;
  int cols;

  Screen *tela;
 public:
  /*! basic constructor, taking the number of rows and columns */
  GameBoard(int r, int c,Screen *t) : rows(r), cols(c),tela(t) {}
  /*! updates the environment representation */
  void update(GameOfLife& game);
};
#endif
