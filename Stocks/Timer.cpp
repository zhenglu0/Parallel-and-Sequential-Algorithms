// -*- C++ -*-

/*
 * Timer.cpp
 *
 * Shielding you from the timing mess.
 * You shouldn't have to call or use anything here. 
 * It's all been done for you.
 */

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include "cilktime.h"
#include "Timer.h"

using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)


// simple constructor
Timer::Timer(string *timerName) {

  startTick = endTick = 0;
  
  totalTime = 0;

  name = *timerName;

}

void Timer::printBegin() {
  std::cout << "----- " << name << " version -----" << std::endl;
}

void Timer::begin() {
  startTick = cilk_getticks();
}

void Timer::end() {
  endTick = cilk_getticks();
  totalTime = (long)(endTick - startTick);
}

void Timer::print() {
  std::cout.setf(ios::fixed);
  std::cout.precision(2);
  std::cout << "  " << name << " Runtime (in milliseconds) = " 
            << totalTime / 1000.f << std::endl;
}

void Timer::printSpeedup(Timer *speedupOverThisTimer) {

    float speedUp = 0;
    if (totalTime > 0) {
      speedUp = speedupOverThisTimer->totalTime / (float) totalTime;
    }
    std::cout.precision(2);
    std::cout << "  " << name << " Speedup over "
	      << speedupOverThisTimer->name << ": " 
	      << speedUp << "x faster"; 
    if (speedUp < 1.0)
      std::cout << " (ie, slower)";
    std::cout << std::endl;
      
}
