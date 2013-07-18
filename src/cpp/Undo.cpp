#include "../include/Undo.h"

Undo::Undo(int ia,int ja){
    amnt = state = 0;
    i = ia;
    j = ja;
    /*for (int k=0;k<MAXUNDOS;k++){
        steps[k] = (void*)0;
    }*/

}

void Undo::addStep(Cell **s){
    if (amnt == MAXUNDOS){
        delete steps[0];
        for (int f=0;f<MAXUNDOS-1;f++){
            steps[f] = steps[f+1];
        }
        steps[amnt-1] = new Memento(s,i,j);
    }else{
        steps[amnt] = new Memento(s,i,j);
        amnt++;
    }
}

bool Undo::reallyUndo(Cell **s){
    if (amnt-1 < 0){
        return false;
    }
    Cell **lst = steps[amnt-1]->getCells();
    for(int ia = 0; ia < j; ia++) {
        for(int ja = 0; ja < i; ja++) {
            if(lst[ia*i + ja]->isAlive()){
                s[ia*i + ja]->revive(lst[ia*i + ja]->getType());
            }else{
                s[ia*i + ja]->kill();
           }
        }
    }
    delete steps[amnt-1];
    amnt--;
    return true;

}
Cell::~Cell(){
    //SDL_FreeSurface(s);
}
Cell::Cell(int i,int j,int t,int typ){
  state = ALIVE;
  i = i;
  j = j;
  type = typ;
}

Memento::Memento(Cell **c,int i,int j){
    cells = new Cell*[i*j];
    for(int ia = 0; ia < j; ia++) {
        for(int ja = 0; ja < i; ja++) {
          cells[ia*i + ja] = new Cell(ia,ja,0,c[ia*i + ja]->getType());
          if(c[ia*i + ja]->isAlive()){
            cells[ia*i + ja]->revive(c[ia*i + ja]->getType());
          }else{
            cells[ia*i + ja]->kill();
          }
        }
      }
}
Cell **Memento::getCells(){
    return cells;
}
Memento::~Memento(){
    for(int ia = 0; ia < i; ia++) {
        for(int ja = 0; ja < j; ja++) {
            delete cells[ia*i + ja];
        }
    }
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

