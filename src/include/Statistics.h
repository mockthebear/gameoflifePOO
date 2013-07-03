/**
 * @file
 * 
 * A component that keeps information about the 
 * number of born and killed cells. It is another 
 * UI interface, since each time a cell is killed or revived, 
 * a text is displayed.
 *
 * @author Rodrigo Bonifacio (rbonifacio[at]cic.unb.br)
 * @date 05/2011
 */

#ifndef STATISTICS_H
#define STATISTICS_H

/*! Statistics class definition
 *
 * This class keeps a history of the number 
 * of killed and revived cells. 
 */ 
class Statistics {
 private:
  int survivors;
  int killed; 
 public:
  /*! Basic constructor, initializing the number of survivors and killed cells to zero */ 
  Statistics() : survivors(0), killed(0) {}

  /*! Notifies that a cell was revived */
  void survive();
  
  /*! notifies that a cell was killed */ 
  void kill();
};
#endif
