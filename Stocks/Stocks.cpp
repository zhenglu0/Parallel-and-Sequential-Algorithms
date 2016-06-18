// -*- C++ -*-

/*
 * Stocks.cpp
 *
 * cilk version from the original stocks.sml at CMU
 *
 */

#include <cstdlib>
//#include <cilk/cilk.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "StocksSupport.cpp"
#include "StocksResult.cpp"
#include "StudentSolution.cpp"
#include "Timer.cpp"

using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)

#define MAX_FOR_QUADRATIC 10000

int defaultSeqLen  = 10;
bool printResult_f = true;
bool printSequence_f = false;
bool executeQuadratic_f = true;

int stocksMain(int seqLength, char* myFile)
{
    vector<int> stockSequence;
    
    std::cout << "-----------------------------------------\n"
      "STOCKS PROBLEM: Given a sequence of integer stock prices,\n"
      "find the maximum jump from an earlier price to a later price.\n"
      "-----------------------------------------\n";

    // Initialize stock sequence array
    if (myFile == NULL) {
      // Create random stock sequence
      stockSequence = randomlyGenerateSeq(seqLength);
    } else { 
      // get the sequence from the input file
      stockSequence = getSequenceFromFile(&seqLength, myFile);
    }
    executeQuadratic_f = (seqLength <= MAX_FOR_QUADRATIC);
    // don't print a really long sequence. that's madness
    printSequence_f = printSequence_f && executeQuadratic_f;
    if (printSequence_f)
      printStockSequence(seqLength, stockSequence);

    // Compare various Stock Market Result algorithms on this sequence.
    Timer *quadTimer = new Timer(new string("Quadratic"));
    Timer *recTimer = new Timer(new string("Recursive (Serial)"));
    Timer *recParTimer = new Timer(new string("Recursive Parallel"));

    // if your input is large enough, your quadratic version might
    // not finish. Hence, you can turn this off if you like.
    if (executeQuadratic_f) {
      StocksResult *quadResult = new StocksResult();

      quadTimer->printBegin();
      quadTimer->begin();
      solveStocksNaive(stockSequence, 0, seqLength, quadResult);
      quadTimer->end();
	
      if (printResult_f)
	quadResult->print();
      
      quadTimer->print(); 
    } else 
      std::cout << "Sequence Length too long. Skipping Quadratic Algorithm." 
                << std::endl;

    // Now for the Divide & Conquer Results!

    // Recursive Serial
    {
      StocksResult *recResult = new StocksResult();
      
      recTimer->printBegin();
      recTimer->begin();
      solveStocksRecurse(stockSequence, 0, seqLength, recResult);
      recTimer->end();
      
      if (printResult_f)
	recResult->print();

      recTimer->print();
      if (executeQuadratic_f)
	recTimer->printSpeedup(quadTimer);
    }
    

    // Recursive Parallel
    {
      StocksResult *recParResult = new StocksResult();
      
      recParTimer->printBegin();
      recParTimer->begin();
      solveStocksRecPar(stockSequence, 0, seqLength, recParResult);
      recParTimer->end();
      
      if (printResult_f)
	recParResult->print();
      
      recParTimer->print();

      if (executeQuadratic_f)
	recParTimer->printSpeedup(quadTimer);
      recParTimer->printSpeedup(recTimer);
    }
    
    return 0;
}

int main(int argc, char* argv[])
{
    int seqLength = defaultSeqLen;
    char *myFile = NULL;
    if (argc > 1) {
      // they might just be asking for usage information
      if (std::string(argv[1]) == "-help") {
	std::cout << "--------- Stocks -help -------------------" << std::endl;
	std::cout << "Usage: ./Stocks -f filename -pRes 0" << std::endl 
		  << "        --OR--" << std::endl 
		  << "       ./Stocks -len 30 -max 100 -pRes 0" << std::endl 
		  << "       where: " << std::endl 
		  << " -f filename specifies that the file called filename "
         "has the stock sequence" << std::endl
		  << "             First line of the file contains"
         " the sequence length" << std::endl
		  << "             Each line after that gives "
         "the stock price" << std::endl
		  << " -pRes 1|0   whether you want the result to be "
         "printed (Default = 1)" << std::endl
		  << " -pSeq 1|0   whether you want the sequence to be"
         " printed (Default = 0)" << std::endl
		  << " The following arguments apply ONLY to randomly "
         "generated stock sequences:" << std::endl
		  << "             (which will occur if no input file "
         "is specified)" << std::endl
		  << " -len x      limits sequence length to x "
         "(Default = " << defaultSeqLen << ")" << std::endl
		  << " -max x      limits maximum stock value to x"
         " (Default = " << maxStockValue << ")" << std::endl;
	exit(0);
      }

      // or they might actually want to run the code!
      for (int i = 1; i < argc; i=i+2) {
	if (std::string(argv[i]) == "-f") {
	  // We know the next argument *should* be the filename:
	  myFile = argv[i + 1];
	} else if (std::string(argv[i]) == "-len") {
	  // We know the next argument *should* be sequence length:
	  seqLength = atoi(argv[i + 1]);
        } else if (std::string(argv[i]) == "-max") {
	  // We know the next argument *should* be max stock value:
	  maxStockValue = atoi(argv[i + 1]);
        } else if (std::string(argv[i]) == "-pRes") {
	  // We know the next argument *should* be 1 or 0
	  printResult_f = (atoi(argv[i + 1]) == 0) ? false : true;
        } else if (std::string(argv[i]) == "-pSeq") {
	  // We know the next argument *should* be 1 or 0
	  printSequence_f = (atoi(argv[i + 1]) == 0) ? false : true;
        } 
      }
    }
    std::cout << "Note: for a complete explanation of command line "
                 "arguments, type: ./Stocks -help" << std::endl;
 
    return stocksMain(seqLength, myFile);
}
