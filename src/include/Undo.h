#ifndef UNDOH
#define UNDOH

#define MAXUNDOS 10

//! EnumState enumeration.
/*! Define the valid states of a cell. */
enum EnumState {DEAD, ALIVE};

/*! Cell class definition
 *
 *  The cell class represents a Cell
 *  in the game of life. Each cell has a
 *  state and methods for killing or
 *  reviving.
 */


class Cell {
 private:
  EnumState state;

  int i,j,type;
 public:
  //SDL_Surface *s;
  Cell(int,int,int,int);
  ~Cell();

  int getType(){return type;};
  /*! Changes the state of a cell to DEAD */
  void kill();

  /*! Changes the state of a cell to ALIVE */
  void revive(int);

  /*! Verifies whether a cell is alive or not */
  bool isAlive();

};

class Memento{
        Cell** cells;
        int i,j;
    public:
        Memento(Cell **c,int,int);
        ~Memento();
        Cell **getCells();
};

class Undo{
        Memento *steps[MAXUNDOS+1];
        int amnt,state,i,j;
        public:
            Undo(int,int);
            ~Undo();
            bool reallyUndo(Cell **s);
            void addStep(Cell **s);

};

#endif

