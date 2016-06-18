// -*- C++ -*-

/*
 * StocksResult.h
 *
 * Just a convient place to store the result of your Stock algorithm.
 * We have kept everything public to make the coding simpler.
 */
#ifndef STOCK_RESULT_H
#define STOCK_RESULT_H

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)

class StocksResult {

 public:

  // all of your algorithms need to fill these 3 fields
  int bestBuy, bestSell, jump;
  
  // Quadratic solution does not need to use these fields
  int low, high;
  
  // constructor gives you a clean-slated result, with all fields set to 0
  StocksResult();
  
  void print();

  // For Your Convenience:
  // you do not have to use this, but you are welcome to
  void copyBuySellJump(StocksResult *copyFromThisOne);

};

#endif
