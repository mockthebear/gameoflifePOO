#include "../include/GameOfLife.h"



GameOfLife::GameOfLife(int w, int h) {
	width = w;
	height = h;

	cells = new Cell*[w*h];
	states.clear();
	states.push_back(new State("dead", "Celula morta comum", "../content/yellow.bmp"));
	states.push_back(new State("alive", "Celula viva comum", "../content/yellow.bmp"));

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			cells[i*width + j] = new Cell(i,j,0);
		}
	}

	killEnvironment();

	statistics = new Statistics();
}

void GameOfLife::killEnvironment() {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			getCell(i, j)->setState("dead");
		}
	}
}

Cell *GameOfLife::getCell(int w, int h) {
	if(w < 0 || w >= width) return NULL;
	if(h < 0 || h >= height) return NULL;

	return  cells[h * width + w];
}

void GameOfLife::nextGeneration() {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			getCell(i, j)->lookAround(i, j, width, height, getCells());
		}
	}
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			getCell(i, j)->processNextGen();
		}
	}
}

char* GameOfLife::getState(int w, int h) {
	return getCell(w, h)->getState();
}

State* GameOfLife::findState(char *stateName){
	list<State*>::iterator It;
	int x;

      It = states.begin();

	for (x = states.size(); x > 0; x--){
		if(strcmp((*It)->getNome(), stateName) == 0) return (*It);
		It++;
	}
	return NULL;
}

Cell** GameOfLife::getCells(){
	return cells;
}

bool GameOfLife::isCellAlive(int j, int i){
	char* estado = getCell(i, j)->getState();
	return (strcmp(estado, "alive") == 0);
}