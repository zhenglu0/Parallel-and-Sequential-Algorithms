// Author : Zheng Luo
// Modified by Zheng Luo on 03/26/14.

#include "thread_pool_simple.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <mutex>

using namespace std;
using namespace chrono;

mutex g_mutex;

bool isprime(int num){
    for(int i = 2; i <= sqrt(num); ++i){
        if(num % i == 0) return false;
}
    return true;
}

void calcPrime(int num){
    bool prime = isprime(num);
    lock_guard<mutex> m(g_mutex);
    cout << num << ": " << boolalpha << prime << "\n";
}

int main(int argc, char* argv[])
{
    thread_pool p;
    p.submit(bind(calcPrime,3));
    p.submit(bind(calcPrime,8));
    p.submit(bind(calcPrime,4));
    p.submit(bind(calcPrime,9));

    this_thread::sleep_for(seconds(1));
    return 0;
}
