#include <iostream>

using namespace std;

#include "../include/GameBoard.h"
#include "../include/Screen.h"

void GameBoard::clearScreen() {
  cout << ".\n";
  cout << ".\n";
  cout << ".\n";
  cout << ".\n";
  cout << ". Nova geracao \n";
  cout << ".\n";
  cout << ".\n";
  cout << ".\n";
  cout << ".\n";
  cout << ".\n";
}

void GameBoard::printLineIds() {
   for(int i = 0; i < cols; i++) {
     cout << "   " << i << "   " ;
   }
   cout << endl;
}

void GameBoard::printLine() {
  for(int i = 0; i < cols; i++) {
    cout << line;
  }
  cout << endl;
}

void GameBoard::update(GameOfLife& game) {
  clearScreen();

  printLineIds();
  printLine();

  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      //cout << (game.isCellAlive(j,i) ? alive : dead) ;
      tela->setCell(i,j,game.isCellAlive(j,i));
    }
    cout << "   " << i << endl;
    printLine();
  }

}
