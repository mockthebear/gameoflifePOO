#include <iostream>
#include <list>

using namespace std;

#include "../include/GameOfLife.h"
#include "../include/RuleReader.h"


Cell::~Cell(){
    //SDL_FreeSurface(s);
}
Cell::Cell(int i,int j,int t,int typ){
  state = ALIVE;
  i = i;
  j = j;
  type = typ;
}


void Cell::kill() {

  state = DEAD;

}

void Cell::revive(int i) {
  type = i;
  state = ALIVE;
}
bool Cell::isAlive() {
  return state == ALIVE;
}

GameOfLife::GameOfLife(int w, int h) {
  width = w;
  height = h;

  //Rules!
  rules = (struct rule*)malloc(sizeof(struct rule));
  rules->id = 0;
  rules->cellToLive = 3;
  rules->amnt = 2;
  rules->cellToDie = (int*)malloc(sizeof(int)*rules->amnt);
  rules->cellToDie[0] = 2; //Morrer se for 2 ou 3;
  rules->cellToDie[1] = 3;
  rules->color[0] = 255;
  rules->color[1] = 255;
  rules->color[2] = 0;
  struct rule *temp = rules->next = (struct rule*)malloc(sizeof(struct rule));
  //IMORTAL

  temp->id = 1;
  temp->cellToLive = -1;
  temp->amnt = 9;
  temp->cellToDie = (int*)malloc(sizeof(int)*9);
  int tmp;
  for (tmp=0;tmp<=8;tmp++){
    temp->cellToDie[tmp] = tmp;
  }
  temp->color[0] = 0;
  temp->color[1] = 0;
  temp->color[2] = 255;
    temp->next = NULL;

  RuleReader *r = new RuleReader();
  r->parseRules(temp);
  //delete r;
  /*temp = temp->next = (struct rule*)malloc(sizeof(struct rule));;
  //Teste

  temp->id = 2;
  temp->cellToLive = 8;
  temp->amnt = 9;
  temp->cellToDie = (int*)malloc(sizeof(int)*9);
  for (tmp=1;tmp<=8;tmp++){
    temp->cellToDie[tmp-1] = tmp;
  }
  temp->color[0] = 255;
  temp->color[1] = 0;
  temp->color[2] = 0;
  temp->next = NULL;*/


  //rules->next->next = temp;

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


