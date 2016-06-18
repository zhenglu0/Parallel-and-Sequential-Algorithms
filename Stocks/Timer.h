// -*- C++ -*-

/*
 * Timer.h
 *
 * Shielding you from the timing mess.
 * You shouldn't have to call or use anything here. 
 * It's all been done for you.
 */

#ifndef TIMER_H
#define TIMER_H

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)

class Timer {

 public:

  unsigned long long startTick, endTick;
  
  long totalTime;

  string name;

  Timer(string *timerName);
  
  void printBegin();
  void begin();
  void end();
  void print();
  void printSpeedup(Timer *speedupOverThisTimer);
};

#endif