#include <iostream>
#include <string>

using namespace std;

#include "../include/GameOfLife.h"
#include "../include/GameBoard.h"
#include "../include/Controller.h"

const int rows = 10;
const int cols = 10;

int main() {
  cout << " _____                      _____  __ _      _  __     "       << endl;
  cout << "|  __ \\                    |  _  |/ _| |    (_)/ _|    "      << endl;
  cout << "| |  \\/ __ _ _ __ ___   ___| | | | |_| |     _| |_ ___ "      << endl;
  cout << "| | __ / _` | '_ ` _ \\ / _ \\ | | |  _| |    | |  _/ _ \\"    << endl;
  cout << "| |_\\ \\ (_| | | | | | |  __| \\_/ / | | |____| | ||  __/"    << endl;
  cout << " \\____/\\__,_|_| |_| |_|\\___|\\___/|_| \\_____/|_|_| \\___|" << endl << endl << endl;

  cout << "Bem vindo, essa eh a versao C++ do jogo GameOfLife " << endl;
  cout << "escrita por Rodrigo Bonifacio (CiC, UnB) como um desafio " << endl; 
  cout << "para ensinar padroes de projetos." << endl << endl;
  cout << "De forma proposital, existem falhas no design dessa aplicacao." << endl;
  cout << "O objetivo eh fazer com que os alunos resolvam, de uma forma " << endl;
  cout << "dirigida e usando padroes de projeto, as principais falhas " << endl;
  cout << "de design. Pressione alguma tecla para comecar: " ;

  getchar();

  GameOfLife game(cols, rows);
  GameBoard board(rows, cols);
  Controller controller(game, board);

  controller.startGame();
  
}


