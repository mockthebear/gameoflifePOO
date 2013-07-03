
#include "../include/GameOfLifeTest.h"

void GameOfLifeTest::setUp() { 
  game = new GameOfLife(10,10);
}

void GameOfLifeTest::tearDown() { 
 if(game) { 
   delete(game); 
 } 
}

/*
 * Testa o construtor das celulas.
 */
void GameOfLifeTest::testCellConstructor() {
  Cell cell;

  CPPUNIT_ASSERT(cell.isAlive());
}

/*
 * Testa a morte das celulas
 */ 
void GameOfLifeTest::testKill() {
  Cell cell;

  CPPUNIT_ASSERT(cell.isAlive());

  cell.kill();

  CPPUNIT_ASSERT(!cell.isAlive());
}

/*
 * Testa o renascimento das celulas
 */
void GameOfLifeTest::testRevive() {
  Cell cell;

  CPPUNIT_ASSERT(cell.isAlive());

  cell.revive();
  CPPUNIT_ASSERT(cell.isAlive());

  cell.kill();
  CPPUNIT_ASSERT(!cell.isAlive());

  cell.revive();
  CPPUNIT_ASSERT(cell.isAlive());
}

/* 
 * Teste nao muito util, ainda incompleto, 
 * com o objetivo de testar o construtor. 
 */
void GameOfLifeTest::testGameOfLifeConstructor() {
  int r = game->aliveCells();
  CPPUNIT_ASSERT_EQUAL(0, r);
}

void GameOfLifeTest::testAliveCells() {
  int r = game->aliveCells();
  CPPUNIT_ASSERT_EQUAL(0, r);
}

/*
 * Teste para verificar as celulas que se tornaram 
 * vivas em um jogo. 
 */
void GameOfLifeTest::testMakeCellAlive() {
  int r = game->aliveCells();
  
  CPPUNIT_ASSERT_EQUAL(0, r);

  game->makeCellAlive(0,0);
  game->makeCellAlive(0,1);
  
  r = game->aliveCells();
  
  CPPUNIT_ASSERT_EQUAL(2, r);
  
}

/*
 * Testa o metodo que conta a quantidade de celulas 
 * vizinhas vivas. Ooops, esse teste eh interessante. 
 */
void GameOfLifeTest::testAliveNeighborCells() {
  game->makeCellAlive(0,0);
  
  int r = game->aliveNeighborCells(0,0);

  CPPUNIT_ASSERT_EQUAL(0, r);
  
  game->makeCellAlive(0,1);
  game->makeCellAlive(1,0);
  game->makeCellAlive(1,1);
   
  r = game->aliveNeighborCells(0,0);

  CPPUNIT_ASSERT_EQUAL(3, r);   
  
}

/* 
 * Teste que verifica o assassinato (ou melhor, a morte) 
 * de celulas em um jogo.  
 */
void GameOfLifeTest::testMakeCellDead() { 
  int r = game->aliveCells();
  
  CPPUNIT_ASSERT_EQUAL(0, r);

  game->makeCellAlive(0,0);
  game->makeCellAlive(0,1);
  
  r = game->aliveCells();
  
  CPPUNIT_ASSERT_EQUAL(2, r);

  game->makeCellDead(0,2);

  r = game->aliveCells();
  
  CPPUNIT_ASSERT_EQUAL(2, r);

  game->makeCellDead(0,0);

  r = game->aliveCells();
  
  CPPUNIT_ASSERT_EQUAL(1, r);

}

/*
 * Esse eh o teste mais interessante, pois considera as 
 * proximas geracoes usando o algoritmo do Conway!
 */
void GameOfLifeTest::testConwayNextGeneration() {
  game->makeCellAlive(2,2);
  game->makeCellAlive(2,3);
  game->makeCellAlive(2,4);

  game->nextGeneration();

  //apos a nova geracao, as celulas vivas 
  //anteriores devem estar mortas.

  CPPUNIT_ASSERT(!game->isCellAlive(2,2));
  CPPUNIT_ASSERT(!game->isCellAlive(2,4));
  
  //por outro lado, as proximas celulas 
  //devem estar vivas.
  CPPUNIT_ASSERT(game->isCellAlive(1,3));
  CPPUNIT_ASSERT(game->isCellAlive(2,3));
  CPPUNIT_ASSERT(game->isCellAlive(3,3));
  
  game->nextGeneration();

  //a proxima geracao deve ser a mesma 
  //da anterior.

  CPPUNIT_ASSERT(game->isCellAlive(2,2));
  CPPUNIT_ASSERT(game->isCellAlive(2,3));
  CPPUNIT_ASSERT(game->isCellAlive(2,4));
}
