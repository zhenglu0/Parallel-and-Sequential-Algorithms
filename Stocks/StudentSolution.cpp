// -*- C++ -*-
// Modified by 罗铮 on 03/30/14.
/*
 * StudentSolution.cpp
 *
 * cilk version from the original stocks.sml at CMU
 *
 * THIS is the only file we will look at when we grade your homework.
 * All other changes you made to any other files will be discarded.
 */

#include <cstdlib>
//#include <cilk/cilk.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include "StocksResult.h"

using namespace std;

#define MIN(x, y) ((x < y) ? x : y)
#define MAX(x, y) ((x > y) ? x : y)

// YOUR naive, quadratic stock market algorithm
void solveStocksNaive_Not_Optimized (const vector<int> &stockSequence, 
                    int beginIndex, int seqLength, StocksResult *result) 
{
    // Initialize the virables
    result->jump = stockSequence[beginIndex+1]-stockSequence[beginIndex];
    // Do the quadratic computation
    for (int i = 0; i < seqLength-1; i++) {
        for (int j = i + 1; j < seqLength; j++) {
            if (result->jump < stockSequence[j] - stockSequence[i]) {
                result->jump = stockSequence[j] - stockSequence[i];
                result->bestBuy = i;
                result->bestSell = j;
            }
        }
    }
}

// An optimized version of the algorithm naive
// http://www.geeksforgeeks.org/maximum-difference-between-two-elements/
void solveStocksNaive(const vector<int> &stockSequence, 
                    int beginIndex, int seqLength, StocksResult *result)
{
    int n = seqLength;
    const vector<int> arr = stockSequence;
    // Initialize diff, current sum and max sum
    // and bestBuy and bestSell
    int diff = arr[1]-arr[0];
    int curr_sum = diff;
    int max_sum = curr_sum;
    int current_start = 0, 
        current_end = 1;
    result->bestBuy = 0;
    result->bestSell = 1;

    for(int i = 1; i < n-1; i++) {
        // Calculate current diff
        // cout << "diff = " << diff << endl;
        diff = arr[i+1]-arr[i];
 
        // Calculate current sum
        if (curr_sum > 0) {
            curr_sum += diff;
            current_end = i+1;
        } else {
            curr_sum = diff;
            current_start = i;
        }
 
        // Update max sum, if needed
        if (curr_sum > max_sum) {
            result->bestSell = current_end;
            result->bestBuy = current_start;
            result->jump = arr[current_end] - 
                           arr[current_start];
            max_sum = curr_sum;
        }
    }
}



// YOUR recursive, divide and conqure stock market algorithm
void solveStocksRecurse(const vector<int> &stockSequence, int beginIndex, 
                        int seqLength, StocksResult *result) 
{
    // Base case of the divide and conqure stock market algorithm 
    if (seqLength == 1) {
        result->low = beginIndex;
        result->high = beginIndex;
        return;
    }

    // Divide step
    int halfLength = seqLength / 2;
    int midPoint = beginIndex + halfLength;

    // By using divide and conqure, we will passs 
    // resultLeft and resultRight as argument
    StocksResult *resultLeft = new StocksResult();
    StocksResult *resultRight = new StocksResult();

    // Conqure step, get resultLeft and resultRight
    solveStocksRecurse(stockSequence, beginIndex, 
                       halfLength, resultLeft);
    solveStocksRecurse(stockSequence, midPoint, 
                       seqLength - halfLength, resultRight);
    // Combine step
    // First calculate the jump between the left and right division
    int jumpBetweenLR = stockSequence[resultRight->high] - 
                        stockSequence[resultLeft->low];

    result->jump = MAX(jumpBetweenLR,
                        MAX(resultLeft->jump, resultRight->jump));

    result->bestBuy = (result->jump == jumpBetweenLR ? resultLeft->low :
                       (result->jump == resultLeft->jump ? 
                        resultLeft-> bestBuy : resultRight->bestBuy)
                       );

    result->bestSell = (result->jump == jumpBetweenLR ? resultRight->high :
                       (result->jump == resultLeft->jump ? 
                        resultLeft-> bestSell : resultRight->bestSell)
                       );

    result->low = (stockSequence[resultLeft->low] < 
                   stockSequence[resultRight->low] ?
                   resultLeft->low : resultRight->low);

    result->high = (stockSequence[resultLeft->high] > 
                    stockSequence[resultRight->high] ?
                    resultLeft->high: resultRight->high);

    // Free memory
    delete resultLeft;
    delete resultRight;
}

// YOUR recursive, divide and conqure stock market algorithm
void solveStocksRecPar(const vector<int> &stockSequence, int beginIndex,
                       int seqLength, StocksResult *result) 
{
    // Base case of the divide and conqure stock market algorithm
    if (seqLength == 1) {
        result->low = beginIndex;
        result->high = beginIndex;
        return;
    }
    
    // Divide step
    int halfLength = seqLength / 2;
    int midPoint = beginIndex + halfLength;
    
    // By using divide and conqure, we will passs 
    // resultLeft and resultRight as argument
    StocksResult *resultLeft = new StocksResult();
    StocksResult *resultRight = new StocksResult();

    // Conqure step, get resultLeft and resultRight
    //cilk_spawn solveStocksRecPar(stockSequence, beginIndex, 
    // halfLength, resultLeft);
    //cilk_spawn solveStocksRecPar(stockSequence, midPoint, 
    // seqLength - halfLength, resultRight);
    //cilk_sync;
    solveStocksRecPar(stockSequence, beginIndex, 
                      halfLength, resultLeft);
    solveStocksRecPar(stockSequence, midPoint, 
                      seqLength - halfLength, resultRight);

    // Combine step
    // First calculate the jump between the left and right division
    int jumpBetweenLR = stockSequence[resultRight->high] - 
                        stockSequence[resultLeft->low];

    result->jump = MAX(jumpBetweenLR,
                        MAX(resultLeft->jump, resultRight->jump));

    result->bestBuy = (result->jump == jumpBetweenLR ? resultLeft->low :
                       (result->jump == resultLeft->jump ? 
                        resultLeft-> bestBuy : resultRight->bestBuy)
                       );

    result->bestSell = (result->jump == jumpBetweenLR ? resultRight->high :
                       (result->jump == resultLeft->jump ? 
                        resultLeft-> bestSell : resultRight->bestSell)
                       );

    result->low = (stockSequence[resultLeft->low] < 
                   stockSequence[resultRight->low] ?
                   resultLeft->low : resultRight->low);

    result->high = (stockSequence[resultLeft->high] > 
                    stockSequence[resultRight->high] ?
                    resultLeft->high: resultRight->high);

    // Free memory
    delete resultLeft;
    delete resultRight;
}
