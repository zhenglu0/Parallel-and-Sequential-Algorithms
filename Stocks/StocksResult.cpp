// -*- C++ -*-

/*
 * StocksResult.cpp
 *
 * An easy place for you to store the results to the stock problem.
 */

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include "StocksResult.h"

using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)


// simple constructor
StocksResult::StocksResult() {
  bestBuy = 0;
  bestSell = 0;
  jump = 0;
  low = 0;
  high = 0;
}

void StocksResult::print() {
    std::cout << "  Result: (max jump = $" << jump << " (buy @ " << bestBuy << 
      ", sell @ " << bestSell << ")" << std::endl;
}

/* 
 * This method is provided to make your life easier, but you are 
 * not obligated to use it.
 */
void StocksResult::copyBuySellJump(StocksResult *copyFromThisOne) {

      bestBuy = copyFromThisOne->bestBuy;
      bestSell = copyFromThisOne->bestSell;
      jump = copyFromThisOne->jump;
}
