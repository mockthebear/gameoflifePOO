/**
 * @file
 *
 * The game of life model component, which compromises
 * the Cell and GameOfLiife class definitions.
 *
 * @author Rodrigo Bonifacio (rbonifacio[at]cic.unb.br)
 * @date 05/2011
 */
 #include <SDL/SDL.h>
#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

#include "Statistics.h"
#include "RuleReader.h"
#include "Undo.h"

/*! GameOfLife class definition
 *
 *  Modularizes the behavior of a game
 *  of life. In this version, just one algorithm
 *  for evolving the environment for a next generation is allowed.
 *  To solve this provlem, we could evolve this design using either
 *  the Strategy or Template Method design patterns
 *  (both).
 *
 *  This version is not well designed, since it keeps
 *  a reference to one instance of the Statistics class. It
 *  would be nice to see an implementation of this class
 *  being a subject participant of the Observer pattern,
 *  whereas the Statics class could be one subscriber
 *  participant of the Observer pattern.
 */
class GameOfLife {
 private:
  int width, height;
  Statistics* statistics;
  Cell** cells;
  Undo *undosys;

  RuleReader *r;
  bool shouldRevive(int w, int h,int *t);
  bool shouldKill(int w, int h);
 public:
    bool grid;
  struct rule *rules;
  /*! Undo! */
  void undo();
  void update();
  /*! Became public! */
  void killEnvironment();
  /*! Constructor, taking the number of columns and rows */
  GameOfLife(int w, int h);

  /*! Returns the number of cells in the ALIVE state */
  int aliveCells();
  Statistics* getStat(){return statistics;};


  /*! Given the position of a cell, returns the number of alive neighbors */
  int aliveNeighborCells(int w, int h);

  /*! Checks whether a cell is alive */
  bool isCellAlive(int w, int h);
  /* check if the cell is immortal */
  bool isCellImmortal(int w, int h);

  /*! Makes a given cell alive */
  void makeCellAlive(int w, int h,int t);


  /*! Kills a given cell */
  void makeCellDead(int w, int h);
  /* Kill the cell, even if it is immortal */
  void makeCellDeadForced(int w, int h);

  /*! Leads the game state to a next generation */
  void nextGeneration();

  /*! Access method to the number of columns */
  int getWidth() const { return width; }

  /*! Access method to the number of rows */
  int getHeight() const { return height; }
    /*! Retorna a celul especificada */
    Cell *getCell(int,int);
};

#endif
