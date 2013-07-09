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

#include <iostream>
#include <cstring>
#include "Statistics.h"
#include "Cell.h"
#include <list>


 using namespace std;

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
	list<State*> states;
	void killEnvironment();
 public:
	/*! Constructor, taking the number of columns and rows */
	GameOfLife(int w, int h);

	/*! Leads the game state to a next generation */
	void nextGeneration();

	/*! Access method to the number of columns */
	int getWidth() const { return width; }

	/*! Access method to the number of rows */
	int getHeight() const { return height; }
	
	/*! Retorna a celula especificada */
	Cell *getCell(int,int);

	/*! Retorna o estado da celula */
	char* getState(int w, int h);

	State* findState(char *stateName);

	Cell **getCells();

	bool isCellAlive(int j, int i);
};

#endif
