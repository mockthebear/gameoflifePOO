#include <iostream>

using namespace std;

#include "../include/Statistics.h"

void Statistics::survive() {
  cout << "Number of cells revived: " << ++survivors << endl;
}

void Statistics::kill() {
  cout << "Number of cells killed: " << ++killed << endl;
} 
