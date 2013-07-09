#include <SDL/SDL.h>
#include <iostream>
#include <list>
#include <cstring>

#include "../include/Cell.h"

Rule::Rule(){
	descricao = (char*) calloc(sizeof(char), 1);
	/*TODO: Abrir janela para inserir condições*/
};

void Rule::setDescricao(){
	descricao = (char*) realloc(descricao, (strlen(descricao)+strlen("Goes ")));
	strcat(descricao, "Goes ");

	descricao = (char*) realloc(descricao, (strlen(descricao)+strlen(nextStateName)));
	strcat(descricao, nextStateName);

	descricao = (char*) realloc(descricao, (strlen(descricao)+strlen(" if ")));
	strcat(descricao, " if ");

	descricao = (char*) realloc(descricao, (strlen(descricao)+strlen((char*)cells)));
	strcat(descricao, (char*)cells);

	descricao = (char*) realloc(descricao, (strlen(descricao)+strlen(" ")));
	strcat(descricao, " ");

	descricao = (char*) realloc(descricao, (strlen(descricao)+strlen(stateChanger)));
	strcat(descricao, stateChanger);

	descricao = (char*) realloc(descricao, (strlen(descricao)+strlen(" are found near the cell.\n")));
	strcat(descricao, " are found near the cell.\n");
};

char* Rule::getDescricao(){
	return descricao;
};

char* Rule::analize(Cell* cell){
	int cellsAround;

	cellsAround = cell->getAroundCells().find(stateChanger)->second;
	if(cellsAround == cells) return nextStateName;
	else return NULL;
};








State::State(char *nome, char* path){
	this->nome = nome;
	s = SDL_LoadBMP(path);
	Rules.clear();
};

State::State(char *nome, char *descricao, char* path){
	this->nome = nome;
	this->descricao = descricao;
	s = SDL_LoadBMP(path);
	Rules.clear();
};

void State::addRule(Rule newrule){
	Rules.push_back(newrule);
}

void State::setNome(char *nome){
	this->nome = nome;
}

void State::setDescricao(char *descricao){
	this->descricao = descricao;
}

char* State::getNome(){
	return nome;
}

char* State::getDescricao(){
	return descricao;
}

char* State::process(Cell* cell){
	list<Rule>::iterator It;
	char *next;

	It = Rules.begin();
	do {
		next = (*It).analize(cell);
		It++;
	} while(next == NULL && It != Rules.end());
	return next;
}

list<Rule> State::getRules(){
	return Rules;
}

SDL_Surface* State::getSurface(){
	return s;
}







Cell::Cell(int i,int j,int t){
  setState("alive");
  i = i;
  j = j;
  switch(t){
        case 1:
            s=SDL_LoadBMP( "../content/red.bmp" );
        break;
        default:
            s=SDL_LoadBMP( "../content/yellow.bmp" );
  }

}

void Cell::kill() {
	setState("dead");
}

void Cell::revive() {
	setState("alive");
}

bool Cell::isAlive() {
	return getState() == "alive";
}

char* Cell::getState() {
	return state->getNome();
}

void Cell::setState(char* stateName) {
	state = findState(stateName);
}

void Cell::lookAround(int w, int h, int width, int height, Cell** cells) {
	map<char*, int>::iterator It;
	int x, y;
	char* estado;
	void* game;

	AroundCells.clear();
	It = AroundCells.begin();
	for(x = w-1; x<=w+1; x++){
		for(y = h-1; y<=h+1; y++){
			if(x<0 || x>width || y<0 || y>height){
				It = AroundCells.find("dead");
				if (It == AroundCells.end()) AroundCells["dead"] = 0;
				else AroundCells["dead"] += 1;
			}
			else{
				estado = getCell(x, y, width, height, cells)->getState();
				It = AroundCells.find(estado);
				if (It == AroundCells.end()) AroundCells[estado] = 0;
				else AroundCells[estado] += 1;
			}
		}
	}
}

void Cell::processNextGen(){
	char* nextGen;

	nextGen = state->process(this);
	if (strcmp(nextGen, state->getNome()) != 0) setState(nextGen);
};

map<char*, int> Cell::getAroundCells(){
	return AroundCells;
};

Cell *Cell::getCell(int w, int h, int width, int height, Cell** cells) {
	if(w < 0 || w >= width) return NULL;
	if(h < 0 || h >= height) return NULL;

	return  cells[h * width + w];
}

SDL_Surface* Cell::getSurface(){
	return state->getSurface();
}