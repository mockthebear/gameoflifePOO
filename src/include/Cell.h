#ifndef CELL_H
#define CELL_H
#include <cstring>
#include <map>
#include <list>

using namespace std;

class Cell;

class Rule {
private:
	char* nextStateName;
	int cells;
	char* stateChanger;
	char* descricao;
public:
	Rule();
	void setDescricao();
	char* getDescricao();
	char* analize(Cell* cell);
};

class State {
private:
	char *nome, *descricao;
	list<Rule> Rules;
	SDL_Surface *s;
public:
	State(char *nome, char* path);
	State(char *nome, char *descricao, char* path);
	void addRule(Rule newrule);
	void setNome(char *nome);
	void setDescricao(char *descricao);
	char* getNome();
	char* getDescricao();
	char* process(Cell* cell);
	list<Rule> getRules();
	SDL_Surface *getSurface();
};

/*! Cell class definition
 *
 *  The cell class represents a Cell
 *  in the game of life. Each cell has a
 *  state and methods for killing or
 *  reviving.
 */
class Cell {
private:
	State *state;
	map<char*, int> AroundCells;

	int i,j;
public:
	Cell(int,int,int);
	/*! Changes the state of a cell to DEAD */
	void kill();

	/*! Changes the state of a cell to ALIVE */
	void revive();

	/*! Verifies whether a cell is alive or not */
	bool isAlive();

	/*! Return the cell state as a string */
	char* getState();

	/*! Set a cell state */
	void setState(char* stateName);

	/*! Register all around cells */
	void lookAround(int h, int w, int width, int height, Cell** cells);

	/*! Process cell's next state */
	void processNextGen();

	map<char*, int> getAroundCells();

	Cell *getCell(int w, int h, int width, int height, Cell** cells);

	SDL_Surface* getSurface();
};

#endif
