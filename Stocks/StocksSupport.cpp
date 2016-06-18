// -*- C++ -*-

/*
 * StocksSupport.cpp
 *
 * Protecting 341 students from the ugliness that is files, random
 * number generation, list creation, and print methods.
 *
 */

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)

int maxStockValue = 500;

void checkLen(int len) {
  if (len < 2) {
    cout << "Sequence Length must be > 1";
    exit(0);
  }
}

vector<int> getSequenceFromFile(int* seqLength, char* filename) {

  vector<int> stockSequence;
  //int file_len;
  string line;

  ifstream myfile (filename);
  if (myfile.is_open())
    {
      int i = 0;
      bool first = true;
      while ( myfile.good())
	{
	  getline (myfile,line);
	  int num = atoi(line.c_str());
	  if (first) {
	    *seqLength = num;
	    checkLen(*seqLength);
	    stockSequence.resize(num); // Now We Know How big it should be
	    first = false;
	    std::cout << "File's stock sequence has length: "
		      << num << "." << std::endl << std::endl;
  	  } else {
	    stockSequence[i] = num;
	    i++;
	  }
	}
      myfile.close();
    }
  else {
    cout << "Unable to open file " << filename << std::endl; 
    exit(0);
  }

  return stockSequence;
}

// This code already works and you shouldn't have to understand or
// modify it, so we've stashed it here.
vector<int> randomlyGenerateSeq(int seqLength) {
  
  checkLen(seqLength);

  std::cout << "Randomly generating stock sequence of length: "
	    << seqLength << "." << std::endl <<
	    "Highest possible stock value = "
	    << maxStockValue << "." << std::endl << std::endl;

  vector<int> stockSequence(seqLength);
  for(int i = 0; i < seqLength; i++) {
    // Populate stockSequence 
    // Note: might want to change rand seed at some point... or not!
    stockSequence[i] = rand() % (maxStockValue + 1);
  }
  return stockSequence;
}

void printStockSequence(int seq_len, vector<int> seq) {

  std::cout << "Stock Sequence =  " << std::endl << "   [";

  for (int i = 0; i < seq_len; i++) {
    std::cout << seq[i] << ", ";
    if (((i+1)%20) == 0)
      std::cout << std::endl << "    ";
  }
  std::cout << "]" << std::endl;
}

