#ifndef GAME_OF_LIFE_H 
#define GAME_OF_LIFE_H

#include <cppunit/extensions/HelperMacros.h>
#include <exception>

#include "GameOfLife.h"

class GameOfLifeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE ( GameOfLifeTest );
  CPPUNIT_TEST ( testCellConstructor ); 
  CPPUNIT_TEST( testGameOfLifeConstructor );
  CPPUNIT_TEST ( testKill );
  CPPUNIT_TEST ( testRevive );
  CPPUNIT_TEST ( testAliveCells );
  CPPUNIT_TEST ( testMakeCellAlive );
  CPPUNIT_TEST ( testMakeCellDead );
  CPPUNIT_TEST ( testAliveNeighborCells ); 
  CPPUNIT_TEST ( testConwayNextGeneration );
  CPPUNIT_TEST_SUITE_END(); 

 public:
  void setUp();
  void tearDown();

  void testCellConstructor();
  void testKill();
  void testRevive();
  void testGameOfLifeConstructor();
  void testAliveCells();
  void testMakeCellAlive();
  void testMakeCellDead();
  void testAliveNeighborCells();
  void testConwayNextGeneration(); 
 private:
  GameOfLife* game;
};

#endif 
