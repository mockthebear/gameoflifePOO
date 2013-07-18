#include <iostream>
#include <list>

using namespace std;

#include "../include/GameOfLife.h"
#include "../include/RuleReader.h"



GameOfLife::GameOfLife(int w, int h) {
  width = w;
  height = h;
  //IMORTAL
  undosys = new Undo(w,h);
  grid = true;
  r = new RuleReader();
  r->parseRules(&rules);
  cells = new Cell*[w*h];
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      cells[i*width + j] = new Cell(i,j,0,0);
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

void GameOfLife::update(){
    undosys->addStep(cells);
}
void GameOfLife::undo(){
    undosys->reallyUndo(cells);
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

Cell *GameOfLife::getCell(int w, int h) {
  if(w < 0 || w >= width) return NULL;
  if(h < 0 || h >= height) return NULL;

  return  cells[h * width + w];
}

void GameOfLife::makeCellAlive(int w, int h,int t) {
  if(w < 0 || w >= width) return;
  if(h < 0 || h >= height) return;

  Cell* c = cells[h * width + w];

  if(!c->isAlive()) {
    cells[h * width + w]->revive(t);
  }

  statistics->survive();
}

void GameOfLife::makeCellDeadForced(int w, int h) {
  if(w < 0 || w >= width) return;
  if(h < 0 || h >= height) return;

  Cell* c = cells[h * width + w];

  if(c->isAlive()) {
    cells[h * width + w]->kill();
  }

  statistics->kill();
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
typedef struct ref{
    Cell *c;
    int t;
} REF;
void GameOfLife::nextGeneration() {
  //list<Cell*> mustRevive;
  list<Cell*> mustDie;
  list<REF*> mustRevive;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      int type = -1;
      if(shouldRevive(j,i,&type)) {
      	REF *rr = (REF*)malloc(sizeof(REF));
      	rr->c = cells[i*width+j];
      	rr->t = type;
      	mustRevive.push_back(rr);
      }
      else if (shouldKill(j,i)) {
      	mustDie.push_back(cells[i*width+j]);
      }
    }
  }
    update();
  for (list<REF*>::iterator it = mustRevive.begin(); it != mustRevive.end(); it++) {
    (*it)->c->revive((*it)->t);
    free((*it));
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
bool GameOfLife::shouldRevive(int w, int h,int *t) {
  int aliveNeighbors = aliveNeighborCells(w,h);
  bool equal = false;
  struct rule *r = rules;
  while (r != NULL){
    if (aliveNeighbors == r->cellToLive){
        equal = true;
        *t = r->id;
        break;
    }
    r = r->next;

  }

  return ((!isCellAlive(w,h)) && (equal));
}

/*
 * Uma celula viva deve morrer caso
 * tenha duas ou tres celulas vizinhas vivas.
 */
bool GameOfLife::shouldKill(int w, int h) {
  int aliveNeighbors = aliveNeighborCells(w,h);
  int cellType = cells[h * width + w]->getType();
  bool equal = true;
  struct rule *r = rules;
  while (r != NULL){
    if (r->id == cellType){
        int i;
        for (i=0;i<r->amnt;i++){
            if (r->cellToDie[i] == aliveNeighbors){
                equal = false;
                break;
            }
        }


        break;
    }
    r = r->next;

  }
  return (isCellAlive(w,h) && (equal));
}


