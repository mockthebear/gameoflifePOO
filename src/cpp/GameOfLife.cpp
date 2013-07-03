#include <iostream>
#include <list>

using namespace std;

#include "../include/GameOfLife.h"



Cell::Cell(){ 
  state = ALIVE;
}

void Cell::kill() {
  state = DEAD;
}

void Cell::revive() {
  state = ALIVE;
}

bool Cell::isAlive() {
  return state == ALIVE;
}

GameOfLife::GameOfLife(int w, int h) {
  width = w;
  height = h;
  
  cells = new Cell*[w*h];
  
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      cells[i*width + j] = new Cell();
    }
  }
  
  killEnvironment();
  
  statistics = new Statistics();
}

void GameOfLife::killEnvironment() {
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      cells[i*width + j]->kill();
    }
  }
}

int GameOfLife::aliveCells() {
  int r = 0;

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(cells[i*width + j]->isAlive()) {
	r++;
      }
    }
  }
  return r;
}

int GameOfLife::aliveNeighborCells(int w, int h) {
  if(w < 0 || w >= width) return 0;
  if(h < 0 || h >= height) return 0;
  
  int r = 0;

  for(int i = h-1; i <= h + 1; i++) {
    for(int j = w-1; j <= w+1; j++) {
      if((! ((i == h) && (j == w))) && isCellAlive(j,i)) {
	r++;
      }
    }
  }
  return r;
}

bool GameOfLife::isCellAlive(int w, int h) {
  if(w < 0 || w >= width) return false;
  if(h < 0 || h >= height) return false;

  return  cells[h * width + w]->isAlive();
}


void GameOfLife::makeCellAlive(int w, int h) {
  if(w < 0 || w >= width) return;
  if(h < 0 || h >= height) return;

  Cell* c = cells[h * width + w];

  if(!c->isAlive()) {
    cells[h * width + w]->revive();
  }

  statistics->survive();
}


void GameOfLife::makeCellDead(int w, int h) {
  if(w < 0 || w >= width) return;
  if(h < 0 || h >= height) return;

  Cell* c = cells[h * width + w];

  if(c->isAlive()) {
    cells[h * width + w]->kill();
  }

  statistics->kill();
}

void GameOfLife::nextGeneration() {
  list<Cell*> mustRevive;
  list<Cell*> mustDie;

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(shouldRevive(j,i)) {
      	mustRevive.push_back(cells[i*width+j]);
      }
      else if (shouldKill(j,i)) {
      	mustDie.push_back(cells[i*width+j]);
      }
    }
  }

  for (list<Cell*>::iterator it = mustRevive.begin(); it != mustRevive.end(); it++) {
    (*it)->revive();
    statistics->survive();
  }

  for (list<Cell*>::iterator it = mustDie.begin(); it != mustDie.end(); it++) {
    (*it)->kill();
     statistics->kill();
  }
}

 /* Usando o TM, deveriamos tornar shouldRevive e 
  * shouldKill abstratos.
  */ 

/*
 * Uma celula morta deve ressuscitar caso 
 * tenha tres celulas vizinhas vivas.

 */ 
bool GameOfLife::shouldRevive(int w, int h) {
  int aliveNeighbors = aliveNeighborCells(w,h);

  return ((!isCellAlive(w,h)) && (aliveNeighbors == 3));
}

/*
 * Uma celula viva deve morrer caso 
 * tenha duas ou tres celulas vizinhas vivas.
 */ 
bool GameOfLife::shouldKill(int w, int h) {
  int aliveNeighbors = aliveNeighborCells(w,h);

  return (isCellAlive(w,h) && (aliveNeighbors != 2 && aliveNeighbors != 3));
}


